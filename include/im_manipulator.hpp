// Maksim Pastukhov B82 mail: st131119@student.spbu.ru
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

