.PHONY: all clean distclean dbmp test test_dbmp test_sol
CFLAGS = -std=c99 -Wextra -Wall -I include/ -pedantic
CXXFLAGS = -std=c++11 -Wextra -Wall -I include/ -pedantic -Wuninitialized \
	   -Wno-reorder -Wno-unused-parameter
LDFLAGS = -lm -lstdc++

sol_main = sol.o

all: sol dbmp

sol: sol.o
	make -C src/
	$(CXX) src/*.o sol.o -o sol

dbmp:
	make -C src/ dbmp

optimized: CXXFLAGS += -O4
optimized: CFLAGS += -O4
optimized: all

debug: CXXFLAGS += -Og -g
debug: CFLAGS += -Og -g
debug: all

test_dbmp: dbmp
	make -C tests/ test_dbmp

test_sol: sol
	make -C tests/ test_sol

test: test_dbmp test_sol

clean:
	-rm --force *.o sol
	make -C tests/ clean
	make -C src/ clean

distclean:
	-rm --force *.bmp
	-rm --force *.o sol
	make -C tests/ clean
	make -C src/ clean

run:	all
	./sol
	sxiv output.bmp
