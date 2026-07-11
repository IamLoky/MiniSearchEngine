#include "SearchEngine.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

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

    unordered_map<string, int> currentResults;

    for (const auto& document : it->second)
    {
       currentResults[document.first] =
           document.second.frequency;
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
                current->second += posting->second.frequency;
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

    if (terms.size() != 2)
    {
        return results;
    }

    auto firstIt = index.find(terms[0]);
    auto secondIt = index.find(terms[1]);

    if (firstIt == index.end() || secondIt == index.end())
    {
        return results;
    }

    for (const auto& doc : firstIt->second)
    {
        auto secondDoc = secondIt->second.find(doc.first);

        if (secondDoc == secondIt->second.end())
        {
            continue;
        }

        const vector<int>& pos1 = doc.second.positions;
        const vector<int>& pos2 = secondDoc->second.positions;

        size_t i = 0;
        size_t j = 0;

        while (i < pos1.size() && j < pos2.size())
        {
            if (pos2[j] == pos1[i] + 1)
            {
                results.push_back(
                {
                    doc.first,
                    1.0
                });

                break;
            }
            else if (pos2[j] < pos1[i] + 1)
            {
                j++;
            }
            else
            {
                i++;
            }
        }
    }

    return results;
}
