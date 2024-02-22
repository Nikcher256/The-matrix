.PHONY: all clean uninstall reinstall

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
INC = -I inc
SRC_DIR = src
OBJ_DIR = obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
NAME := ./way_home

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

uninstall: clean
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)/*.o

reinstall: uninstall all
