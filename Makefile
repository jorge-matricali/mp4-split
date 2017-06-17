OBJECTS = mp4-split.o

EXEC = mp4-split

CXXFLAGS = -Wall

CXX = g++

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

clean :
	rm mp4-split mp4-split.o
