CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SRC_GUI=src/window
SOURCES=main.cpp $(SRC_GUI)/gui.cpp -lncurses
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=net-spice

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
