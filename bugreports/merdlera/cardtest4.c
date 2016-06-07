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
    int oldOutpost, newOutpost;
    
    printf("CARDTEST4: OUTPOST\n");
    
    //int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
    
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);
    oldOutpost = state.outpostPlayed;
    
    result = cardEffect(outpost, 0, 0, 0, &state, 1, NULL);
    assertc(result, "Outpost completely failed");
    
    newOutpost = state.outpostPlayed;
    assertDiff(oldOutpost, newOutpost, "Outposts Played aren't different");
    assertSame(newOutpost, 1, "Outposts Played != 1");
    
    checkFail();
    
    return 0;
}