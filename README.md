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


Because C does not support dynamically assigned array size using variables. The use of malloc is needed to allocate the size of $\ Vector X$ and $\ Vector Y$ dynamically.
 However malloc still comes with its constraints, that is it is ultimately limited by the current user's available RAM or system memory.
 Thus, the allocation of very large blocks of memory could lead to allocation failures. As seen in the figure above, $\ 2^30$ size allocation crashes the program.
 While the limitation can vary depending on the specifciations of the computer, the maximum size the test was conducted is $\ 2^28$
