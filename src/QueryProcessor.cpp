#include "QueryProcessor.h"

QueryProcessor::QueryProcessor(
    const InvertedIndex& index,
    size_t totalDocuments
)
    : index(index),
      totalDocuments(totalDocuments)
{
}
