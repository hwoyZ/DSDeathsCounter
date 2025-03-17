NAME=DSDeathsCounter

BIN=$(NAME).exe

RELDIR=$(NAME)-bin

VER=pre-release

HASH=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

CXXFLAGS=-std=c++17 -pedantic  -Wall -O2 -D__DCVERSION__='"$(VER)"' -D__DCHASH__='"$(HASH)"'
LDFLAGS=-dynamic-libstdc++ -dynamic-libgcc #-static-libstdc++ -static-libgcc

RM=del
RMDIR=rmdir

SHELL=cmd.exe

.PHONY: clean distclean style
$(BIN): main.o
	$(CXX) $(LDFLAGS) -o $(BIN) main.o

main.o: main.cpp soulgame.hpp process.hpp

style:
	astyle --style=allman *.cpp *.hpp

clean:
	$(RM) *.o $(BIN)
	
distclean:
	$(RM) *.o $(BIN) *.txt *.orig Makefile *.tgz *.txz & $(RMDIR) /S /Q $(RELDIR)

.PHONY: rel

rel: $(BIN)
	make prepare && tar -cvzf $(NAME)-$(VER)-win64.tgz $(RELDIR)
