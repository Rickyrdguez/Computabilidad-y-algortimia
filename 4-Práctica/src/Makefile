CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

OBJS = p04_html_analyzer.o Attribute.o tag.o Comment.o HtmlDocument.o HtmlAnalyzer.o

p04_html_analyzer: $(OBJS)
	$(CXX) $(CXXFLAGS) -o p04_html_analyzer $(OBJS)

p04_html_analyzer.o: p04_html_analyzer.cc clases.h
	$(CXX) $(CXXFLAGS) -c p04_html_analyzer.cc

Attribute.o: Attribute.cc clases.h
	$(CXX) $(CXXFLAGS) -c Attribute.cc

tag.o: tag.cc clases.h
	$(CXX) $(CXXFLAGS) -c tag.cc

Comment.o: Comment.cc clases.h
	$(CXX) $(CXXFLAGS) -c Comment.cc

HtmlDocument.o: HtmlDocument.cc clases.h
	$(CXX) $(CXXFLAGS) -c HtmlDocument.cc

HtmlAnalyzer.o: HtmlAnalyzer.cc clases.h
	$(CXX) $(CXXFLAGS) -c HtmlAnalyzer.cc

clean:
	rm -f *.o p04_html_analyzer