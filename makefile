#ncourses options
NC=-lmenu -lncurses
# Object files to either reference or create
SRC_W=src/window
OBJECTS=main.o $(SRC_W)/gui.o
# The executable file that will be created at the end
EXEC=net-spice.out
# The flags to use for compilation
FLAGS=-Wall
# The code compiler to use for compilation
CC=g++

# Perform action on all object files (May or may not exist)
all: $(OBJECTS)
	$(CC) $(FLAGS) -o $(EXEC) $(OBJECTS) $(NC)
