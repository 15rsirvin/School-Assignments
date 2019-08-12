OBJECTS = term.o TermSortingList.o Lab9.o 

HEADERS = term.h TermSortingList.h


Lab9: $(OBJECTS)
	g++ $^ -o $@

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -i *.o Lab8