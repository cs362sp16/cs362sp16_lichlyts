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
    int oldHandCount, newHandCount;
    
    printf("CARDTEST1: SMITHY\n");
    
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);
    
    //TEST SMITHY
    result = cardEffect(smithy, 0, 0, 0, &state, 1, NULL);
    oldHandCount = numHandCards(&state);
    assertc(result, "Smithy completely failed");
    
    newHandCount = numHandCards(&state);
    assertc(oldHandCount != newHandCount, "Didn't draw cards");
    
    checkFail();
    
    return 0;
}