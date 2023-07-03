# Makefile

# Compiler
CC = clang++

# Compiler flags
CFLAGS = -std=c++11 -Wall -Wextra -Wno-missing-braces -g

# Linker flags
LDFLAGS = -lraylib 

# Target executable
TARGET = out

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(LDFLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)

