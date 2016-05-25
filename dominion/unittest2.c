#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>

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

int main() {
    int numPlayers = 2;
    int kingdomCards[10] = {smithy, adventurer, gardens, embargo, cutpurse, mine, ambassador, outpost, baron, tribute};
    int randomSeed = 15;
    struct gameState state;
    int result = 0;
    
    printf("UNITTEST2: WHOSE TURN\n");
    
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);
    result = whoseTurn(&state);
    assertc(result == 1, "Should be Player 1's turn");
    
    checkFail();
    
    return 0;
}