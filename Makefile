wop: main.c characters.c combat.c dialogue.c items.c locations.c magic.c
	gcc -o wop main.c characters.c combat.c dialogue.c items.c locations.c magic.c -I.

clean:
	-rm -f *.o
