# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -g -fsanitize=address -I/opt/homebrew/Cellar/sfml/2.6.1/include

# Linker flags
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -fsanitize=address

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

# Find all .cpp files in src directory and its subdirectories
SOURCES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)

# Generate corresponding .o files for each .cpp file
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Main target
TARGET = sfml-app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LIBS)

# Compile each .cpp file into a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean run

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
