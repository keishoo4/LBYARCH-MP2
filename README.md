# LBYARCH-MP2
Cu, Keisha
Diamante, Deo Zamir

## 1. Project Overview
This project implements a dot product kernel in both:
- **C (scalar implementation)**
- **x86-64 assembly using scalar SIMD instructions**

The kernels are tested with vector sizes \(n = 2^{20}, 2^{24}, 2^{30}\) (reduced if needed for memory limits). Each kernel is run **20 times** to calculate the **average execution time**. Correctness of the assembly kernel is verified against the C kernel.

## 2. Build Configurations

- **Debug**
  - Includes debug symbols
  - Minimal optimization
  - Useful for verifying correctness
- **Release**
  - Fully optimized
  - Used for realistic performance benchmarking

---

## 3. Execution and Results

Each kernel was executed **20 times**, and the average execution time was recorded.
The C version is treated as the reference for correctness checking.

### 3.1 C Kernel

| Vector Size | Avg. Time (Debug) | Avg. Time (Release) | Notes |
|------------|-----------------|-------------------|------|
| 2^20       | 0.00425 s         | 0.0012 s           | Correctness passed |
| 2^24       | 0.0546 s          | 0.0186 s           | Correctness passed |
| 2^30       | 3.50275 s         | 0.9532 s           | Correctness passed |

### 3.2 x86-64 Assembly Kernel

| Vector Size | Avg. Time (Debug) | Avg. Time (Release) | Notes |
|------------|-----------------|-------------------|------|
| 2^20       | 0.00125 s         | 0.00125 s          | Correctness passed |
| 2^24       | 0.01495 s         | 0.0184 s           | Correctness passed |
| 2^30       | 0.95735 s         | 0.9580 s           | Correctness passed |

### Performance Analysis
- The Release configuration runs significantly faster than Debug due to compiler optimizations.
- In Debug mode, the assembly implementation is noticeably faster for larger input sizes.
- In Release mode, the C compiler optimizations reduce the performance gap, making C and Assembly closer in speed.
- x86-64 assembly kernel slightly outperforms C kernel for large vectors because of SIMD scalar floating-point instructions.
- For smaller input sizes, performance differences are minimal due to overhead such as function calls, loop control, and memory handling dominating execution time.

---

## 4. Screenshots

### 4.1 Debug Build Output
![Debug Output](screenshots/debug.png)

### 4.2 Release Build Output
![Release Output](screenshots/release.png)

## 5. Demonstration Video

- Assembly and Main Demo [Video Link Here]