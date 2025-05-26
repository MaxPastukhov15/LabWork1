// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#include <iostream>
#include <fstream>
#include <vector>
#include "bmp_utils.hpp"
#include "rotate_image.hpp"
#include "gaussian_filter.hpp"
#include <chrono>

void showMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Rotate 90 degrees clockwise\n";
    std::cout << "2. Rotate 90 degrees counterclockwise\n";
    std::cout << "3. Apply Gaussian filter\n";
    std::cout << "4. Save image\n";
    std::cout << "5. Exit\n";
}

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
                auto st = std::chrono::high_resolution_clock::now();
                rotateImage(image, RotationDirection::Clockwise);
                auto en = std::chrono::high_resolution_clock::now();
                auto d = std::chrono::duration_cast<std::chrono::microseconds>(en - st);
                std::cout << d.count() << '\n';
                std::cout << "Image rotated 90 degrees clockwise.\n";
                break;
            }
            case 2: {
                // Rotate 90 degrees counterclockwise
                auto st = std::chrono::high_resolution_clock::now();
                rotateImage(image, RotationDirection::CounterClockwise);
                auto en = std::chrono::high_resolution_clock::now();
                auto d = std::chrono::duration_cast<std::chrono::microseconds>(en - st);
                std::cout << d.count() << '\n';
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
		auto st = std::chrono::high_resolution_clock::now();
                applyGaussianFilter(image, kernelSize, sigma);
                auto en = std::chrono::high_resolution_clock::now();
                auto d = std::chrono::duration_cast<std::chrono::microseconds>(en - st);
                std::cout << d.count() << '\n';
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

