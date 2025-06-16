CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC_DIR = src
BIN_DIR = bin
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/student.c $(SRC_DIR)/file_operations.c $(SRC_DIR)/utils.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/student_manager

all: $(BIN_DIR) $(EXECUTABLE)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

run: all
	./$(EXECUTABLE)

.PHONY: all clean run
