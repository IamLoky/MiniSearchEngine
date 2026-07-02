#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <string>
#include <unordered_set>
#include <vector>

class TextProcessor
{
private:
    std::unordered_set<std::string> stopWords;

public:
    TextProcessor();

    std::string cleanWord(const std::string& word);

    bool isStopWord(const std::string& word) const;

    std::vector<std::string> tokenize(const std::string& text);
};

#endif
