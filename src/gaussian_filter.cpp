// Maksim Pastukhov B82 mail: st131119@student.spbu.ru

#include "bmp_utils.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
#include <thread>

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
    const unsigned int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
     
    auto process_segment = [&](int start_y, int end_y){
    	for (int y = start_y; y < end_y; ++y) {
        	for (int x = 0; x < width; ++x) {
        	    float red = 0.0f, green = 0.0f, blue = 0.0f;

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
    };
    
    int rows_per_thread = height / num_threads;
    for (unsigned int i = 0; i < num_threads; ++i){
    	int start_y = i * rows_per_thread;
    	int end_y = (i == num_threads - 1) ? height : (i + 1) * rows_per_thread;
    	threads.emplace_back(process_segment, start_y , end_y);
    }
    
    for (auto& thread : threads) thread.join();
	
    // Image pixel update
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            image.setPixel(x, y, filteredPixels[y * width + x]);
        }
    }
}

