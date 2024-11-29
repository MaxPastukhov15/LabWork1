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
    auto pixels = image.getPixels();

    // generation for Gauss kernel
    std::vector<std::vector<float>> kernel(kernelSize, std::vector<float>(kernelSize));
    int halfSize = kernelSize / 2;
    float sum = 0.0;

    for (int i = -halfSize; i <= halfSize; ++i) {
        for (int j = -halfSize; j <= halfSize; ++j) {
            kernel[i + halfSize][j + halfSize] = exp(-(i * i + j * j) / (2 * sigma * sigma));
            sum += kernel[i + halfSize][j + halfSize];
        }
    }

    // Normalization of kernel
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j] /= sum;
        }
    }

    // using the filter
    std::vector<RGB> filteredPixels(width * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = 0, g = 0, b = 0;

            for (int ky = -halfSize; ky <= halfSize; ++ky) {
                for (int kx = -halfSize; kx <= halfSize; ++kx) {
                    int nx = x + kx;
                    int ny = y + ky;

                    // checking for bounds
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        const RGB& pixel = pixels[ny * width + nx];
                        float weight = kernel[ky + halfSize][kx + halfSize];

                        r += pixel.r * weight;
                        g += pixel.g * weight;
                        b += pixel.b * weight;
                    }
                }
            }

            filteredPixels[y * width + x] = {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b)};
        }
    }

    // update of  pixels in image
    image.setPixels(filteredPixels);
}



#endif // GAUSSIAN_FILTER_HPP




