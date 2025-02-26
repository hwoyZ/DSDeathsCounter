BIN=DSDeathsCounter.exe
CXXFLAGS=-std=c++17 -pedantic  -Wall -O2

SHELL=cmd.exe

.PHONY: clean distclean style
$(BIN): main.o
	$(CXX) -o $(BIN) main.o

main.o: main.cpp soulgame.hpp process.hpp

style:
	astyle --style=allman *.cpp *.hpp

clean:
	$(RM) *.o $(BIN)
	
distclean:
	$(RM) *.o $(BIN) *.txt *.orig Makefile
