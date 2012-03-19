MAKE := make

.PHONY : clean

all : syrop

syrop :
	$(MAKE) -C utils
	$(MAKE) -C core

syrop_gui:
	echo 'no way' 

docs :
	doxygen config.dox

clean :
	$(MAKE) clean -C utils
	$(MAKE) clean -C core
	rm -rf docs
