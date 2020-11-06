.SUFFIXES:		# Clears out the suffix list.
.SUFFIXES: .cpp .o	# Introduces all the suffixes used.

SHELL = /bin/bash
EXE = practica1
SRC = practica1.cpp objetos.cpp
OBJ = $(SRC:.cpp=.o)

# CFLAGS - C/C++ compiler parameters.       
CFLAGS = -g -DXWINDOWS -DSHM -I/usr/include -I.

# LDFLAGS - Linker parameters.
LDFLAGS = -L/usr/lib  

# LIBS - Libraries to use.
LIBS = -lGL -lGLU -lglut -lm

# CC - UNIX command to call C/C++ GNU compilator.
CC = g++

# All.
all: $(EXE)

# Executable.
$(EXE): objetos.o practica1.o
	$(CC) -o $(EXE) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBS)

# Clean OBJ and EXECUTABLE.
clean:
	rm -f *.o
	rm -f $(EXE)

# Compress files.
tgz:
	rm -f *.o
	rm *~
	rm -f $(EXE)
	tar -zcvf $(EXE).tgz *