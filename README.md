# Mini Search Engine

A C++-based Mini Search Engine that indexes a collection of text documents and supports efficient document retrieval using an **Inverted Index**, **Positional Index**, **TF-IDF ranking**, and **Binary Serialization**.

## Overview

This project demonstrates the core ideas behind modern search engines by implementing efficient indexing and retrieval techniques from scratch in C++. It focuses on clean object-oriented design, efficient STL data structures, and practical information retrieval algorithms.

## Features

* Inverted Index for fast keyword lookup
* Positional Posting Lists for phrase search
* Multi-word AND query support
* Phrase search using positional indexes
* TF-IDF based document ranking
* Text normalization (case folding and punctuation removal)
* Stop-word removal
* Binary serialization and deserialization of the index
* Persistent index loading to avoid rebuilding the index every execution

## Technologies Used

* C++17
* STL

  * `unordered_map`
  * `unordered_set`
  * `vector`
  * `filesystem`
* Object-Oriented Programming
* Binary File I/O

## Project Structure

```text
MiniSearchEngine/
│
├── docs/
│   ├── doc1.txt
│   ├── doc2.txt
│   ├── doc3.txt
│   └── doc4.txt
│
├── src/
│   ├── main.cpp
│   ├── SearchEngine.cpp
│   ├── SearchEngine.h
│   ├── TextProcessor.cpp
│   ├── TextProcessor.h
│   ├── QueryProcessor.cpp
│   └── QueryProcessor.h
│
├── index.bin
├── README.md
└── .gitignore
```

## Architecture

```text
                 Documents
                     │
                     ▼
             Text Processor
      (Cleaning + Tokenization +
         Stop-word Removal)
                     │
                     ▼
            Inverted Index
                     │
      ┌──────────────┼──────────────┐
      │              │              │
      ▼              ▼              ▼
 Phrase Search    TF-IDF       Serialization
      │              │              │
      └──────────────┼──────────────┘
                     ▼
              Search Results
```

## Algorithms

### Inverted Index

Each unique word maps to a list of documents in which it appears.

This enables efficient document retrieval without scanning every document for every query.

### Positional Index

Each posting stores:

* Document name
* Term frequency
* Positions of every occurrence

The stored positions make phrase queries such as:

```text
"apple banana"
```

possible.

### Multi-word AND Search

For a query containing multiple words, the engine computes the intersection of posting lists and ranks only the documents containing every query term.

### TF-IDF Ranking

Matching documents are ranked using TF-IDF so that more informative terms contribute more to a document's score than very common words.

### Binary Serialization

The complete index can be written to a binary file (`index.bin`) and loaded again on future executions, avoiding repeated indexing of the document collection.

## Time Complexity

| Operation             | Complexity                             |
| --------------------- | -------------------------------------- |
| Build Index           | O(total words)                         |
| Single-word Search    | O(number of matching documents)        |
| Multi-word AND Search | Depends on posting list intersections  |
| Phrase Search         | Depends on positional list comparisons |
| Save Index            | O(index size)                          |
| Load Index            | O(index size)                          |

## How to Build

Compile using:

```bash
g++ -std=c++17 src/main.cpp src/SearchEngine.cpp src/TextProcessor.cpp src/QueryProcessor.cpp -o search_engine
```

Run:

```bash
./search_engine
```

## Example Queries

Single word:

```text
apple
```

Multi-word:

```text
apple banana
```

Phrase search:

```text
"apple banana"
```

## Future Improvements

* OR and NOT query support
* Top-K result retrieval
* BM25 ranking
* Wildcard search
* Stemming and lemmatization
* Autocomplete using a Trie
* Unit tests
* CMake build system

## Learning Outcomes

Through this project, I gained practical experience with:

* Efficient data structures
* Information Retrieval fundamentals
* Object-oriented software design
* Binary file serialization
* STL containers and algorithms
* Search engine indexing techniques
* Modern C++ programming

## License

This project is intended for educational and learning purposes.
