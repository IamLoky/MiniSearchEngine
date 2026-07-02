#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "TextProcessor.h"

class SearchEngine
{
private:
    TextProcessor processor;

    std::unordered_map<
        std::string,
        std::unordered_map<std::string, int>
    > index;

    std::unordered_set<std::string> stopWords =
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

public:
    void buildIndex(const std::string& folderPath);

    std::vector<std::pair<std::string, int>>
    search(const std::string& query);
};

#endif
