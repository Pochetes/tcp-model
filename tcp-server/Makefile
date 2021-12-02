all: server

server: main.o
	g++ main.o -o server

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	${RM} server *.o