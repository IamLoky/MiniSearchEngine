#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <unordered_map>
#include <vector>

class SearchEngine
{
private:
    std::unordered_map<
        std::string,
        std::unordered_map<std::string, int>
    > index;

public:
    void buildIndex(const std::string& folderPath);

    std::vector<std::pair<std::string, int>>
    search(const std::string& word);
};

#endif
