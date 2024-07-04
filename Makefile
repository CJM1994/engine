CXX = g++
BUILD_DIR = build
SOURCE_DIR = src
ASSETS_DIR = assets
INCLUDE_DIR = include
HEADER_CFLAGS = -I./include/
SDL_CFLAGS = -Wall -I/usr/include/SDL2 -D_REENTRANT
SDL_LFLAGS = -lSDL2

# Automatically find all .cpp files in SOURCE_DIR
SRCS = $(wildcard $(SOURCE_DIR)/*.cpp)

# Generate corresponding .o file names
OBJS = $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Target executable
EXEC = $(BUILD_DIR)/main

# Default target
all: $(EXEC)
	cp $(ASSETS_DIR)/* $(BUILD_DIR)

# Rule to link object files into executable
$(EXEC): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(SDL_CFLAGS) $(HEADER_CFLAGS) $(SDL_LFLAGS) $^ -o $@

# Rule to compile each source file into object files
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(SDL_CFLAGS) $(HEADER_CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*

