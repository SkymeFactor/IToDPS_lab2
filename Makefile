CPPC=g++
CPPFLAGS=-Wall -c -std=c++17
SOURCES=Main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=clData.h clHandler.h clReader.h
EXECUTABLE=ConsoleCalc

all: $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) *.o
 
$(EXECUTABLE): $(OBJECTS)
	$(CPPC) -Wall -o $@ $(OBJECTS) $(HEADERS)

Main.o: Main.cpp
	$(CPPC) $(CPPFLAGS) -o $@ Main.cpp
