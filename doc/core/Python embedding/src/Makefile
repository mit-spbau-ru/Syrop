PYVER=2.7
PYTHON=python$(PYVER)
INCDIR=-I/usr/include/$(PYTHON)
LIBS=-l$(PYTHON) -lboost_python

example1 : example1.o
	g++ example1.o -o example1 $(LIBS)

example1.o : example1.cpp
	g++ -c example1.cpp -c $(INCDIR)

clean : 
	rm -f *.o example1 hello.txt

default : example1

.PHONY : clean
