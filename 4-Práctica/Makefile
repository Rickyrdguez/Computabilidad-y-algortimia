CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = src

OBJS = p04_html_analyzer.o Attribute.o tag.o Comment.o HtmlDocument.o HtmlAnalyzer.o

p04_html_analyzer: $(OBJS)
	$(CXX) $(CXXFLAGS) -o p04_html_analyzer $(OBJS)

%.o: $(SRC)/%.cc $(SRC)/clases.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o p04_html_analyzer
