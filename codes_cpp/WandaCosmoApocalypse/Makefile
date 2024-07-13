CC = g++
CFLAGS = -O1 -Wall -std=c++17 -Wno-missing-braces -Iinclude/
LDFLAGS = -Llib/
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRCS = main.cpp grid.hpp grid.cpp simulation.hpp simulation.cpp
EXEC = CosmoWanda.exe

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f $(EXEC)