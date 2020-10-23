
default: build run

build:
	gcc -lglfw -lGL -lGLEW -lm src/*.c -o bin/loli

debug:
	gcc -g -lglfw -lGL -lGLEW -lm src/*.c -o bin/loli

clean:
	rm -r ./a.out

run:
	./bin/loli
