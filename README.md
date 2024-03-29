# Introduction
This project investigates the performance differences between C and x86-64 assembly language implementations of a 1-dimensional stencil operation. 
The C function serves as a baseline, while the assembly version demonstrates performance optimization using vector instructions.

# x86-to-C Interface Program
| Input                  | Output             |
| ---------------------- | ---------------------- |
| ![input](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/0d94e286-bdb1-4f28-bdd6-f102dfae8292)| ![output](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/05a9eecb-67c8-46ec-a318-b4e6e975dcfb)

The x86-to-C interface program accepts an input n that is size $\ 2^n$ and also a question if the program was run in debug mode or release mode.
This is because the program's output is a CSV file that contains the time it took for the function in c and the assembly for each iteration.
It also shows the average of the entire iteration for a more straightforward analysis comparison of time for both functions.

# Vector Size Allocation
| Malloc use             | Limitation             |
| ---------------------- | ---------------------- |
|![malloc](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/fa093b71-ffc3-4b91-a045-26c738dc39bd)|![Limitations](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/78aa4c8e-cbb2-4b89-b8f1-db95d0bec0e9)


Because C does not support dynamically assigned array size using variables, the use of malloc is needed to allocate the size of $\ Vector X$ and $\ Vector Y$ dynamically.
However, malloc still comes with its constraints, which are ultimately limited by the current user's available RAM or system memory.
Thus, allocating huge blocks of memory could lead to allocation failures. The figure above shows that $\ 2^{30}$ size allocation crashes the program.
While the limitation can vary depending on the specifications of the computer, the maximum size the test was conducted is $\ 2^{28}$.

# Random Value Assignment
| Vector X value assignment |
| ---------------------- |
|![rand val assignment](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/c71dd3e0-fb98-4c95-b236-fe88a9a6e4ca)
$\ Vector X$  is assigned with random double-precision floating-point values. This is then copied to $\ Vector X_{asm}$ which holds values for the assembly function to read from.

# 1-D Stencil Operation Implementation
| C Function             | Assembly Function      |
| ---------------------- | ---------------------- |
|![c function](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/d496d77b-747d-4204-9381-e08b82c3e6ac)|![assembly func](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/f9030ba0-56d5-4d61-a4bb-b178dc74f74c)

Both the C and assembly functions implement a 1-dimensional stencil operation. This operation iterates through a $\ Vector X$  and calculates a new value for each element in the output $\ Vector Y$.<br> <br> 
The calculation involves summing the current element ($\ X[i]$) with its 3 predecessors ($\ X[i - 3]$, $\ X[i - 2]$, $\ X[i - 1]$) <br> 
and 3 successors ($\ X[i + 3]$, $\ X[i + 2]$, $\ X[i + 1]$).
