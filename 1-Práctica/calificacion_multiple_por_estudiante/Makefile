EXEC = p01_multiple_grades
OBJS = calificacion_multiple.o p01_multiple_grades.o
CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(EXEC) $(OBJS)