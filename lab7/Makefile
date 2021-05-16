TARGET = shooting.out
CFLAGS = -O3

.PHONY: all clear

all: $(TARGET)

$(TARGET):
	g++ $(CFLAGS) main.cpp -o $(TARGET)
	./$(TARGET)
	gnuplot plot.plt

clear:
	rm -rf $(TARGET) *.dat *.svg