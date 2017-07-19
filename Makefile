bjp: main.c tcp.c
	gcc -o bjp main.c tcp.c -l ncurses -I. -g
clean:
	rm -f *.o bjp
