#### Este archivo no trabaja con los archivos que tienen ahi.
#### Debieron haber adaptado esto a sus archivos. Algo como esto

CC = gcc
FLAGS = -O2
FLAGSprof= -Og -pg
FLAGSdeb=-g
BINARIES= EXPLICT IMPLICIT

all: $(BINARIES)

EXPLICT: calor_explicito.c
	$(CC) -o EXPLICT $(FLAGS) calor_explicito.c -lm
	
IMPLICIT: implicit.c
	$(CC) -o IMPLICIT $(FLAGS) calor_explicito.c -lm

EXPLICTPROF: calor_explicito.c
	$(CC) -o EXPLICTprof $(FLAGSprof) calor_explicito.c -lm
	
IMPLICITPROF: implicit.c
	$(CC) -o IMPLICITprof $(FLAGSprof) calor_explicito.c -lm


clean:
	rm -f $(BINARIES) EXPLICTprof IMPLICITprof *.o

# prog : main.o
	# cc -o prog main.o
# main.o : main.c math.h
	# cc -c main.c
# clean :
	# rm -f *.o prog