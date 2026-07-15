# 🔍 Mini Search Engine

A lightweight search engine built in **C++17** that demonstrates the core principles of **Information Retrieval (IR)**. The project indexes a collection of text documents using an **Inverted Index** with **Positional Postings**, supports **multi-word AND queries**, **exact phrase search**, **TF-IDF ranking**, and **binary serialization** for fast index persistence.

The project was developed to explore how modern search engines efficiently index, rank, and retrieve documents while applying object-oriented design and STL data structures.

## Table of Contents

* [Features](#features)
* [Architecture](#architecture)
* [Project Structure](#project-structure)
* [Algorithms](#algorithms)
* [Time Complexity](#time-complexity)
* [How to Build](#how-to-build)
* [Example Queries](#example-queries)
* [Future Improvements](#future-improvements)
* [Learning Outcomes](#learning-outcomes)

## Features

* Fast document retrieval using an **Inverted Index**
* **Positional Posting Lists** for exact phrase search
* Multi-word **AND** query support
* **TF-IDF** based document ranking
* Text normalization (case folding and punctuation removal)
* Stop-word filtering
* Binary serialization (`index.bin`) for persistent storage
* Binary deserialization for fast startup
* Object-oriented design with modular components
* Implemented entirely in **C++17** using the Standard Template Library (STL)

## Architecture

```text
                    +----------------------+
                    |   Text Documents     |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |   Text Processor     |
                    |----------------------|
                    | • Tokenization       |
                    | • Case Folding       |
                    | • Stop-word Removal  |
                    | • Punctuation Filter |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |   Inverted Index     |
                    |----------------------|
                    | Word -> Posting List |
                    +----------+-----------+
                               |
          +--------------------+--------------------+
          |                                         |
          v                                         v
+----------------------+              +-----------------------+
|  Phrase Search       |              |   TF-IDF Ranking      |
| (Positional Index)   |              |   Score Computation   |
+----------+-----------+              +-----------+-----------+
           |                                          |
           +-------------------+----------------------+
                               |
                               v
                    +----------------------+
                    |   Search Results     |
                    +----------------------+
```

The project first preprocesses all documents to normalize text and remove stop words. An inverted index with positional postings is then constructed. During querying, the engine supports both keyword search and exact phrase search while ranking matching documents using TF-IDF.

## Project Structure

```text
MiniSearchEngine/
│
├── docs/                  # Sample text documents
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
├── README.md
├── .gitignore
└── index.bin              # Serialized index (generated after indexing)
```

## Algorithms

### 1. Inverted Index

The search engine builds an inverted index that maps each unique term to the documents in which it appears. This avoids scanning every document during a search and enables efficient retrieval.

### 2. Positional Posting Lists

Each posting stores:

* Document name
* Term frequency
* Positions of every occurrence

The stored positions enable efficient exact phrase matching by verifying that consecutive query terms appear at adjacent positions within the same document.

### 3. Multi-word AND Search

For queries containing multiple terms, the engine intersects the posting lists of all query terms. Only documents containing every query term are retained, and their relevance scores are accumulated.

### 4. TF-IDF Ranking

Documents are ranked using the TF-IDF (Term Frequency–Inverse Document Frequency) scoring scheme. This assigns higher importance to terms that are frequent in a document but relatively rare across the document collection.

### 5. Binary Serialization

The constructed index is written to a binary file (`index.bin`) and can be loaded in future executions. This significantly reduces startup time by avoiding repeated indexing of the same document collection.

## Time Complexity

| Operation             | Complexity                                                                |
| --------------------- | ------------------------------------------------------------------------- |
| Build Inverted Index  | **O(T)**, where **T** is the total number of words across all documents   |
| Single-word Search    | **O(P)**, where **P** is the size of the posting list                     |
| Multi-word AND Search | **O(P₁ + P₂ + ... + Pₙ)** (posting list intersection)                     |
| Phrase Search         | Depends on the number of positional comparisons within matching documents |
| Save Index            | **O(Index Size)**                                                         |
| Load Index            | **O(Index Size)**                                                         |
| TF-IDF Ranking        | **O(R)**, where **R** is the number of matching documents                 |

## How to Build

Compile the project using a C++17 compatible compiler.

```bash
g++ -std=c++17 src/main.cpp src/SearchEngine.cpp src/TextProcessor.cpp src/QueryProcessor.cpp -o search_engine
```

Run the executable:

```bash
./search_engine
```

## Example Queries

### Single-word Search

```text
apple
```

### Multi-word AND Search

```text
apple banana
```

Returns only documents containing **both** words.

### Phrase Search

```text
"apple banana"
```

Returns only documents where the exact phrase appears.

### Sample Output

```text
Enter search query:
apple banana

Search Results:
doc4.txt (4.53)
doc1.txt (2.98)
doc2.txt (1.75)
```

## Future Improvements

* OR and NOT query support
* Wildcard search
* Autocomplete using a Trie
* Stemming and lemmatization
* BM25 ranking
* Query suggestions
* Unit testing
* Configurable stop-word dictionary
* Web-based user interface
* CMake-based build system

## Learning Outcomes

This project strengthened my understanding of:

* Information Retrieval fundamentals
* Inverted and positional indexing
* TF-IDF ranking
* Efficient use of STL containers
* Binary file serialization
* Object-oriented software design
* C++17 programming
* Algorithm analysis and optimization
* Modular software development
  
## Screenshots

### Single-word Search

![Single Word Search](docs/screenshots/single_search.png)

### Phrase Search

![Phrase Search](docs/screenshots/phrase_search.png)
