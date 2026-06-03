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
