.SUFFIXES:		# Clears out the suffix list.
.SUFFIXES: .cpp .o	# Introduces all the suffixes used.

EXE = practica4
SRC = practica4.cpp objetos.cpp objetos.h file_ply_stl.cpp file_ply_stl.h vertex.h
OBJ = $(SRC:.cpp=.o)

# CFLAGS - C/C++ compiler parameters.       
CFLAGS = -g -DXWINDOWS -DSHM -I/usr/include -I.

# LDFLAGS - Linker parameters.
LDFLAGS = -L/usr/lib/nvidia-331

# LIBS - Libraries to use.
LIBS = -lglut -lGLU -lGL -lsupc++ -lm -lc -lstdc++ -lpthread

# CC - UNIX command to call C/C++ GNU compilator.
CC = g++

# Executable.
$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LIBS)

# Clean OBJ and EXECUTABLE.
clean:
	rm -rf *.o $(EXE)

# Compress files.
tgz:
	rm -f *.o *~ $(EXE)
	tar -zcvf $(EXE).tgz *