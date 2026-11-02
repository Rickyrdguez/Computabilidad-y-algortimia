CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
SRC = src
TARGET = dfa2grammar

SRCS = $(wildcard $(SRC)/*.cc)
OBJS = $(patsubst $(SRC)/%.cc,%.o,$(SRCS))
HEADERS = $(wildcard $(SRC)/*.h)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: $(SRC)/%.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: clean