#include "SearchEngine.h"

#include <iostream>

using namespace std;

int main()
{
  SearchEngine engine;

  engine.loadIndex("index.bin");

  engine.saveIndex("index.bin");

  cout << "Index saved successfully.\n";

  string query;

  cout << "Enter search query: ";
  getline(cin, query);

  auto results = engine.search(query);

  cout << "Search Results:\n";

  for(const auto& result : results)
  {
    cout
        << result.documentName
        << " ("
        << result.score
        << ")\n";
  }

  return 0;
}
