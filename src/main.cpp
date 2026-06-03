#include "SearchEngine.h"

#include <iostream>

using namespace std;

int main()
{
  SearchEngine engine;

  engine.buildIndex("../docs");

  auto results = engine.search("apple");

  cout << "Search Results:\n";

  for(const auto& result : results)
  {
    cout
        << result.first
        << " ("
        << result.second
        << ")\n";
  }

  return 0;
}
