# Makefile

# Compiler
CC = clang++

# Compiler flags
CFLAGS = -std=c++11 -Wall -Wextra -Wno-missing-braces -g

# Linker flags
LDFLAGS = -lraylib 

# Target
TARGET = out
COMPS = brick-breaker.o main.o

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -c main.cpp brick-breaker.cpp $(LDFLAGS)
	$(CC) $(CFLAGS) -o $(TARGET) $(COMPS) $(LDFLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(COMPS) $(TARGET)

