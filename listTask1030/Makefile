CircularQueue: CircularQueue.o Simulation.o  CircularQueueMain.o
	gcc -o CircularQueue CircularQueue.o Simulation.o CircularQueueMain.o

Simulation.o: Simulation.c CircularQueue.h
	gcc -c Simulation.c

CircularQueue.o: CircularQueue.c
	gcc -c CircularQueue.c CircularQueue.h

CircularQueueMain.o: CircularQueueMain.c
	gcc -c CircularQueueMain.c

clean:
	rm -rf *.o
	rm -rf *.gch
	rm -rf CircularQueue