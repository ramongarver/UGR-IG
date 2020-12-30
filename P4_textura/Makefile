
EXE = practica4
SRC = practica4.cpp

# LDFLAGS - Linker parameters.
LDFLAGS = -L/usr/X11R6/lib/

# LIBS - Libraries to use.
LIBS =  -lGL -lGLU -lglut -lm -lX11 -lpthread

# CC - UNIX command to call C/C++ GNU compilator.
CC = g++

all: $(EXE) 

$(EXE): $(SRC) CImg.h
	$(CC) -o $(EXE) -std=c++11 -I./ $(SRC) $(LIBS)

# Clean OBJ and EXECUTABLE.
clean:
	rm -rf *.o $(EXE)