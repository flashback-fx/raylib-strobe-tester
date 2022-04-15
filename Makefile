all: strobe strobe_vsync

strobe: strobe.c
	gcc -std=c99 -Wall -Wextra -pedantic strobe.c -o strobe -lraylib -lGL -lm -pthread -ldl -lrt -lX11
strobe_vsync: strobe.c
	gcc -std=c99 -Wall -Wextra -pedantic -D VSYNC strobe.c -o strobe_vsync -lraylib -lGL -lm -pthread -ldl -lrt -lX11
