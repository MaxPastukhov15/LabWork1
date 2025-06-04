CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic -Iinclude
TARGET = im_ed
SOURCES = src/main.cpp   src/bmp_utils.cpp src/gaussian_filter.cpp src/rotate_image.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

format:
	astyle -A1 -s4 *.cpp *.hpp
 
