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
CC_FLAG S= -Wall      \
   		   -g
  
# Command used at clean target
RM = rm -rf

# Compilation and linking

all: objFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) $^ -o $@
 
./obj/%.o: ./src/%.c ./libs/%.h
	$(CC) $< $(CC_FLAGS) -o $@

./obj/Main.o: ./src/Main.c $(H_SOURCE)
	$(CC) $< $(CC_FLAGS) -o $@

objFolder:
 
clean:
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
 
.PHONY: all clean