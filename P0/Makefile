.SUFFIXES:		# Clears out the suffix list.
.SUFFIXES: .cpp .o	# Introduces all the suffixes used.

SHELL = /bin/bash
EXE = practica0
MODULES = $(EXE).o

# CFLAGS - C/C++ compiler parameters.       
CFLAGS = -g -c -DXWINDOWS -I/usr/include -I     

# LDFLAGS - Linker parameters.
LDFLAGS = -L/usr/lib  

# LIBS - Libraries to use.
LIBS = -lglut -lGLU  -lGL -lX11 -lXext  -lc -lm

# CC - UNIX command to call C/C++ GNU compilator.
CC = g++

# Executable.
$(EXE): $(MODULES)	
	$(CC) -o $(EXE) $(LDFLAGS) $(MODULES) $(LIBS)