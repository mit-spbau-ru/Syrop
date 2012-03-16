PYTHON   := python2.7
INCLUDES := -I/usr/include/$(PYTHON) -I../includes
CFLAGS   := -Wall -Werror -pedantic -D _DEBUG $(INCLUDES) -ggdb3
LIBS     := -l$(PYTHON) -lboost_python -lutils
LIBSPATH := -L../utils/
CC       := g++
RM       := rm -f

SOURCES  := $(wildcard *.cpp)
OBJECTS  := $(patsubst %.cpp, %.o, $(SOURCES))

.PHONY : clean
.SUFFIXES : .cpp .o .h

all : syrop

syrop : $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBSPATH) $(LIBS) -o $@

.cpp.o :
	$(CC) -MMD -c $(CFLAGS) $(INCPATH) $< -o $@

-include *.d

clean :
	$(RM) *.o *.d syrop


