# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -g -I/opt/homebrew/Cellar/sfml/2.6.1/include -I/opt/homebrew/include -I$(INC_DIR)

# Linker flags
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
DATA_DIR = data

# Find all .cpp files in src directory and its subdirectories
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')

# Generate corresponding .o files for each .cpp file
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Main target
TARGET = sfml-app

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(DATA_DIR)
	$(CC) $^ -o $@ $(LDFLAGS) $(LIBS)

# Compile each .cpp file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DATA_DIR):
	mkdir -p $(DATA_DIR)

.PHONY: clean run

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
