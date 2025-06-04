/**
 * @file im_manipulator.hpp
 * @author Maksim Pastukhov (st131119@student.spbu.ru)
 * @brief Image manipulation functions declarations
 * 
 * Contains declarations for:
 * - Image rotation (rotateImage)
 * - Gaussian filter (applyGaussianFilter)
 * 
 * Defines RotationDirection enum for specifying
 * image rotation direction.
 */

#ifndef IM_MANIPULATOR_HPP
#define IM_MANIPULATOR_HPP

#include "bmp_utils.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
#include <thread>

enum class RotationDirection { Clockwise, CounterClockwise };
void rotateImage(BMPImage& image, RotationDirection direction);

void applyGaussianFilter(BMPImage& image, int kernelSize, float sigma);

#endif // GAUSSIAN_FILTER_HPP

