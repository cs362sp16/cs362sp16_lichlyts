CFLAGS = -Wall -fpic -coverage -lm -std=c11

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

randomtestadventurer: dominion.o rngs.o
	gcc -std=c11 dominion.o rngs.o randomtestadventurer.c -o randomtestadventurer $(CFLAGS)

randomtestcard1: dominion.o rngs.o
	gcc -std=c11 dominion.o rngs.o randomtestcard1.c -o randomtestcard1 $(CFLAGS)

randomtestcard2: dominion.o rngs.o
	gcc -std=c11 dominion.o rngs.o randomtestcard2.c -o randomtestcard2 $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer 90 &> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	make clean

randomtestcard1.out: randomtestcard1
	./randomtestcard1 42 &> randomtestcard1.out
	gcov -f -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	make clean

randomtestcard2.out: randomtestcard2
	./randomtestcard2 42 &> randomtestcard2.out
	gcov -f -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	make clean

randomtestsuite: randomtestadventurer randomtestcard1 randomtestcard2
	
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

testdom: dominion.o interface.o
	gcc dominion.o interface.o rngs.o testdominion.c -o testdom $(CFLAGS)

testdominion.out: testdom
	./testdom 42 &> testdominion.out
	gcov dominion.c >> testdominion.out
	cat dominion.c.gcov >> testdominion.out
	make clean

all: playdom player testsuite randomtestsuite testdom

clean:
	rm -rf *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer testdom player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM
