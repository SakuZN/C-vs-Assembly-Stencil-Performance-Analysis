# Introduction
This project investigates the performance differences between C and x86-64 assembly language implementations of a 1-dimensional stencil operation. 
The C function serves as a baseline, while the assembly version demonstrates performance optimization using vector instructions.
<br><br>
This <b>README</b> provides a detailed analysis of the program and the performance differences of the function implementations.

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
$\ Vector X$  is assigned with random double-precision floating-point values. This is then copied to $\ Vector X_{asm}$, which holds values for the assembly function to read from.

# 1-D Stencil Operation Implementation
| C Function             | Assembly Function      |
| ---------------------- | ---------------------- |
|![c function](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/d496d77b-747d-4204-9381-e08b82c3e6ac)|![assembly func](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/f9030ba0-56d5-4d61-a4bb-b178dc74f74c)

Both the C and assembly functions implement a 1-dimensional stencil operation. This operation iterates through a $\ Vector X$  and calculates a new value for each element in the output $\ Vector Y$.<br> <br> 
The calculation involves summing the current element ($\ X[i]$) with its 3 predecessors ($\ X[i - 3]$, $\ X[i - 2]$, $\ X[i - 1]$) <br> 
and 3 successors ($\ X[i + 3]$, $\ X[i + 2]$, $\ X[i + 1]$).

## C Function Algorithm Breakdown
- 1. <b>Setup</b>: The function takes three arguments: $\ Vector X$, $\ Vector Y$ (output array), and size (size of $\ Vector X$).
  
- 2. <b>Initialization</b>: It calculates the limit as $\ size - 3$ to avoid out-of-bounds access. It initializes $\ y_{Index}$ to $\ 0$ to keep track of the current index in the output array.
     
- 3. <b>Loop</b>: The function iterates over the input array from the fourth element to the limit element. In each iteration, it calculates the sum of the current element and its three predecessors and successors, and stores the result in the output array at the $\ y_{Index}$ position and increment it after.
  
- 4. <b>End</b>: End after reaching the limit.
<br>
This function is a straightforward implementation of a 1D stencil operation in C. It uses a single loop to iterate over the input array and perform the stencil operation, which involves adding up a certain number of neighboring elements for each element in the array. This function's time complexity is $\ O(n)$,
where $\ n$  is the size of the input array. This is because it performs a constant amount of work for each element in the array. The function does not use any advanced C features or optimizations, so its performance is determined mainly by the CPU speed and the C compiler's efficiency.

## Assembly Function Algorithm Breakdown
- 1. <b>Setup</b>:  The function begins by pushing the registers $\  RSI, RBX, R12, R13, RBP$ onto the stack to save their original values. It then sets up the stack frame by moving the stack pointer $\ RSP$ into the base pointer $\ RBP$, and adding 48 to $\ RBP$ to account for the space used by the pushed registers.
  
- 2. <b>Initialization</b>: The function initializes several registers to zero $\ (RAX, RBX, R13, R12, R11, R10) $. It calculates the limit as $\ size - 3$ $\ 
 (R10 = R8 - 3)$ to avoid out-of-bounds access. It sets up pointers to the input and output arrays $\ (RSI = RCX, R13 = RDX)$.

- 3. <b>Loop</b>: The function enters a loop that continues until the loop counter $\ RBX$ equals the limit $\ R10$. In each iteration, it uses the SIMD instruction $\ addsd$ to add double-precision floating-point values from the input array, and stores the result in the output array at the current index. It increments the output array index $\ R11$ and the loop counter $\ RBX$ after each iteration.

- 4. <b>End</b>: If the function was successful, it sets $\ RAX$ to 1. It then pops the original values of $\ RBP, R13, R12, RBX, RSI$ off the stack to restore their original values. Finally, it returns from the function.
<br>
(Add Explanation Here)

# Sanity Check
| Code Implementation    | Code Output            |
| ---------------------- | ---------------------- |
|![sanity check](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/2038c977-0679-4801-9de4-a42aff8694c2)|![sanity check output](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/6efe9d14-db07-4fb6-9991-15f6594537da)

The program includes a correctness check by comparing the output of the assembly implementation to the C implementation. If the outputs don't match, the program terminates, signaling a potential implementation error or a fatal issue (e.g., stack misalignment) in the assembly function. This is an important part of the program as it ensures consistency and fairness of function comparison.

# Performance Testing
## Methodology
Both the C and assembly functions are benchmarked in debug and release modes (run via Visual Studio). Execution times are measured for vector sizes of $\ 2^{20}$, $\ 2^{24}$, and $\ 2^{28}$. Each test executes 50 times to obtain average runtimes.

## Input size $\ 2^{20}$ Test
### Debug Mode
| Program Run            | Program Output           |
| ---------------------- | ---------------------- |
|![2^20 debug](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/fcd964be-d995-4900-861e-77c61133ca5b)|![2^20 debug output](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/70fc21a7-e5c5-43d9-a1aa-975ce830302b)

The table shows the execution times of a 1-D stencil operation implemented in C and Assembly, performed on a vector of size $\ 2^{20}$ (1,048,576) over 50 iterations. The C implementation has an average time of $\ 0.00468(s)$, with slight variations around $\ 0.005(s)$. On the other hand, the Assembly implementation consistently outperforms the C version with an average time of $\ 0.0015(s)$, showing times around $\ 0.001(s)$ to $\ 0.002(s)$. This test was conducted in Debug mode, where compiler optimizations are turned off. The performance difference might decrease or even reverse in Release mode due to compiler optimizations.

### Release Mode
| Program Run            | Program Output           |
| ---------------------- | ---------------------- |
|![2^20 release](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/88027682-8b1e-4f23-8cd6-c649b5d45662)|![2^20 release output](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/39f54dd5-4262-481a-a6e1-0eb2519cce2c)

The C implementation has an average time of $\ 0.00146(s)$, showing a significant improvement over the Debug mode due to compiler optimizations. The Assembly implementation maintains consistent performance with an average time of $\ 0.00152(s)$, slightly slower than the C version in this case. This demonstrates the power of compiler optimizations in Release mode, which can sometimes result in high-level language implementations outperforming hand-optimized Assembly code.

## Input size $\ 2^{24}$ Test
### Debug Mode
| Program Run            | Program Output           |
| ---------------------- | ---------------------- |
|![2^24 debug](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/0c84f2c3-485a-4849-ae09-a98caedd18cb)|![2^24 debug output](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/eae058e5-642c-4cb5-90e2-0dbe8374c112)


The table shows the execution times of a 1-D stencil operation implemented in C and Assembly, performed on a vector of size $\ 2^{24}$ (16,777,216) over 50 iterations. The C implementation has an average time of $\ 0.074620(s)$ while the Assembly implementation maintains a faster average time of $\ 0.024100(s)$. Like the debug test for the smaller size, the c implementation is slower than the assembly function. This is apparent with the now huge gap between their average times.

### Release Mode
| Program Run            | Program Output           |
| ---------------------- | ---------------------- |
|![2^24 release](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/8ec89e48-5a53-4442-966f-13da55eab7f6)|![2^24 release output](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/a9a7d5cd-c2d4-4ea7-ba4c-215642ff4d48)


The C implementation has an average time of $\ 0.022880(s)$. Like the previous test, there is a significant improvement over the Debug mode due to compiler optimizations. The Assembly implementation maintains consistent performance with an average time of $\ 0.024600(s)$, slightly slower than the C version in this case.

## Input size $\ 2^{28}$ Test
### Debug Mode
| Program Run            | Program Output           |
| ---------------------- | ---------------------- |
|![2^28 debug](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/7427ebf2-c5f2-4a4a-850b-22655e6cacaa)|![2^28 debug output](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/1eb3aa23-4c97-4c54-88a1-68218dae3c70)

The table shows the execution times of a 1D stencil operation implemented in C and Assembly, performed on a vector of size $\ 2^{28}$ (268,435,456) over 50 iterations in Debug mode. The C implementation has an average time of $\ 1.212640(s)$, while the Assembly implementation has an average time of $\ 0.389920(s)$. Compared to the previous test with a vector size of $\ 2^{24}$, the gap between the average times of C and Assembly has increased significantly, making Assembly's efficiency more pronounced.

### Release Mode
| Program Run            | Program Output           |
| ---------------------- | ---------------------- |
|![2^28 release](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/5c064728-166b-489d-a2d9-99777f3cb969)|![2^28 release output](https://github.com/SakuZN/C-vs-Assembly-Stencil-Performance-Analysis/assets/106810417/9fa1cf57-af7b-422e-aa64-140480831cf2)


The C implementation has an average time of $\ 0.368360(s)$, showing a substantial improvement over the Debug mode due to compiler optimizations. The Assembly implementation maintains consistent performance with an average time of $\ 0.390240(s)$, also slightly slower than the C version in this case. This is impressive considering the average time difference of the test in debug mode, showcasing the power of modern compilers and their optimizations.

# Conclusion

Based on the analysis of the execution times for the 1D stencil operation implemented in C and Assembly, it can be concluded that both languages have their strengths and use cases.


In scenarios where raw performance and consistent execution across debug and release modes are paramount, especially with large datasets, assembly is the better choice. This is due to its low-level nature, allowing for fine-grained optimizations that often outpace compiler-generated code. However, modern compilers today are very sophisticated, and our release mode tests illustrate this. Compiler optimizations significantly boosted C's performance, often matching or even exceeding that of the handcrafted assembly implementation.

Still, Assembly remains a powerful tool for performance-critical scenarios in system software, game development, or real-time applications where absolute control is essential.  However, its complexity, potential portability issues, and less intuitive debugging make it less suitable for general-purpose programming tasks.  


C, and other high-level languages offer a compelling balance of performance, readability, and development speed for most applications.  If complex algorithms are used within a project, and the utmost performance is desired, Assembly can be selectively used to optimize hotspots, as seen in our tests.  With ever-improving compilers, the performance gap between high-level languages and assembly is narrowing. Therefore, choosing between C and Assembly necessitates carefully considering development time, code maintainability, portability, and the performance demands of the project.

