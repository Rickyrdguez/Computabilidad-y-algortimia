CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = src
TARGET = p01_single_grades

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp,%.o,$(SRCS))
HEADERS = $(wildcard $(SRC)/*.h)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: $(SRC)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: clean
