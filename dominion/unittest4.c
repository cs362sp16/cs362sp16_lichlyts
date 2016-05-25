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
    int randomSeed = 22;
    struct gameState state;
    int result = 0;
    int oldNumCards, newNumCards;
    
    printf("UNITTEST4: BUY CARD\n");
    
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);
    oldNumCards = numHandCards(&state);
    
    result = buyCard(3, &state);
    assertc(result, "Failed buyCard");
    
    newNumCards = numHandCards(&state);
    assertDiff(oldNumCards, newNumCards, "Hand sizes aren't different");
    
    checkFail();
    
    return 0;
}