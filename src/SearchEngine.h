#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "TextProcessor.h"
#include "Types.h"

class SearchEngine
{
private:
    TextProcessor processor;

    InvertedIndex index;

    size_t totalDocuments = 0;

    std::vector<SearchResult>
    searchPhrase(const std::string& phrase);

public:
    void buildIndex(const std::string& folderPath);

    std::vector<SearchResult>
    search(const std::string& query);

    const InvertedIndex& getIndex() const;

    size_t getTotalDocuments() const;

    void saveIndex(const std::string& filename) const;

    void loadIndex(const std::string& filename);
};

#endif
