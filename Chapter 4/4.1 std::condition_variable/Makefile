PROGRAM   = main
CXX       = g++
CXXFLAGS  = -Wall -Wextra -pedantic -std=c++17

$(PROGRAM): main.o
	$(CXX) -c -o $(PROGRAM) main.o

.PHONY: clean

clean:
	-rm *.o $(PROGRAM) *core
