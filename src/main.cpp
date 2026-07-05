#include "SearchEngine.h"

#include <iostream>

using namespace std;

int main()
{
  SearchEngine engine;

  engine.buildIndex("docs");

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
