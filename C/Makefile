# Andoni Garcia. 2014.

.PHONY: clean

CC = gcc
CFLAGS = -o
SRC = json.c httppost.c

register: CODE2040.h $(SRC) registration.c 
	$(CC) $(CFLAGS) register $(SRC) registration.c

stageI: CODE2040.h $(SRC) stage_I.c
	$(CC) $(CFLAGS) stageI $(SRC) stage_I.c

stageII: CODE2040.h $(SRC) stage_II.c
	$(CC) $(CFLAGS) stageII $(SRC) stage_II.c

stageIII: CODE2040.h $(SRC) stage_III.c
	$(CC) $(CFLAGS) stageIII $(SRC) stage_III.c

stageIV: CODE2040.h $(SRC) stage_IV.c
	$(CC) $(CFLAGS) stageIV $(SRC) stage_IV.c

clean:
	rm -rf register stageI stageII stageIII stageIV