EXEFILE = votecount
CXXFLAGS = -c -Wall
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
INCLUDES = -Iinclude

$(EXEFILE): $(OBJECTS)
	g++ $^ -o $@ $(INCLUDES)

%.o: %.cpp
	g++ $(CXXFLAGS) $^ -o $@ $(INCLUDES)

clean:
	rm *.o $(EXEFILE)

.PHONY: clean