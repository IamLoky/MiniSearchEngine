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
}
