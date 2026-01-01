##
# Simulator in raylib
#
# @file
# @version 0.1


raylib: main.c
	gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o program

clean:
	rm -f program

run:
	./program

# end
