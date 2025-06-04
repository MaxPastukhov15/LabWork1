/**
 * @file im_manipulator.hpp
 * @author Maksim Pastukhov (st131119@student.spbu.ru)
 * @brief Image manipulation functions declarations.
 */

#ifndef IM_MANIPULATOR_HPP
#define IM_MANIPULATOR_HPP

#include "bmp_utils.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
#include <thread>

/**
 * @enum RotationDirection
 * @brief Specifies the direction of image rotation.
 */
enum class RotationDirection { Clockwise, CounterClockwise };
/**
 * @brief Rotates a BMP image by 90 degrees in the specified direction.
 * 
 * @param image The BMPImage to rotate.
 * @param direction The rotation direction (Clockwise or CounterClockwise).
 */
void rotateImage(BMPImage& image, RotationDirection direction);

/**
 * @brief Applies a Gaussian blur filter to a BMP image.
 * 
 * @param image The BMPImage to filter.
 * @param kernelSize The size of the kernel (must be odd).
 * @param sigma The standard deviation for the Gaussian function.
 */
void applyGaussianFilter(BMPImage& image, int kernelSize, float sigma);

#endif // GAUSSIAN_FILTER_HPP

