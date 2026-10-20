CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = p06_DFA_simulator
SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean