#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <unordered_map>
#include <vector>

struct Posting
{
   int frequency = 0;

   std::vector<int> positions;
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
