# @author Michael Tessier, Chao-Jung (Julie) Wu
# @Version 1.00.00
# @since 2016-11-16

TARGET = bin/tp2
LIBS = -lm -ljansson
CC = gcc
CFLAGS = -g -Wall
SRC = src/
DDIR = data/

.PHONY: default all clean data test cleantest

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
HEADERS = $(SRC)$(wildcard *.h)
	
$%.o: %.c $(HEADERS)
	$(CC) ${CFLAGS} -c $< -o $@

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(OBJECTS) ${CFLAGS} $(LIBS) -o $@

clean:
	-rm -f $(SRC)*.o $(TARGET) a.out $(DDIR)*.* *.txt

data:
	-git submodule init
	-git submodule update

# TEST compiles cmdtest, then executes cmdtest which cleans and compiles again tp2 and runs the test
test:
	-cd test && $(MAKE)
	-./test/cmdtest

cleantest:
	-cd test && $(MAKE) clean	
