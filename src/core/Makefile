SRC := ..
INCLUDES := $(SRC)/includes
PLUGINS := $(SRC)/plugins
UTILS := $(SRC)/utils
INTEGRATON := $(SRC)/integration
GUI := $(SRC)/gui

PYVER := 2.7
PYTHON := python$(PYVER)
CFLAGS := -Werror -pedantic
LIBS := -l$(PYTHON) -lboost_python -lutils
LIBSPATH := -L$(UTILS)
INCPATH := -I/usr/include/$(PYTHON) -I$(INCLUDES) -I/usr/include/file
CC := g++
MAKE := make

SOURCES_CPP = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES_CPP))

.SUFFIXES: .cpp .o .h

syrop : $(OBJECTS)
	@echo -n 'Linking $@ ...'
	@$(CC) $(LIBS) $(CFLAGS) $(OBJECTS) -o $@
	@echo ' OK'

.cpp.o :
	@echo -n 'Compiling $@ ...'
	@$(CC) -MMD -c $(CFLAGS) $(INCPATH) $< -o $@
	@echo ' OK'

clean :
	@$(RM) *.o *.d

-include *.d

run : all
	./$(OUT)

utils :
	$(MAKE) -C $(utils)

.PHONY : clean
