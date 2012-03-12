СС := g++
CFLAG := -Wall -D _DEBUG
LIBS :=
INCLUDE :=

all : libutils.a

libutils.a : proxysettings.o netparams.o iniparser.o fileinfo.o stringutils.o system.o
	ar crs libutils.a proxysettings.o netparams.o iniparser.o fileinfo.o stringutils.o system.o

proxysettings.o : proxysettings.cpp
	$(CC) $(CFLAG) proxysettings.cpp -c -o proxysettings.o

netparams.o : netparams.cpp
	$(CC) $(CFLAG) netparams.cpp -c -o netparams.o

iniparser.o : iniparser.cpp
	$(CC) $(CFLAG) iniparser.cpp -c -o iniparser.o

fileinfo.o : fileinfo.cpp
	$(CC) $(CFLAG) fileinfo.cpp -c -o fileinfo.o

stringutils.o : stringutils.cpp
	$(CC) $(CFLAG) stringutils.cpp -c -o stringutils.o

system.o : system.cpp
	$(CC) $(CFLAG) system.cpp -c -o system.o

main.o : main.cpp
	$(CC) $(CFLAG) main.cpp -c -o main.o

clean:
	rm -rf *.o *.a

.PHONY : clean

