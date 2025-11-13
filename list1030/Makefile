Que: Que.o Simulation.o QueMain.o
	gcc -o Que Que.o Simulation.o QueMain.o

Simulation.o: Simulation.c Que.h
	gcc -c Simulation.c

Que.o: Que.c 
	gcc -c Que.c 

QueMain.o: QueMain.c
	gcc -c QueMain.c

clean:
	rm -rf *.o
	rm -rf *.gch
	rm -rf Que

