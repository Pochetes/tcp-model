all: client

client: main.o
	g++ main.o -o client

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	${RM} client *.o