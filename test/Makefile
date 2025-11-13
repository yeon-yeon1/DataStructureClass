testApp: test1.o testMain.o
	gcc -o testApp test1.o testMain.o

test1.o: test1.c test1.h
	gcc -c test1.c

test2.o: test2.c test1.h
	gcc -c test2.c

testMain.o: testMain.c
	gcc -c testMain.c

clean:
	rm -rf *.o
	rm -rf *.gch
	rm -rf testApp