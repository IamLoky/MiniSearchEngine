#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "TextProcessor.h"

struct Posting
{
    int frequency = 0;
};

struct SearchResult
{
    std::string documentName;
    int score = 0;
};

using PostingList =
    std::unordered_map<std::string, Posting>;

using InvertedIndex =
    std::unordered_map<std::string, PostingList>;

class SearchEngine
{
private:
    TextProcessor processor;

    InvertedIndex index;

    size_t totalDocuments = 0;

public:
    void buildIndex(const std::string& folderPath);

    std::vector<SearchResult>
    search(const std::string& query);
};

#endif
