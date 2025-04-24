
# 🧵🔢 Multithreaded Sorting Application

This project, is a C based application that implements multithreaded Merge Sort. In this application, first user enter 10 numbers and then it stores in an array. Then, the array is divided into halves, sorted in parallel using threads, and finally merges into a sorted array. 


## 🚀 Features

- **Multithreaded Sorting**: 
    - 2 threads sort first half and second half of the array in parallel: which is multithreading.
    - after these 2 threads, the third thread merges 2 halves in a sorted array. 
    - Finally, the parent thread( which is the main function in C), prints the sorted array. 
- **Merge Sort**: Efficiently sort two halves with Merge Sort algorithm
- **Dynamic Memory Management**: Uses ```malloc``` and ```free``` to allocate and manage memory for sorting and merging.


## 🛠️ How It Works

- **Input**: The program prompts the user to input 10 integers.
- **Split**: The unsorted array is divided into two halves.
- **Sort**: Two threads sort each half of the array in parallel( if your system has one core, then it will be concurrently) using the merge sort algorithm.
- **Merge**: A third thread merges the two sorted halves into a final sorted array.
- **Output**: The program prints the final sorted array.
## 🔧 Getting Started

### Prerequisites
+ C Compiler (e.g., GCC)
+ pthread Library for multithreading support (usually available by default)
