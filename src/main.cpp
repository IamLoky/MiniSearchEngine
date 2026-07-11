#include "SearchEngine.h"

#include <iostream>

using namespace std;

int main()
{
  SearchEngine engine;

  engine.buildIndex("docs");

  const auto& index = engine.getIndex();

  auto it = index.find("apple");

  if(it != index.end())
  {
      std::cout << "APPLE\n";

      for(const auto& doc : it->second)
      {
          std::cout << doc.first << "\n";

          std::cout << "Frequency: "
                    << doc.second.frequency
                    << "\n";

          std::cout << "Positions: ";

          for(int pos : doc.second.positions)
          {
              std::cout << pos << " ";
          }

          std::cout << "\n\n";
       }
   }

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
