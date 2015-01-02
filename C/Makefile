# Andoni Garcia. 2014.

.PHONY: clean

SRC = json.c httppost.c

register: CODE2040.h $(SRC) registration.c 
	gcc -Wall -o register $(SRC) registration.c -lm

stageI: CODE2040.h $(SRC) stage_I.c
	gcc -Wall -o stageI $(SRC) stage_I.c -lm

stageII: CODE2040.h $(SRC) stage_II.c
	gcc -Wall -o stageII $(SRC) stage_II.c -lm

stageIII: CODE2040.h $(SRC) stage_III.c
	gcc -Wall -o stageIII $(SRC) stage_III.c -lm

stageIV: CODE2040.h $(SRC) stage_IV.c
	gcc -Wall -o stageIV $(SRC) stage_IV.c -lm

clean:
	rm -rf register stageI stageII stageIII stageIV