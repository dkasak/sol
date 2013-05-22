.PHONY: all, clean, distclean, dbmp
CFLAGS = -std=c99 -Wextra -Wall -pedantic -g 
CXXFLAGS = -std=c++11 -Wextra -Wall -pedantic -g -Wuninitialized -Wno-reorder -Wno-unused-parameter
LDFLAGS = -lm -lstdc++

dbmp_objects = dbmp.o
sol_objects = sol.o BRDF.o Sampler.o Plane.o ColourRGB.o Light.o Material.o Ray.o World.o Screen.o Intersection.o Shape.o Sphere.o Vector.o Debug.o Options.o Camera.o Tracer.o

all: sol dbmp

sol: $(sol_objects) $(dbmp_objects)
dbmp: $(dbmp_objects)
test_dbmp: $(dbmp_objects)

optimized: CXXFLAGS += -O3
optimized: clean all

clean: 
	-rm --force *.o test_dbmp sol

distclean:
	-rm --force *.o *.bmp test_dbmp sol

run:	all
	./sol
	sxiv -p output.bmp
