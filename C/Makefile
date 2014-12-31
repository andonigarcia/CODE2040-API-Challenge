# Andoni Garcia. 2014.

.PHONY: clean

SRC = json.c httppost.c

register: CODE2040.h $(SRC) registration.c 
	gcc -Wall -o register $(SRC) registration.c -lm

clean:
	rm -rf register