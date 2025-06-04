#include "gtest/gtest.h"
#include "bmp_utils.hpp"
#include "im_manipulator.hpp"
#include <fstream>
#include <cstdio>

// Helper function to create a simple test BMP file
void createTestBMP(const std::string& filename, int width, int height, const std::vector<RGB>& pixels) {
    std::ofstream file(filename, std::ios::binary);
    
    // File header
    BMPFileHeader fh;
    fh.bfType = 0x4D42;
    fh.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + width * height * sizeof(RGB);
    fh.bfReserved1 = 0;
    fh.bfReserved2 = 0;
    fh.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    file.write(reinterpret_cast<char*>(&fh), sizeof(fh));
    
    // Info header
    BMPInfoHeader ih;
    ih.biSize = sizeof(BMPInfoHeader);
    ih.biWidth = width;
    ih.biHeight = height;
    ih.biPlanes = 1;
    ih.biBitCount = 24;
    ih.biCompression = 0;
    ih.biSizeImage = width * height * sizeof(RGB);
    ih.biXPelsPerMeter = 0;
    ih.biYPelsPerMeter = 0;
    ih.biClrUsed = 0;
    ih.biClrImportant = 0;
    file.write(reinterpret_cast<char*>(&ih), sizeof(ih));
    
    // Pixel data
    file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(RGB));
    file.close();
}

class ImageEditorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a 3x3 test image
        testPixels = {
            {255, 0, 0}, {0, 255, 0}, {0, 0, 255},
            {255, 255, 255}, {0, 0, 0}, {0, 255, 255},
            {255, 255, 0}, {255, 0, 255}, {0, 0, 255}
        };
        createTestBMP("test.bmp", 3, 3, testPixels);
    }
    
    void TearDown() override {
        std::remove("test.bmp");
        std::remove("output.bmp");
    }
    
    std::vector<RGB> testPixels;
};



TEST_F(ImageEditorTest, BMPReadInvalidFile) {
    BMPImage image;
    EXPECT_FALSE(image.read("nonexistent.bmp"));
}

TEST_F(ImageEditorTest, BMPSaveFile) {
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    image.save("output.bmp");
    
    // Verify the saved file
    BMPImage savedImage;
    EXPECT_TRUE(savedImage.read("output.bmp"));
    EXPECT_EQ(savedImage.getWidth(), 3);
    EXPECT_EQ(savedImage.getHeight(), 3);
}

TEST_F(ImageEditorTest, BMPSetDimensions) {
    BMPImage image;
    image.setDimensions(4, 2);
    EXPECT_EQ(image.getWidth(), 4);
    EXPECT_EQ(image.getHeight(), 2);
    
    EXPECT_THROW(image.setDimensions(-1, 5), std::invalid_argument);
}

// Rotation Tests
TEST_F(ImageEditorTest, RotateClockwise) {
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    
    rotateImage(image, RotationDirection::Clockwise);
    
    // Check dimensions
    EXPECT_EQ(image.getWidth(), 3);
    EXPECT_EQ(image.getHeight(), 3);
    
    // Check pixel positions
    // Original top-left (255,0,0) should now be bottom-left
    RGB pixel = image.getPixel(0, 2);
    EXPECT_EQ(pixel.r, 255);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 0);
}

TEST_F(ImageEditorTest, RotateCounterClockwise) {
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    
    rotateImage(image, RotationDirection::CounterClockwise);
    
    // Original top-left (255,0,0) should now be top-right
    RGB pixel = image.getPixel(2, 0);
    EXPECT_EQ(pixel.r, 255);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 0);
}

TEST_F(ImageEditorTest, DoubleRotationIdentity) {
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    BMPImage original = image;
    
    rotateImage(image, RotationDirection::Clockwise);
    rotateImage(image, RotationDirection::CounterClockwise);
    
    // Should be back to original
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            EXPECT_EQ(image.getPixel(x, y).r, original.getPixel(x, y).r);
            EXPECT_EQ(image.getPixel(x, y).g, original.getPixel(x, y).g);
            EXPECT_EQ(image.getPixel(x, y).b, original.getPixel(x, y).b);
        }
    }
}

// Gaussian Filter Tests
TEST_F(ImageEditorTest, GaussianFilterSmallKernel) {
    BMPImage image;
    image.setDimensions(5, 5);
    image.setPixel(2, 2, {255, 255, 255}); // White center
    
    applyGaussianFilter(image, 3, 1.0f);
    
    // Center should still be brightest
    RGB center = image.getPixel(2, 2);
    RGB edge = image.getPixel(0, 0);
    EXPECT_GT(center.r, edge.r);
}

TEST_F(ImageEditorTest, GaussianFilterLargeSigma) {
    BMPImage image;
    image.setDimensions(5, 5);
    image.setPixel(2, 2, {255, 255, 255}); // White center
    
    applyGaussianFilter(image, 5, 5.0f);
    
    // With large sigma, the center won't be as bright
    RGB center = image.getPixel(2, 2);
    EXPECT_LT(center.r, 100);
}

// Integration Tests
TEST_F(ImageEditorTest, RotateThenFilter) {
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    
    rotateImage(image, RotationDirection::Clockwise);
    applyGaussianFilter(image, 3, 1.0f);
    
    // Just verify the operation completed without errors
    EXPECT_EQ(image.getWidth(), 3);
    EXPECT_EQ(image.getHeight(), 3);
}

TEST_F(ImageEditorTest, FilterThenRotateThenSave) {
    BMPImage image;
    ASSERT_TRUE(image.read("test.bmp"));
    
    applyGaussianFilter(image, 3, 1.0f);
    rotateImage(image, RotationDirection::CounterClockwise);
    image.save("output.bmp");
    
    // Verify the saved file
    BMPImage savedImage;
    EXPECT_TRUE(savedImage.read("output.bmp"));
    EXPECT_EQ(savedImage.getWidth(), 3);
    EXPECT_EQ(savedImage.getHeight(), 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
