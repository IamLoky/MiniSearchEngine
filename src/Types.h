#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <unordered_map>

struct Posting
{
   int frequency = 0;
};

struct SearchResult
{
   std::string documentName;
   double score = 0.0;
};

using PostingList =
    std::unordered_map<std::string, Posting>;

using InvertedIndex =
    std::unordered_map<std::string, PostingList>;

#endif
