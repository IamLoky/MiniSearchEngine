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

        string line;

        while(getline(file, line))
        {
            vector<string> words =
                processor.tokenize(line);

            for(const string& word : words)
            {
                index[word][fileName].frequency++;
            }
        }
    }
}

vector<SearchResult>
SearchEngine::search(const string& query)
{
    vector<SearchResult> results;

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
