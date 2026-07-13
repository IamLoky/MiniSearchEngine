#include "SearchEngine.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;
namespace fs = std::filesystem;

static void writeString(std::ofstream& out,
                        const std::string& str)
{
    size_t length = str.size();

    out.write(
        reinterpret_cast<const char*>(&length),
        sizeof(length));

    out.write(str.data(), length);
}

static std::string readString(std::ifstream& in)
{
    size_t length;

    in.read(
        reinterpret_cast<char*>(&length),
        sizeof(length));

    std::string str(length, '\0');

    in.read(&str[0], length);

    return str;
}

void SearchEngine::buildIndex(const string& folderPath)
{
    for(const auto& entry : fs::directory_iterator(folderPath))
    {
        if(!entry.is_regular_file())
        {
            continue;
        }

        string fileName = entry.path().filename().string();
        
        ifstream file(entry.path());

        if(!file.is_open())
        {
            continue;
        }

        totalDocuments++;

        int position = 0;

        string line;

        while(getline(file, line))
        {
            vector<string> words =
                processor.tokenize(line);

            for(const string& word : words)
            {
                Posting& posting =
                    index[word][fileName];

                posting.frequency++;

                posting.positions.push_back(position);

                position++;
            }
        }
    }
}

const InvertedIndex&
SearchEngine::getIndex() const
{
    return index;
}

size_t
SearchEngine::getTotalDocuments() const
{
    return totalDocuments;
}

vector<SearchResult>
SearchEngine::search(const string& query)
{
    vector<SearchResult> results;

    if (query.size() >= 2 &&
        query.front() == '"' &&
        query.back() == '"')
    {
        return searchPhrase(
            query.substr(1, query.size() - 2)
        );
    }

    vector<string> terms = processor.tokenize(query);

    if(terms.empty())
    {
        return {};
    }

    const string& firstTerm = terms[0];

    auto it = index.find(firstTerm);

    if(it == index.end())
    {
        return {};
    }

    unordered_map<string, double> currentResults;

    double df =
        static_cast<double>(it->second.size());

    double idf =
        log(
            static_cast<double>(totalDocuments + 1) / (df + 1)
        );

    for (const auto& document : it->second)
    {
        double tf = document.second.frequency;

        currentResults[document.first] =
            tf * idf;
    }

    for (size_t i = 1; i < terms.size(); i++)
    {
        auto postingIt = index.find(terms[i]);

        if (postingIt == index.end())
        {
            return {};
        }

        auto current = currentResults.begin();

        while (current != currentResults.end())
        {
            auto posting = postingIt->second.find(current->first);

            if (posting == postingIt->second.end())
            {
                current = currentResults.erase(current);
            }
            else
            {
                double df =
                    static_cast<double>(postingIt->second.size());

                double idf =
                    log(
                        static_cast<double>(totalDocuments + 1) / (df + 1)
                    );

                double tf =
                    posting->second.frequency;

                current->second += tf * idf;
                ++current;
            }
        }
    }

    for (const auto& document : currentResults)
    {
        results.push_back(
        {
            document.first,
            document.second
        });
    }

    sort(
        results.begin(),
        results.end(),
        [](const SearchResult& a,
           const SearchResult& b)
        {
            return a.score > b.score;
        }
    );

    return results;
}

vector<SearchResult>
SearchEngine::searchPhrase(const string& phrase)
{
    vector<SearchResult> results;

    vector<string> terms = processor.tokenize(phrase);

    if (terms.empty())
        return results;

    auto firstWord = index.find(terms[0]);

    if (firstWord == index.end())
        return results;

    for (const auto& document : firstWord->second)
    {
        const string& fileName = document.first;

        int phraseCount = 0;

        // Try every occurrence of the first word
        for (int startPos : document.second.positions)
        {
            bool match = true;

            // Check remaining words
            for (size_t term = 1; term < terms.size(); term++)
            {
                auto wordIt = index.find(terms[term]);

                if (wordIt == index.end())
                {
                    match = false;
                    break;
                }

                auto docIt = wordIt->second.find(fileName);

                if (docIt == wordIt->second.end())
                {
                    match = false;
                    break;
                }

                bool foundPosition = false;

                for (int pos : docIt->second.positions)
                {
                    if (pos == startPos + static_cast<int>(term))
                    {
                        foundPosition = true;
                        break;
                    }
                }

                if (!foundPosition)
                {
                    match = false;
                    break;
                }
            }

            if (match)
                phraseCount++;
        }

        if (phraseCount > 0)
        {
            results.push_back(
            {
                fileName,
                static_cast<double>(phraseCount)
            });
        }
    }

    sort(results.begin(), results.end(),
         [](const SearchResult& a,
            const SearchResult& b)
         {
             return a.score > b.score;
         });

    return results;
}

void SearchEngine::saveIndex(const string& filename) const
{
    ofstream out(filename, ios::binary);

    if(!out)
    {
        throw runtime_error(
            "Could not open file for writing.");
    }

    constexpr char MAGIC[] = "MSE1";

    writeString(out, MAGIC);

    constexpr int INDEX_VERSION = 1;

    out.write(
        reinterpret_cast<const char*>(&INDEX_VERSION),
        sizeof(INDEX_VERSION));

    out.write(
        reinterpret_cast<const char*>(
            &totalDocuments),
        sizeof(totalDocuments));

    size_t totalWords = index.size();

    out.write(
        reinterpret_cast<char*>(&totalWords),
        sizeof(totalWords));

    for(const auto& wordEntry : index)
  {
    // Write the word
      writeString(out, wordEntry.first);

      size_t postingCount = wordEntry.second.size();

      out.write(
          reinterpret_cast<const char*>(&postingCount),
          sizeof(postingCount));

    // Write each posting
      for(const auto& postingEntry : wordEntry.second)
      {
          writeString(out, postingEntry.first);

          const Posting& posting = postingEntry.second;

          out.write(
              reinterpret_cast<const char*>(&posting.frequency),
              sizeof(posting.frequency));

          size_t positionCount =
              posting.positions.size();

          out.write(
              reinterpret_cast<const char*>(&positionCount),
              sizeof(positionCount));

          for(int position : posting.positions)
          {
              out.write(
                  reinterpret_cast<const char*>(&position),
                  sizeof(position));
          }
      }
  }
}

void SearchEngine::loadIndex(const string& filename)
{
    ifstream in(filename, ios::binary);

    if(!in)
    {
        throw runtime_error(
            "Could not open index file.");
    }

    index.clear();
}
