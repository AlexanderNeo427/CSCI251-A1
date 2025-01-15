# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++14 -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source and Object Files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Executable Name
TARGET = ./main.app run

# Default Target
all: $(TARGET) 

# Build Executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Pattern Rule for Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)  # Ensure build directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Target
clean:
	rm -rf $(BUILD_DIR)

# Run Target
run:
	@$(TARGET)

# Phony Targets
.PHONY: all clean run