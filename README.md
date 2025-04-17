<div align="center">

# RB-Tree

## Algorithms & Data Structures III Project

</div>

## Description

This project implements a Red-Black Tree in C, a self-balancing binary search tree. The implementation is based on the book **"Introduction to Algorithms"** by Cormen, Leiserson, Rivest, and Stein.

The project is divided into three main files:
- `Functions.h`: Contains the function declarations and data structures.
- `Functions.c`: Implements the functions defined in the header file.
- `Main.c`: The main program that demonstrates the usage of the Red-Black Tree.

## Features

- Insertion of nodes into the Red-Black Tree.
- Deletion of nodes while maintaining tree properties.
- Search for specific keys in the tree.
- Printing the tree structure.

## How to Run

To compile the project, use the following command:

```bash
make
```

To execute the program, use:

```bash
./myrb < input_file > output_file
```
Replace `input_file` with the name of your input file and `output_file` with the desired output file.

Example:

Input (`test.in`):

```bash
i 4
i 6
i 1
i 2
i 7
i 3
i 5
i 8
r 8
```
Output (`test.out`):

```bash
                4(P)

           /             \

       2 (P)               6 (V)

      /       \           /     \

1 (V)       3 (V)      5 (P)    7 (P)
```

Or, as a list of nodes:

```bash
1,2,1
2,1,0
3,2,1
4,0,0
5,2,0
6,1,1
7,2,0
```

Compare the generated output file (test.out) with the expected output file (test.sol) using the diff command:

```bash
diff test.sol test.out
```
If the diff command does not return anything, it means the test was successful.



## Students: Nathan Endo, Nicolas Cosenza

## Institute: UFPR (Universidade Federal do Paraná)

## Lecturer: Dr. Eduardo Cunha de Almeida
