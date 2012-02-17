.PHONY: all, clean, distclean, dbmp
CFLAGS = -std=c99 -Wextra -Wall -pedantic
CXXFLAGS = -Wextra -Wall -pedantic
LDFLAGS = -lm

dbmp_objects = dbmp.o test_dbmp.o
sol_objects = main.o

all: main

clean: 
	-rm *.o test_dbmp

distclean:
	-rm *.o *.bmp test_dbmp

dbmp : $(dbmp_objects) test_dbmp 
dbmp.o : dbmp.h
test_dbmp.o : dbmp.h
test_dbmp : test_dbmp.o dbmp.o

