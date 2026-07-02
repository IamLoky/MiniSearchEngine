#include "TextProcessor.h"

#include <algorithm>
#include <sstream>
#include <cctype>

using namespace std;

TextProcessor::TextProcessor()
{
    stopWords =
    {
        "a",
        "an",
        "the",
        "is",
        "are",
        "was",
        "were",
        "of",
        "to",
        "for",
        "on",
        "in",
        "at",
        "by",
        "with",
        "and",
        "or"
      };
}

string TextProcessor::cleanWord(const string& word)
{
    string result;

    for(char ch : word)
    {
        if(isalnum(static_cast<unsigned char>(ch)))
        {
            result +=
                tolower(static_cast<unsigned char>(ch));
        }
    }

    return result;
}

bool TextProcessor::isStopWord(
    const string& word) const
{
    return stopWords.find(word)
           != stopWords.end();
}

vector<string>
TextProcessor::tokenize(
    const string& text)
{
    vector<string> words;

    stringstream ss(text);

    string word;

    while(ss >> word)
    {
        word = cleanWord(word);

        if(word.empty())
            continue;

        if(isStopWord(word))
            continue;

        words.push_back(word);
    }

    return words;
}
