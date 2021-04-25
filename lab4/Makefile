TARGET = rk.out
CFLAGS = -O3

.PHONY: all clear

all: $(TARGET)

$(TARGET): main.o rk.o
	g++ *.o $(CFLAGS) -o $(TARGET)
	./$(TARGET)
	gnuplot plot.plt

$@: $< rk.h
	g++ $(CFLAGS) $< -o $@

clear:
	rm -rf $(TARGET) *.o *.svg *.dat