CFLAGS=-ggdb -Wall -Wextra

all: hello hello.i hello.s

hello.o: main.c
	gcc $(CFLAGS) -Wa,-a=hello.lst -c main.c

hello: hello.o
	gcc $(CFLAGS) -static -Wl,-Map=hello.map -o hello hello.o

hello.i: main.c
	gcc $(CFLAGS) -E main.c > hello.i

hello.s: main.c
	gcc $(CFLAGS) -S main.c

# Type "make verbose" to see the whole command line
verbose:
	gcc -v $(CFLAGS) -Wextra -c main.c

clean:
	rm -f hello hello.o hello.i hello.s