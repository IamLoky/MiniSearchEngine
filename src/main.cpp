#include "SearchEngine.h"

#include <filesystem>
#include <iostream>

using namespace std;

namespace fs = std::filesystem;

int main()
{
    SearchEngine engine;

    if(fs::exists("index.bin"))
    {
        cout << "Loading index...\n";
        engine.loadIndex("index.bin");
    }
    else
    {
        cout << "Building index...\n";
        engine.buildIndex("docs");
        engine.saveIndex("index.bin");
    }

    string query;

    while(true)
    {
        cout << "\nEnter search query (type 'exit' to quit): ";

        getline(cin, query);

        if(query == "exit")
            break;

        auto results = engine.search(query);

        cout << "\nSearch Results:\n";

        if(results.empty())
        {
            cout << "No matching documents found.\n";
            continue;
        }

        for(const auto& result : results)
        {
            cout
                << result.documentName
                << " ("
                << result.score
                << ")\n";
        }
    }

    return 0;
}
