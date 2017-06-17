OBJECTS = mp4-split.o

EXEC = mp4-split

CFLAGS = -Wall

C = gcc

all: $(OBJECTS)
	$(C) $(CFLAGS) -o $(EXEC) $(OBJECTS)

clean :
	rm mp4-split mp4-split.o
