# @author Chao-Jung (Julie) Wu

all: cmdtest

cmdtest: cmdtest.o
	gcc -o cmdtest cmdtest.o
cmdtest.o: cmdtest.c
	gcc -Wall -c cmdtest.c


.PHONY: clean

clean:
	rm -f *.o cmdtest a.out 
	rm -fr .*.swo

