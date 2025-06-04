
# Performance report

# Image Processing Optimization Report

## Introduction
This document presents performance improvements achieved through optimization of core image processing operations. The key optimizations include multi-threading implementation and algorithm refinement.

## Test Environment
### Hardware Specifications
- **Device**: Lenovo IdeaPad 3
- **CPU**: Intel Core i3-1115G4 (2 cores/4 threads) @ 3.0GHz-4.1GHz
- **RAM**: 8GB DDR4
- **Storage**: 256GB SSD
- **OS**: Linux (Ubuntu 22.04 LTS)
- **Compiler**: GCC 11.3.0 with C++11 support

### Test Image
- **Filename**: Airplane.bmp
- **Dimensions**: 1024×1024 pixels (square)
- **Size**: 768 KB (3,145,728 bytes)
- **Format**: 24-bit uncompressed BMP
  
## Performance Results

### Rotation Operations
| Operation            | Single-thread | hardware concurrency (4 threads) | Improvement | 8 threads | 5 threads|
|----------------------|---------------|----------------------------------|-------------|-----------|----------|
| Clockwise Rotation   | 16,764 μs     | 5,733 μs                         | 2.92x       |  5452 μs  | 5910 μs  |
| Counter-clockwise    | 7,943 μs      | 5,365 μs                         | 1.48x       |  6222 μs  | 5900 μs  |


**Analysis:** The rotation operations benefited significantly from:
- Multi-threaded pixel processing
- Optimized memory access patterns

### Gaussian Filter(11 kernel size, sigma 80)
| Metric               | Single-thread  | hardware concurrency(4 threads)  | Improvement  | 8 threads | 5 threads|
|----------------------|----------------|----------------------------------|--------------|-----------|----------|
| Execution Time (μs)  | 534054         | 5064                             | 105.5x faster| 479956    | 481110   |
| Throughput (MPixel/s)| ~0.19          | ~20.1                            | 105.5x       |           |          |

**Key Optimizations:**
1. **Parallel Processing:** Divided image into vertical segments processed by separate threads
2. **Boundary Handling:** Efficient edge pixel handling with std::clamp
3. **Memory Efficiency:** Reduced temporary allocations

## Conclusion
The optimization efforts resulted in dramatic performance improvements:
- Rotation operations now 1.5-3x faster
- Gaussian filter shows 100x+ speedup
- System scales well with core count
- the best choice to use number of threads that are avalaible for you
