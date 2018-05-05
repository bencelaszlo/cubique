all:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/texture.c src/utils.c src/collision_detection.c src/io.c -lSOIL -lobj -lGL -lGLU -lglut -lm -o cubique -Wall -Wextra -Wpedantic
