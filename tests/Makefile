.PHONY: all test_sol test_dbmp

CFLAGS = -std=c99 -Wextra -Wall -I ../include/ -pedantic
CXXFLAGS = -std=c++11 -Wextra -Wall -I ../include/ -pedantic -Wuninitialized \
	   -Wno-reorder -Wno-unused-parameter
LDFLAGS = -lm -lstdc++

sol_tests = test_vector
dbmp_tests = test_write test_load

all: test_sol test_dbmp

test_dbmp: test_write.o test_load.o
	$(CC) -lm ../src/dbmp.o test_write.o -o test_write
	$(CC) ../src/dbmp.o test_load.o -o test_load
	./test_write
	./test_load

test_sol: test_vector.o
	$(CXX) ../src/*.o test_vector.o -o test_vector
	./test_vector

clean:
	-rm --force *.bmp
	-rm --force *.o $(sol_tests) $(dbmp_tests)
