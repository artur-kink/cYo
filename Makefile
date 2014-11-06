all: yo

yo: yo.c cyo.c
	gcc yo.c cyo.c -lcurl -o yo

clean:
	rm *.o
	rm yo
