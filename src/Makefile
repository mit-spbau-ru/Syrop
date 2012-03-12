MAKE := make

.PHONY : clean

compile :
	$(MAKE) -C utils
	$(MAKE) -C core

docs :
	doxygen config.dox

clean :
	$(MAKE) clean -C utils
	$(MAKE) clean -C core
	rm -rf docs
