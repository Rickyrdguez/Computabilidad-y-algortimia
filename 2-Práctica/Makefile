CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

OBJS = p02_string.o alfabeto.o cadena.o lenguaje.o

p02_strings: $(OBJS)
	$(CXX) $(CXXFLAGS) -o p02_strings $(OBJS)

p02_string.o: p02_string.cpp p02_string.h
	$(CXX) $(CXXFLAGS) -c p02_string.cpp

alfabeto.o: alfabeto.cpp p02_string.h
	$(CXX) $(CXXFLAGS) -c alfabeto.cpp

cadena.o: cadena.cpp p02_string.h
	$(CXX) $(CXXFLAGS) -c cadena.cpp

lenguaje.o: lenguaje.cpp p02_string.h
	$(CXX) $(CXXFLAGS) -c lenguaje.cpp

clean:
	rm -f *.o p02_strings