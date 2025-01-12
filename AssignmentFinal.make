all: AssignmentFinal
AssignmentFinal: AssignmentFinal.o
	gcc -o AssignmentFinal AssignmentFinal.o

AssignmentFinal.o: AssignmentFinal.c diloseis.h
	gcc -c AssignmentFinal.c -o AssignmentFinal.o

clean:
	rm -f *.o AssignmentFinal
