CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

OBJS=llrec-test.o llrec.o

all: llrec-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------

llrec-test: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) 

llrec.o: llrec.cpp llrec.h
	$(CXX) $(CXXFLAGS) -o $@ -c llrec.cpp

llrec-test.o: llrec-test.cpp llrec.h
	$(CXX) $(CXXFLAGS) -o $@ -c llrec-test.cpp

clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 