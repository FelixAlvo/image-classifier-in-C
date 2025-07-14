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
UTILS_DIR = $(SRC_DIR)/utils
IMAGE_DIR = $(SRC_DIR)/image


# include
INCLUDES = -I$(SRC_DIR) -I$(UTILS_DIR) -I$(IMAGE_DIR)

# source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
UTIL_FILES = $(wildcard $(UTILS_DIR)/*.c)
IMAGE_FILES = $(wildcard $(IMAGE_DIR)/*.c)

SRCS = $(SRC_FILES) $(UTIL_FILES) $(IMAGE_FILES)

# object files
OBJ_FILES = \
	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES)) \
	$(patsubst $(UTILS_DIR)/%.c,$(OBJ_DIR)/%.o,$(UTIL_FILES)) \
	$(patsubst $(IMAGE_DIR)/%.c,$(OBJ_DIR)/%.o,$(IMAGE_FILES)) \
	

# Output binary name and directory
TARGET = $(BUILD_DIR)/catDog


# build rule
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) -lm

# compile .c files in to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(IMAGE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# TEST BELOW

TEST_DIR = test

TEST_SRC_DIR = $(TEST_DIR)/test_src

TEST_BUILD_DIR = $(TEST_DIR)/test_build

TEST_OBJ_DIR = $(TEST_BUILD_DIR)/obj

TEST_SRC = $(TEST_SRC_DIR)/test.c
TEST_OBJ = $(TEST_OBJ_DIR)/test.o
TEST_BIN = $(TEST_BUILD_DIR)/tests

TEST_DEPS = $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES))

$(TEST_BIN): $(TEST_OBJ) $(TEST_DEPS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

# compile test source separately
$(TEST_OBJ): $(TEST_SRC)
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: test
test: $(TEST_BIN)
	@$(TEST_BIN)

# clean rule
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TEST_BUILD_DIR)