MAKEFLAGS += --silent

cc = g++
cflags = -std=c++17 -g -c

bitmap.o : bitmap.cpp bitmap.h 
	$(cc) $(cflags) -o bitmap.o bitmap.cpp

handle.o : handle.cpp handle.h 
	$(cc) $(cflags) -o handle.o handle.cpp

main.o : main.cpp 
	$(cc) $(cflags) -o main.o main.cpp

all: main.o bitmap.o handle.o 
	$(cc) -std=c++17 -g -o main main.o bitmap.o handle.o 

clean:
	rm -f -- main -f -- *.o -f -- *.exe
