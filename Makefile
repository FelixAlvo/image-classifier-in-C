# C-Complier
CC = gcc
# C-flags, Warnings-all, Optimization level 2
Cflags = -Wall -O2


# build directory
BUILD_DIR = build
# object directory
OBJ_DIR = $(BUILD_DIR)/obj


# source directory
SRC_DIR = src

# source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/neural_net.c

# object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Output binary name and directory
TARGET = $(BUILD_DIR)/catDog


# build rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# compile .c files in to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# clean rule
clean:
	rm -rf $(BUILD_DIR)
