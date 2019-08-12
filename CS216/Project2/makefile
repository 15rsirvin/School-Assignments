OBJECTS = term.o SortingList.o CS216PA2.o autocomplete.o

HEADERS = term.h SortingList.h autocomplete.h


CS216PA2: $(OBJECTS)
	g++ $^ -o $@

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i *.o CS216PA2