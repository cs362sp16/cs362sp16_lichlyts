#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int failed = 0;

void assertc(int a, char *msg) {
    //succeeds on 0
    if (a != 0) {
        printf("FAILED ASSERTION: %s\n", msg);
        failed = 1;
    }
}

void assertSame(int a, int b, char *msg) {
    if (a != b) {
        printf("FAILED ASSERTION: %s\n", msg);
        failed = 1;
    }
}

void assertDiff(int a, int b, char *msg) {
    if (a == b) {
        printf("FAILED ASSERTION: %s\n", msg);
        failed = 1;
    }
}

void checkFail() {
    if (!failed) {
        printf("TEST SUCCESSFULY COMPLETED!\n");
    }
}

#define NUM_TESTS 1000

int main(int argc, char *argv[]) {
    
    int numPlayers = 0, seed = 0, player = 0, outpostCountBefore = 0, outpostCountAfter = 0, handCountBefore = 0, handCountAfter = 0, failed = 0, passed = 0;
    int kingdomCards[10] = {smithy, adventurer, gardens, embargo, cutpurse, mine, ambassador, outpost, baron, tribute};
    struct gameState state;
    
    if (argc != 2) {
        printf("A random seed is required!\n");
        return 1;
    } else {
        char *input = argv[1];
        seed = atoi(input);
        printf("Seed: %i\n", seed);
    }
    
    printf("Testing Outpost Card!\n");
    
    // seed random with our given seed
    srand(seed);
    
    int i = 0;
    for (i = 0; i < NUM_TESTS; i++) {
        
        // generate random number of players, always have at least two
        numPlayers = (rand() % 2) + 2;
        
        initializeGame(numPlayers, kingdomCards, seed, &state);
        
        // start with first player
        player = 0;
        
        // randomize number of cards in deck, discard, and hand up to their max value
        state.deckCount[player] = rand() % MAX_DECK;
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % MAX_DECK;
        
        // every 200 tests make player's deck count zero
        if (i % 200 == 0) {
            state.deckCount[player] = 0;
        }
        
        // get before details
        outpostCountBefore = state.outpostPlayed;
        handCountBefore = state.handCount[player];
        
        // play outposts
        cardEffect(outpost, 0, 0, 0, &state, 0, 0);
        
        // get after details
        outpostCountAfter = state.outpostPlayed;
        handCountAfter = state.handCount[player];
        
        // compare before and after details
        if (outpostCountAfter != outpostCountBefore + 1) {
            failed++;
            printf("COUNT FAILURE!\n");
            printf("Before: %i\n", outpostCountBefore);
            printf("After: %i\n", outpostCountAfter);
        } else if (handCountAfter != handCountBefore - 1) {
            failed++;
            printf("HAND FAILURE!\n");
            printf("Before: %i\n", handCountBefore);
            printf("After: %i\n", handCountAfter);
        } else {
            passed++;
        }
        
    }
    
    // print overall stats
    printf("\nTests Run: %i | Tests Passed: %i | Tests Failed: %i\n", NUM_TESTS, passed, failed);
    
    return 0;
}