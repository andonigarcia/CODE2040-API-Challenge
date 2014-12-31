# Andoni Garcia. 2014.

.PHONY: clean

SRC = json.c httppost.c

register: CODE2040.h $(SRC) registration.c 
	gcc -Wall -o register $(SRC) registration.c -lm

stageI: CODE2040.h $(SRC) stage_I.c
	gcc -Wall -o stageI $(SRC) stage_I.c -lm

stageII: CODE2040.h $(SRC) stage_II.c
	gcc -Wall -o stageII $(SRC) stage_II.c -lm

clean:
	rm -rf register stageI stageII