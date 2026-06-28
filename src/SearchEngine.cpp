#include "SearchEngine.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

string normalizeWord(string word)
{
    for(char& ch : word)
    {
        ch = tolower(static_cast<unsigned char>(ch));
    }

    return word;
}

string cleanWord(string word)
{
    string result;

    for(char ch : word)
    {
        if(isalnum(static_cast<unsigned char>(ch)))
        {  
            result += tolower(ch);
        }
    }

    return result;
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

        string word;

        while(file >> word)
        {
            word = cleanWord(word);

            if(word.empty())
            {
                continue;
            }
            index[word][fileName]++;
        }
    }
}

vector<pair<string, int>>
SearchEngine::search(const string& word)
{
    vector<pair<string, int>> results;

    string query = cleanWord(word);

    auto it = index.find(query);

    if(it == index.end())
    {
        return results;
    }

    for(const auto& document : it->second)
    {
        results.push_back(document);
    }

    sort(
        results.begin(),
        results.end(),
        [](const auto& a, const auto& b)
        {
            return a.second > b.second;
        }
    );

    return results;
}
