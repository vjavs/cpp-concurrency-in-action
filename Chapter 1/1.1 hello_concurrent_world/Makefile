PROGRAM   = main
CXX       = g++
CXXFLAGS  = -g -Wall -Wextra -pedantic -std=c++2a
LDLIBS    = -lpthread

$(PROGRAM): main.o
	$(CXX) -o $(PROGRAM) $(LDLIBS) main.o

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
