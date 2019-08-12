OBJECTS = term.o SortingList.o Lab10.o autocomplete.o 

HEADERS = term.h TermSortingList.h autocomplete.h


Lab10: $(OBJECTS)
	g++ $^ -o $@

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i *.o Lab10