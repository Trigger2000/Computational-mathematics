CC = g++
CFLAGS = -c -O3
SOURCES = main.cpp vector.cpp matrix.cpp rozenbrok.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = rozenbrok

.PHONY: all clear

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@
	./$(EXECUTABLE)
	gnuplot plot.plt

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -rf $(EXECUTABLE) *.o *.svg *.dat