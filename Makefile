# Makefile for Image Editor and Tests
CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic -Iinclude 
TARGET = im_ed
TEST_TARGET = im_ed_tests

# Source files
SOURCES = src/main.cpp src/bmp_utils.cpp src/gaussian_filter.cpp src/rotate_image.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Test files
TEST_SOURCES = tests/test.cpp src/bmp_utils.cpp src/gaussian_filter.cpp src/rotate_image.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Main program build
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Test program build
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS) -lgtest -lgtest_main -lpthread

# Build rule for .cpp files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test target - builds and runs tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_OBJECTS) $(TEST_TARGET)

# Format code
format:
	astyle -A1 -s4 *.cpp *.hpp

.PHONY: all clean test format
