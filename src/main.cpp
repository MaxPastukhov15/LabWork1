/**
 * @file main.cpp
 * @author Maksim Pastukhov (st131119@student.spbu.ru)
 * @brief Main program for BMP image processing.
 * 
 * Provides a command-line interface for loading, manipulating, and saving BMP images.
 * Supported operations include rotation and Gaussian blur filtering.
 */

/**
 * @brief Displays the main menu options.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include "bmp_utils.hpp"
#include "im_manipulator.hpp"
#include <chrono>

void showMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Rotate 90 degrees clockwise\n";
    std::cout << "2. Rotate 90 degrees counterclockwise\n";
    std::cout << "3. Apply Gaussian filter\n";
    std::cout << "4. Save image\n";
    std::cout << "5. Exit\n";
}

/**
 * @brief Main function for the BMP image processing application.
 * 
 * @return int Exit status (0 for success, 1 for error).
 * 
 * The function:
 * 1. Prompts the user for an input BMP filename.
 * 2. Reads the image file.
 * 3. Displays a menu for image manipulation options.
 * 4. Processes user choices until exit is selected.
 */

int main() {
    BMPImage image;

    std::string filename;
    std::cout << "Enter the name of the input file: ";
    std::cin >> filename;

    if (!image.read(filename)) {
        std::cerr << "Error reading BMP file!" << std::endl;
        return 1;
    }

    bool running = true;
    while (running) {
        showMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Rotate 90 degrees clockwise
                rotateImage(image, RotationDirection::Clockwise);
                std::cout << "Image rotated 90 degrees clockwise.\n";
                break;
            }
            case 2: {
                // Rotate 90 degrees counterclockwise
                rotateImage(image, RotationDirection::CounterClockwise);
                std::cout << "Image rotated 90 degrees counterclockwise.\n";
                break;
            }
            case 3: {
                // Apply Gaussian filter
                int kernelSize;
                float sigma;

                std::cout << "Enter kernel size (odd number): ";
                std::cin >> kernelSize;

                if (kernelSize % 2 == 0) {
                    std::cout << "Kernel size must be an odd number. Try again.\n";
                    break;
                }

                std::cout << "Enter sigma (standard deviation): ";
                std::cin >> sigma;

                applyGaussianFilter(image, kernelSize, sigma);
		
                std::cout << "Gaussian filter applied.\n";
                break;
            }
            case 4: {
                // Save the image
                std::string outputFilename;
                std::cout << "Enter the name of the output file: ";
                std::cin >> outputFilename;

                image.save(outputFilename);
                std::cout << "Image saved as " << outputFilename << ".\n";
                break;
            }
            case 5: {
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

