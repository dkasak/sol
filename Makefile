.PHONY: all, clean, distclean, dbmp
CFLAGS = -std=c99 -Wextra -Wall -pedantic
CXXFLAGS = -Wextra -Wall -pedantic
LDFLAGS = -lm

dbmp_objects = dbmp.o
sol_objects = sol.o

all: sol dbmp

sol: $(sol_objects)
dbmp : $(dbmp_objects)
test_dbmp : $(dbmp_objects)

clean: 
	-rm *.o test_dbmp sol

distclean:
	-rm *.o *.bmp test_dbmp sol

