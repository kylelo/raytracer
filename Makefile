CC = g++
#LIBS = -lGL -lGLU -lglut
LIBS = -framework OpenGL -framework GLUT
OBJS = main.o renderer.o light.o intersect.o camera.o object.o math.o geom.o

all: raytracer

raytracer: $(OBJS)
	$(CC) $(OBJS) -o raytracer $(LIBS)

main.o: main.cpp
	$(CC) -c main.cpp $(LIBS)

renderer.o: renderer.cpp
	$(CC) -c renderer.cpp

light.o: light.cpp
	$(CC) -c light.cpp

intersect.o: intersect.cpp
	$(CC) -c intersect.cpp

camera.o: camera.cpp
	$(CC) -c camera.cpp

object.o: object.cpp
	$(CC) -c object.cpp

math.o: math.cpp
	$(CC) -c math.cpp

scene.o: geom.cpp
	$(CC) -c geom.cpp

clean:
	rm -rf *o $(OBJS)
