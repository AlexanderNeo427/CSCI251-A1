# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11 -Iinclude
# CXXFLAGS_BUILD = -Wall -Wextra -Werror -std=c++14 -Iinclude
# CXXFLAGS_DEBUG = -Wall -std=c++14 -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source and Object Files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Executable Name
TARGET = $(BUILD_DIR)/main

# Default Target
all: $(TARGET) run

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