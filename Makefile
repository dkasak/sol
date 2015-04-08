.PHONY: all clean distclean dbmp test test_dbmp test_sol
CFLAGS = -std=c99 -Wextra -Wall -I include/ -pedantic
CXXFLAGS = -std=c++11 -Wextra -Wall -I include/ -pedantic -Wuninitialized \
	   -Wno-reorder -Wno-unused-parameter
LDFLAGS = -lm -lstdc++

dbmp_objects = dbmp.o
sol_objects = BRDF.o Film.o Sampler.o Plane.o ColourRGB.o Light.o \
	      Material.o Ray.o World.o Screen.o Intersection.o Shape.o \
	      Sphere.o Vector.o Debug.o Options.o Camera.o Tracer.o Box.o
sol_main = sol.o

all: sol dbmp test

sol: $(sol_objects) $(dbmp_objects) $(sol_main)
dbmp: $(dbmp_objects)

test_write: $(dbmp_objects)
test_load: $(dbmp_objects)

test_dbmp: test_write test_load
test_sol: $(sol_objects) test_vector

optimized: CXXFLAGS += -O4
optimized: CFLAGS += -O4
optimized: all

debug: CXXFLAGS += -Og -g
debug: CFLAGS += -Og -g
debug: all

test:	test_dbmp test_sol
	./test_write
	./test_load
	./test_vector

clean:
	-rm --force *.o test_write test_load test_vector sol

distclean:
	-rm --force *.o *.bmp test_write test_load test_vector sol

run:	all
	./sol
	sxiv -p output.bmp
