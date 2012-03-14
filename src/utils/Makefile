INCLUDES := ../includes
<<<<<<< HEAD
CFLAGS   := -Wall -Werror -pedantic -D _DEBUG -I$(INCLUDES) -ggdb3
CC       := g++
RM       := rm -f
=======
CFLAGS := -Wall -Werror -pedantic -D _DEBUG -I$(INCLUDES)
CC := g++
RM := rm -f
>>>>>>> 4dc38dafe4c5542c0dfb0cef2cdb000b3bbaca30

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

.PHONY : clean
.SUFFIXES : .cpp .o .h

all : libutils.a

libutils.a : $(OBJECTS)
	ar crs libutils.a $(OBJECTS)

.cpp.o :
	$(CC) -MMD -c $(CFLAGS) $< -o $@

-include *.d

clean :
	$(RM) *.o *.d *.a
<<<<<<< HEAD
=======

>>>>>>> 4dc38dafe4c5542c0dfb0cef2cdb000b3bbaca30
