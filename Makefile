.PHONY: all, clean, distclean, dbmp
CFLAGS = -std=c99 -Wextra -Wall -pedantic -g 
CXXFLAGS = -Wextra -Wall -pedantic -g -Wuninitialized -Wno-reorder
LDFLAGS = -lm -lstdc++

dbmp_objects = dbmp.o
sol_objects = sol.o Plane.o ColourRGB.o Light.o Material.o Point.o Ray.o World.o Screen.o ShadeInfo.o Shape.o Sphere.o Vector.o Debug.o Options.o Camera.o

all: sol dbmp

sol: $(sol_objects) $(dbmp_objects)
dbmp : $(dbmp_objects)
test_dbmp : $(dbmp_objects)

clean: 
	-rm --force *.o test_dbmp sol

distclean:
	-rm --force *.o *.bmp test_dbmp sol

run:	all
	./sol
	sxiv output.bmp
