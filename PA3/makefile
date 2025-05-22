CC=g++
CFLAGS = -c
LDFLAGS=-std=c++11 -O3 -lm
SOURCES=*.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=cb
INCLUDES=*.h

all: bin/cb
	@echo -n ""

bin/cb: cb.o
	$(CC) -O3 cb.o -o bin/cb

cb.o: src/cb.cpp
	$(CC) $(CFLAGS) $< -Ilib -o $@

clean:
	rm -rf *.o ./$(EXECUTABLE)
