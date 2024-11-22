#include <iostream>
#include <fstream>
#include <vector>
#include "bmp_utils.hpp"
#include "rotate_clockwise.hpp"
#include "rotate_counterclockwise.hpp"
#include "gaussian_filter.hpp"

void showMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Rotate 90 degrees clockwise\n";
    std::cout << "2. Rotate 90 degrees counterclockwise\n";
    std::cout << "3. Apply Gaussian filter\n";
    std::cout << "4. Save image\n";
    std::cout << "5. Exit\n";
}

int main() {
    std::string filename;
    std::cout << "Enter the name of the input file: ";
    std::cin >> filename;

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    std::vector<RGB> pixels;

    // Pass the pixels vector to readBMP to store the pixel data
    if (!readBMP(file, fileHeader, infoHeader, pixels)) {
        std::cerr << "Error reading BMP file!" << std::endl;
        return 1;
    }
    

    int currentWidth = infoHeader.biWidth;
    int currentHeight = infoHeader.biHeight;

    bool running = true;
    while (running) {
        showMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Rotate 90 degrees clockwise
                pixels = rotate90Clockwise(pixels, currentWidth, currentHeight);
                std::swap(currentWidth, currentHeight);  // Swap width and height after rotation
                std::cout << "Image rotated 90 degrees clockwise.\n";
                break;
            }
            case 2: {
                // Rotate 90 degrees counterclockwise
                pixels = rotate90CounterClockwise(pixels, currentWidth, currentHeight);
                std::swap(currentWidth, currentHeight);  // Swap width and height after rotation
                std::cout << "Image rotated 90 degrees counterclockwise.\n";
                break;
            }
            case 3: {
                // Apply Gaussian filter
                pixels = applyGaussianFilter(pixels, currentWidth, currentHeight);
                std::cout << "Gaussian filter applied.\n";
                break;
            }
            case 4: {
                // Save the image
                std::string outputFilename;
                std::cout << "Enter the name of the output file: ";
                std::cin >> outputFilename;

                std::ofstream outFile(outputFilename, std::ios::binary);
                if (!outFile) {
                    std::cerr << "Error creating output file!" << std::endl;
                    break;
                }

                // Calculate row padding
                int rowPadding = (4 - (currentWidth * 3) % 4) % 4;

                // Update the headers with current width, height, and pixel data size
                infoHeader.biWidth = currentWidth;
                infoHeader.biHeight = currentHeight;
                infoHeader.biSizeImage = (currentWidth * 3 + rowPadding) * abs(currentHeight);
                fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + infoHeader.biSizeImage;

                // Write the headers
                outFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
                outFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

                // Write pixel data row by row, adding padding at the end of each row
                for (int y = 0; y < abs(currentHeight); ++y) {
                    // Write one row of pixel data
                    outFile.write(reinterpret_cast<char*>(&pixels[y * currentWidth]), currentWidth * sizeof(RGB));

                    // Write padding bytes at the end of the row
                    outFile.write("\0\0\0", rowPadding);
                }

                outFile.close();
                std::cout << "Image saved as '" << outputFilename << "'.\n";
                break;
            }
            case 5: {
                // Exit the program
                running = false;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    return 0;
}

