# Define the compiler.
CXX = g++

# Define the compiler flags.
CXXFLAGS = -Wall -std=c++17

# Define the target executable.
TARGET = hw4

# Define the source files.
SRCS = hw4.cpp

#Define the object files.
OBJS = $(SRCS:.cpp=.o)

# Raylib and system libs
LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

# Rule to build the target executable.
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to build object files.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $ (OBJS) $(TARGET)