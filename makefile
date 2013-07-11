OBJ = main.o mutex.o

all: $(OBJ)
	gcc $(OBJ) -o prodcons -lpthread

main.o: main.c mutex.h
	gcc -c main.c

mutex.o: mutex.h mutex.c 
	gcc -c mutex.c
	ar -cru libmutex.a mutex.o

clean:
	rm *.o prodcons

teste:
	./prodcons
