CC = g++
CFLAGS = -O1 -Wall -std=c++17 -Wno-missing-braces
LDFLAGS = 
LDLIBS = 

SRCS = main.cpp 
EXEC = TestMake.exe

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f $(EXEC)