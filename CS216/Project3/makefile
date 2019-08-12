HEADERS = Graph.h Matrix.h
OBJECTS = CS216PA3.o Graph.o Matrix.o
CC = g++ -std=c++11

#build executable program
CS216PA3: $(OBJECTS)
	$(CC) $^ -o $@
#build objective files from source files
%.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@
#clean up the mess
clean:
	rm -i *.o CS216PA3

