SRC := ..
INCLUDES := $(SRC)/includes
PLUGINS := $(SRC)/plugins
UTILS := $(SRC)/utils
INTEGRATON := $(SRC)/integration
GUI := $(SRC)/gui

PYVER := 2.7
PYTHON := python$(PYVER)
CFLAGS := -Werror
LIBS := -l$(PYTHON) -lboost_python -lutils
LIBSPATH := -L$(UTILS)
INCPATH := -I/usr/include/$(PYTHON) -I$(INCLUDES)
CC := g++
MAKE := make

all : coreutils.o pluginrunner.o

coreutils.o : coreutils.cpp coreutils.h
	$(CC) coreutils.cpp $(INCPATH) $(CFLAGS) -c -o coreutils.o

pluginrunner.o : pluginrunner.cpp pluginrunner.h
	$(CC) pluginrunner.cpp $(INCPATH) $(CFLAGS) -c -o pluginrunner.o

utils :
	$(MAKE) -C $(utils)

clean : 
	rm -f *.o

.PHONY : clean
