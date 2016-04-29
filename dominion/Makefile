CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest1: 
	gcc dominion.c unittest1.c rngs.c -o unittest1 $(CFLAGS)

unittest2:
	gcc dominion.c unittest2.c rngs.c -o unittest2 $(CFLAGS)

unittest3:
	gcc dominion.c unittest3.c rngs.c -o unittest3 $(CFLAGS)

unittest4:
	gcc dominion.c unittest4.c rngs.c -o unittest4 $(CFLAGS)

cardtest1:
	gcc dominion.c cardtest1.c rngs.c -o cardtest1 $(CFLAGS)

cardtest2:
	gcc dominion.c cardtest2.c rngs.c -o cardtest2 $(CFLAGS)

cardtest3:
	gcc dominion.c cardtest3.c rngs.c -o cardtest3 $(CFLAGS)

cardtest4:
	gcc dominion.c cardtest4.c rngs.c -o cardtest4 $(CFLAGS)

testsuite: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	
unittestresults.out: testsuite
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	make clean

all: playdom player testsuite

clean:
	rm -rf *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM
