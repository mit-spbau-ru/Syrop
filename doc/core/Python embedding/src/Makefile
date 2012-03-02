PYVER=2.7
PYTHON=python$(PYVER)
INCDIR=-I/usr/include/$(PYTHON)
LIBS=-l$(PYTHON) -lboost_python

all : example1 example2

example1 : example1.o
	g++ example1.o -o example1 $(LIBS)

example2 : example2.o
	g++ example2.o -o example2 $(LIBS)

example1.o : example1.cpp
	g++ -c example1.cpp -c $(INCDIR)

example2.o : example2.cpp
	g++ -c example2.cpp -c $(INCDIR)

clean : 
	rm -f *.o example1 example2 hello.txt

.PHONY : clean
