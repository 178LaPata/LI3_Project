# Name of the project
PROJ_NAME=programa-principal
 
# .c files
C_SOURCE=$(wildcard ./src/*.c)
 
# .h files
H_SOURCE=$(wildcard ./libs/*.h)
 
# Object files
OBJ=$(subst .c,.o,$(subst src,obj,$(C_SOURCE)))
 
# Compiler
CC = gcc
 
# Flags for compiler
CC_FLAG S= -Wall -g
  

