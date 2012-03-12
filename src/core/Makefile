PYTHON   := python2.7
INCLUDES := -I/usr/include/$(PYTHON) -I../includes
CFLAGS   := -Wall -Werror -pedantic -D _DEBUG $(INCLUDES)
LIBS     := -l$(PYTHON) -lboost_python -lutils
LIBSPATH := -L../utils
CC       := g++
RM       := rm -f

SOURCES  := $(wildcard *.cpp)
OBJECTS  := $(patsubst %.cpp, %.o, $(SOURCES))

.PHONY : clean
.SUFFIXES : .cpp .o .h

-include *.d

all : syrop

syrop : $(OBJECTS)
	$(CC) $(LIBS) $(CFLAGS) $(OBJECTS) -o $@

.cpp.o :
	$(CC) -MMD -c $(CFLAGS) $(INCPATH) $< -o $@

clean :
	$(RM) *.o *.d syrop


