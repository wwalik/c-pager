PROJECT_NAME := app

SHELL := /bin/bash

INCLUDE_DIR := include
SRC_DIR := src
BUILD_DIR := build
INSTALL_DIR := /bin

CC := gcc
CFLAGS := --std=gnu99 -iquote$(INCLUDE_DIR) -MMD -lncurses
DBGFLAGS := -g

.PHONY: all clean 

all: $(PROJECT_NAME) 

clean:
	rm $(PROJECT_NAME)* 
	rm $(BUILD_DIR)/*.o
	rm $(BUILD_DIR)/*.d

# transform all src/*.c paths into build/*.o paths
src_c_files := $(wildcard $(SRC_DIR)/*.c)
src_o_files := $(patsubst %.c,%.o,$(src_c_files))
build_o_files := $(subst $(SRC_DIR),$(BUILD_DIR),$(src_o_files))

# Build main executable
$(PROJECT_NAME): $(build_o_files)
	$(CC) $^ -o $@ $(CFLAGS)

# Build .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DBGFLAGS) -c $< -o $@


# include dependencies magic
-include $(BUILD_DIR)/*.d
