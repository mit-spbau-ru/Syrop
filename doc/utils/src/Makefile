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

all : test1

test1 : test1.o utils
	$(CC) test1.o $(LIBSPATH) $(LIBS) -o test1

test1.o : test1.cpp
	$(CC) test1.cpp $(INCPATH) $(CFLAGS) -c -o test1.o

utils :
	$(MAKE) -C $(UTILS)

.PHONY : clean

clean :
	rm -f *.o test1
	$(MAKE) clean -C $(UTILS)