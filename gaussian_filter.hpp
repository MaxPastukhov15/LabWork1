// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
#ifndef GAUSSIAN_FILTER_HPP
#define GAUSSIAN_FILTER_HPP

#include "bmp_utils.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

void applyGaussianFilter(BMPImage& image, int kernelSize, float sigma) {
    int width = image.getWidth();
    int height = image.getHeight();

    // Gaussian kernel generation
    std::vector<std::vector<float>> kernel(kernelSize, std::vector<float>(kernelSize));
    int halfSize = kernelSize / 2;
    float sum = 0.0;

    for (int i = -halfSize; i <= halfSize; ++i) {
        for (int j = -halfSize; j <= halfSize; ++j) {
            kernel[i + halfSize][j + halfSize] = exp(-(i * i + j * j) / (2 * sigma * sigma));
            sum += kernel[i + halfSize][j + halfSize];
        }
    }

    // Kernel normalization
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j] /= sum;
        }
    }

    // Filter applying
    std::vector<RGB> filteredPixels(width * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float red = 0.0f;
            float green = 0.0f;
            float blue = 0.0f;

            // Apply the Gaussian kernel
            for (int ky = -halfSize; ky <= halfSize; ++ky) {
                for (int kx = -halfSize; kx <= halfSize; ++kx) {
                    int nx = std::clamp(x + kx, 0, width - 1);
                    int ny = std::clamp(y + ky, 0, height - 1);

                    float weight = kernel[ky + halfSize][kx + halfSize];
                    const RGB& neighbor = image.getPixel(nx, ny);

                    red += neighbor.r * weight;
                    green += neighbor.g * weight;
                    blue += neighbor.b * weight;
                }
            }

            // Clamp and store the filtered values
            RGB& outputPixel = filteredPixels[y * width + x];
            outputPixel.r = static_cast<uint8_t>(std::clamp(red, 0.0f, 255.0f));
            outputPixel.g = static_cast<uint8_t>(std::clamp(green, 0.0f, 255.0f));
            outputPixel.b = static_cast<uint8_t>(std::clamp(blue, 0.0f, 255.0f));
        }
    }

    // Image pixel update
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            image.setPixel(x, y, filteredPixels[y * width + x]);
        }
    }
}

#endif // GAUSSIAN_FILTER_HPP

