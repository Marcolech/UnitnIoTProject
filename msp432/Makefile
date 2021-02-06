PROJECT_NAME := UnitnIoTProject

# PROJECT setup
PROJECT_DIR :=
# binary files location
BIN_DIR 	:= $(PROJECT_DIR)bin
# source code to compile
SRC_DIR 	:= $(PROJECT_DIR)src
# board configuration files
CONFIG_DIR 	:= $(PROJECT_DIR)config
# library folder with TI libraries
LIB_DIR 	:= $(PROJECT_DIR)lib

include $(CONFIG_DIR)/include.mk
include $(CONFIG_DIR)/target.mk
include $(CONFIG_DIR)/compiler.mk

# output files
BINARY_FILE = $(BIN_DIR)/$(PROJECT_NAME).out
MAP_FILE = $(BIN_DIR)/$(PROJECT_NAME).map

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Project executable
MAIN_DIR 	= $(SRC_DIR)
MAIN_DEPS	= $(call rwildcard,$(MAIN_DIR),*.h)
MAIN_SRCS	= $(call rwildcard,$(MAIN_DIR),*.c)
MAIN_OBJS 	= $(patsubst $(SRC_DIR)%.c,$(BIN_DIR)%.o,$(MAIN_SRCS))


# build object file (.o) for all c file in src directory (my code)
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@echo 'Building target: "$@"'
	@mkdir -p $(@D)
	@$(CC) -c -o $@ $< $(CC_FLAGS) $(CC_INCLUDE_FLAGS)

# create final executable
build: $(MAIN_OBJS)
	@echo 'Linking $(BINARY_FILE)'
	@$(LD) -o $(BINARY_FILE) $^ $(LD_FLAGS) $(LD_INCLUDE_FLAGS)
	@echo 'Linking done'

help:
	@cat README

clean:
	@rm -rf $(BIN_DIR)

all : build

rebuild: clean build


#COMMANDS
.PHONY: help clean build rebuild all
.DEFAULT_GOAL := all
