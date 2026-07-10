#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include "Types.h"
#include "TextProcessor.h"

class QueryProcessor
{
private:
    const InvertedIndex& index;
    size_t totalDocuments;
    TextProcessor processor;

public:
    QueryProcessor(
        const InvertedIndex& index,
        size_t totalDocuments
    );
};

#endif
