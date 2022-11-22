# Name of the project
PROJ_NAME=programa-principal

# .c files
C_SOURCE=$(wildcard ./src/*.c)

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)

# .h files
H_SOURCE=$(wildcard ./libs/*.h)
 
# Object files
OBJ=$(subst .c,.o,$(subst src,obj,$(C_SOURCE)))
 
# Compiler
CC = gcc

GLIB = `pkg-config --cflags --libs glib-2.0`

# Flags for compiler
CC_FLAGS = -Wall -g
  
run:
	@mkdir resultados
	@$(CC) $(CFLAGS) $(SRC) $(GLIB) -o $(PROJ_NAME)

clean:
	@rm -rf *.o $(PROJ_NAME) *~ resultados