# Patent System

## Overview

This project is the lab from my DSA class, a C++ program designed to manage patents and firms base on real-world data, with an emphasis on **encapsulation**, **flexibility**, and **abstract data structures**. The project includes various classes representing patents, firms, and systems of firms, and aims to **support different data structure** implementations (e.g., arrays, linked lists, hash tables) while maintaining a **consistent API** for interacting with patents and firms.

> Note: This is my first C++ project, and I tried to make it more "object-oriented", though I'm uncertain about the quality of the code. (thanks to LLMs, I learned a lot 🤣)

## Design Goals
1. **Data Structure Design & Implementation**: Practice data structure learned in the course, such as linked list, vector.
1. **Abstraction and Encapsulation**: Provide a clear interface for interacting with patents and firms, allowing different data structure implementations to be swapped easily.
2. **Flexibility**: Allow the patent system to be implemented using different underlying data structures, such as linked lists or arrays, providing the ability to choose the best structure based on the use case.

## Features

- **Patent and Firm Management**: Classes for managing patents (`Patent`) and firms (`Firm`) allow for comprehensive tracking and manipulation of patent information, with an overall class (`FirmSystem`) to control the whole patent system.
- **Flexible Data Structures**: Implementation of multiple data structures, such as arrays, linked lists, and hash tables, for both firm and firm system, providing flexibility for optimization based on use cases. (Although `unorder_map` may be the best for the current scenario, for learning purposes, I implemented the classes with as many data structures as possible)
- **Abstract Interfaces**: Abstract base classes are used to ensure that different data structure implementations can be swapped seamlessly while preserving a consistent API.


## Class Overview
- **Patent**: Represents a patent, with information such as patent ID, title, and owner.
- **Firm**: Represents a firm, capable of owning multiple patents. (this is where mainly the data structure is used)
- **FirmSystem**: Manages a collection of firms and their associated patents. (support operations between firms)


## Project Structure

- **Header Files**:
  - `patent.hpp`: Defines the `Patent` class, which represents individual patents.
  - `firm.hpp`: Defines the `Firm` class, representing a firm that owns patents.
  - `firmSys.hpp`: Defines the `FirmSystem` class, responsible for managing a collection of firms.
  - `linked_list_template.hpp`: Defines a linked list template (`SinglyLinkedList`).
  - `vector_template.hpp`: Defines a vector-like template class (`LinearList`).

- **Source Files**:
  - `main.cpp`: Contains the main function and CLI for the patent system

## Getting Started
### Prerequisites
- C++ compiler such as `g++` or `Clang`.
- C++11 or later for compiling the project.
- CMake (version 3.10 or later).

### Compilation
To compile the project using CMake, follow these steps:
1. Create a build directory:
   ```
   mkdir build && cd build
   ```
2. Run CMake to configure the project:
   ```
   cmake ..
   ```
3. Build the project:
   ```
   make
   ```

### Running the Program
Once compiled, run the executable to interact with the patent system:
```
./patent_system
```

## Patent System Walkthrough

### 1. Select Data Structures

When the program starts, you will be prompted to select the data structures to use for managing patents and firms. You can choose between linked lists, vectors, and hash tables for both firm(patents) and firmSystem.
```
Select the Firm Data Structure to use:
1. LinkedList
2. Vector
3. UnorderedMap
Enter choice: 1
Select the Firm System Data Structure to use:
1. Vector
2. UnorderedMap
Enter choice: 1
```

### 2. Patent System Menu

After selecting the data structures, you will see the main menu for the patent system, where you can perform various operations on patents and firms:

```
=====================================
        PATENT SYSTEM MENU          
=====================================
-------------------------------------
           PATENT OPERATIONS           
1. Add Patent to Firm
2. Remove Patent from Firm
3. Transfer Patent between Firms
-------------------------------------
           FIRM OPERATIONS           
4. Display Firm Details
5. Display All Firms Info
6. Add Firm
7. Remove Firm
-------------------------------------
0. Exit
=====================================
Select an option: 
```

## Future Improvements
- **Hash Table Implementation**: Add support for using hash tables to manage patents and firms for optimized searching and insertion. Currently, the project directly uses `std::unordered_map` for the firm system, but it's better to implement a hash table by myself 💪.
- **Improved User Interface**: Create a more user-friendly CLI or even a GUI, WebUI for easier interaction
- **<font color="red">Serialization</font>**: Add functionality to save and load firm and patent data to/from a file for persistence.
- **<font color="red">Performance Metrics</font>**: Implement functionality to measure and display performance metrics for different data structure implementations.
- **Performance Optimization**: Add more data structures and algorithms to improve the performance of the patent system.