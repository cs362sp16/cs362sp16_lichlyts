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
    
    int numPlayersNormal = 2;
    int numPlayersAbnormal = 4000;
    int kingdomCardsAcceptable[10] = {smithy, adventurer, gardens, embargo, cutpurse, mine, ambassador, outpost, baron, tribute};
    int kingdomCardsUnacceptable[10] = {smithy, adventurer, gardens, embargo, embargo, cutpurse, mine, ambassador, outpost, baron};
    int randomSeed = 11;
    struct gameState state;
    int result = 0;
    
    printf("UNITTEST1: INITIALIZE GAME\n");
    
    result = initializeGame(numPlayersNormal, kingdomCardsAcceptable, randomSeed, &state);
    assertc(result, "No duplicates, 2 players");
    
    result = initializeGame(numPlayersNormal, kingdomCardsUnacceptable, randomSeed, &state);
    assertSame(result, -1, "Duplicate kingdom cards, 2 players");
    
    result = initializeGame(numPlayersAbnormal, kingdomCardsAcceptable, randomSeed, &state);
    assertc(result, "Lots of players");
    
    checkFail();
    
    return 0;
}