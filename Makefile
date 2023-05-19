CC = g++

CFLAGS += -g -Wall

.PHONY: all

all: hub
	rm -rf *.o

hub: Model.o Controller.o View.o
	$(CC) $(CFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

Model.o:
	$(CC) $(CFLAGS) -o $@ -c Model.cpp

Controller.o:
	$(CC) $(CFLAGS) -o $@ -c Controller.cpp

View.o:
	$(CC) $(CFLAGS) -o $@ -c View.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf *.o hub
