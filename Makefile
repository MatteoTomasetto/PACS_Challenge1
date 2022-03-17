CXXFLAGS = -fPIC
LDFLAGS = -L. -Wl,-rpath=${PWD}
LIBS = -lcauchyutilities

.PHONY: all clean distclean

all: main

main: main.o libcauchyutilities.so
	$(CXX) $(LDFLAGS) main.o -o main $(LIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

libcauchyutilities.so: cauchy_utilities.o
	$(CXX) $(LDFLAGS) -shared -Wl,-soname,libcauchyutilities.so \
	cauchy_utilities.o -o libcauchyutilities.so

cauchy_utilities.o: cauchy_utilities.cpp
	$(CXX) $(CXXFLAGS) -c cauchy_utilities.cpp

clean:
	$(RM) *.o 

distclean: clean
	$(RM) libcauchyutilities.so main
