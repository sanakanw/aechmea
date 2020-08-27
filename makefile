
default: build run

build:
	gcc -lglfw -lGL -lGLEW -lm src/*.c

clean:
	rm -r ./a.out

run:
	./a.out
