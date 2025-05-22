CC=g++
CFLAGS = -c
LDFLAGS=-std=c++11 -O3 -lm
SOURCES=*.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mps
INCLUDES=*.h

all: bin/mps
	@echo -n ""

bin/mps: mps.o
	$(CC) -O3 mps.o -o bin/mps

mps.o: src/mps.cpp
	$(CC) $(CFLAGS) $< -Ilib -o $@

clean:
	rm -rf *.o ./$(EXECUTABLE)
