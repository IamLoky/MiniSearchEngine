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
