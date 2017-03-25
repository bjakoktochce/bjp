bjp: main.c tcp.c
	gcc -o bjp main.c tcp.c -I.
clean:
	rm -f *.o bjp
