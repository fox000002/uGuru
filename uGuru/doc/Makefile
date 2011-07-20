#
all : doc

doc : Doxyfile
	doxygen $<

.PHONY : clean
clean :
	rm -rvf html
	rm -rvf latex

