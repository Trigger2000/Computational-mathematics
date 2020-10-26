TARGET = a.out
CFLAGS = -O3

.PHONY: all clear

all: $(TARGET)

$(TARGET): main.o vector.o matrix.o
	g++ *.o $(CFLAGS) -o $(TARGET)

$@: $< vector.h matrix.h
	g++ $(CFLAGS) $< -o $@

clear:
	rm -rf $(TARGET) *.o