# LabWork 1
## Author
Pastukhov Maksim Germanovich, группа 24.Б82-мм
## Contacts
st131119@student.spbu.ru
## Description
A high-performance BMP image processing tool with multi-threaded operations for:
- 90° clockwise/counter-clockwise rotation
- Gaussian blur filter application

## Key Features
- **Multi-threaded Processing**: Leverages all available CPU cores for optimal performance
- **BMP Format Support**: Handles standard BMP files with 24-bit color depth
- **Modular Architecture**: Clean separation of image processing algorithms
- **Optimized Algorithms**: Efficient implementations for fast operations

## Performance Metrics
| Operation            | Before Optimization | After Optimization | Speedup |
|----------------------|---------------------|--------------------|---------|
| Clockwise Rotation   | 16764 μs            | 5733 μs            | 2.92x   |
| Counter-clockwise    | 7943 μs             | 5365 μs            | 1.48x   |
| Gaussian Filter      | 534054 μs           | 5064 μs            | 105.5x  |

## Requirements
- C++11 compatible compiler
## Build & Run
```bash
make        # Compile the application
./im_ed     # Run the program
make clean  # Clean build artifacts
```
## To watch doxygen documentation(Linux)
```bash

xdg-open docs/html/index.html 
``` 

