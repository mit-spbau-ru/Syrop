SRC := ../../../src
INCLUDES := $(SRC)/includes
PLUGINS := $(SRC)/plugins
UTILS := $(SRC)/utils
CORE := $(SRC)/core
INTEGRATON := $(SRC)/integration
GUI := $(SRC)/gui

CFLAGS := -Werror
LIBS := -lutils
LIBSPATH := -L$(UTILS)
INCPATH := -I$(INCLUDES)
CC := g++
MAKE := make

all : test

test : test.o utils
	$(CC) test.o $(LIBSPATH) $(LIBS) -o test

test.o : test.cpp
	$(CC) test.cpp $(INCPATH) $(CFLAGS) -c -o test.o

utils :
	$(MAKE) -C $(UTILS)

.PHONY : clean

clean :
	rm -f *.o test
	$(MAKE) clean -C $(UTILS)