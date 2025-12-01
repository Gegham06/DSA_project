# Data_structures

Here you can see what data structures this repository contains 
### 1\. `C-Vector`: A Dynamic Array Library

# Project Title: `C-Vector` - A Generic Dynamic Array Library

## Overview

C++ has `std::vector`, a powerful tool for managing dynamic arrays. C arrays, however, are fixed in size. This project is about creating `C-Vector`, a library that provides a generic, type-safe dynamic array (vector) implementation in C. The library will manage its own memory, growing as needed when new elements are added.

## Core Features

  - Create and destroy a vector.
  - Get the current size and capacity of the vector.
  - Add an element to the end (`push_back`).
  - Remove an element from the end (`pop_back`).
  - Get or set the element at a specific index.
  - Automatically resize (grow) the internal array when its capacity is reached.

## Demo Application Idea

A command-line program that reads an unknown number of integers from the user, stores them in a `C-Vector`, and then prints them out along with the final size and capacity of the vector.

## Key Learning Concepts

  - **Dynamic Memory Management**: `malloc`, `realloc`, `free`.
  - **Amortized Analysis**: Understanding the performance of resizing.
  - **Generic Programming in C**: Using `void*` and `memcpy` to handle any data type.
  - **API Design**: Creating a clean and reusable interface.

-----

Of course\! Here are two additional project ideas focusing on the stack and queue data structures, following the same format.

-----

### 2\. `C-HashMap`: A Hash Map Library

# Project Title: `C-HashMap` - A Key-Value Hash Map Library

## Overview

Many modern languages have built-in dictionaries or hash maps. This project involves building a hash map in C to store key-value pairs. Your library should handle string keys and `void*` values, allowing it to store any type of data. It must efficiently handle hash collisions.

## Core Features

  - Create and destroy a hash map.
  - Insert a key-value pair.
  - Retrieve a value given a key.
  - Delete a key-value pair.
  - Check if a key exists.
  - Implement a string hashing function (e.g., djb2).
  - Handle collisions using **chaining** (linked lists at each bucket).

## Demo Application Idea

A word frequency counter. The demo program should read a text file, use the `C-HashMap` library to store each unique word as a key and its frequency count as the value, and then print the results.

## Key Learning Concepts

  - **Hashing**: Designing hash functions and handling collisions.
  - **Data Structures**: Combining arrays and linked lists.
  - **Pointer Management**: Managing memory for keys, values, and nodes.
  - **API Encapsulation**: Hiding implementation details from the user.

-----
