INCLUDES := ../includes
CFLAGS   := -Wall -Werror -pedantic -D _DEBUG -I$(INCLUDES)
CC       := g++
RM       := rm -f

SOURCES  := $(wildcard *.cpp)
OBJECTS  := $(patsubst %.cpp, %.o, $(SOURCES))

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