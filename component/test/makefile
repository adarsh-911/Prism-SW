# Directories and flags
INCLUDES = -I./ -I../../depends/ -I../../event/
CXX = g++
CXXFLAGS = -std=c++17 $(INCLUDES) -lglfw -lGLEW -lGLU -lGL -lX11
LDFLAGS = -lm

# Source files
aabb_cpp = ../../depends/glm-aabb/AABB.cpp
eventManager_cpp = ../../event/eventManager.cpp
SRC = test.cpp $(aabb_cpp) $(eventManager_cpp)

# Object files
OBJ = test.o aabb.o eventManager.o

# Final executable target
TARGET = test

# Default target: build the final executable
all: $(TARGET)

# Linking step to generate the final executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Rule for compiling test.cpp into test.o
test.o: test.cpp
	$(CXX) -c $(CXXFLAGS) test.cpp -o test.o

# Rule for compiling AABB.cpp into aabb.o
aabb.o: $(aabb_cpp)
	$(CXX) -c $(CXXFLAGS) $(aabb_cpp) -o aabb.o

# Rule for compiling eventManager.cpp into eventManager.o
eventManager.o: $(eventManager.cpp)
	$(CXX) -c $(CXXFLAGS) $(eventManager_cpp) -o eventManager.o

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

