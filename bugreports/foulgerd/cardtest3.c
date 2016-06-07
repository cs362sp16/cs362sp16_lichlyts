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
    int kingdomCards[10] = {smithy, adventurer, gardens, embargo, great_hall, mine, ambassador, outpost, baron, tribute};
    int randomSeed = 15;
    struct gameState state;
    int result = 0;
    int oldHandCount, newHandCount;
    int oldActionCount, newActionCount;
    
    printf("CARDTEST3: GREAT HALL\n");
    
    initializeGame(numPlayers, kingdomCards, randomSeed, &state);
    oldHandCount = numHandCards(&state);
    oldActionCount = state.numActions;
    
    //int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);
    
    //TEST GREAT HALL
    result = cardEffect(great_hall, 0, 0, 0, &state, 1, NULL);
    assertc(result, "Completely failed Great Hall");
    
    newHandCount = numHandCards(&state);
    assertSame(oldHandCount, newHandCount, "Hand sizes aren't the same");
    
    newActionCount = state.numActions;
    assertDiff(oldActionCount, newActionCount, "Actions didn't change");
    if (newActionCount == oldActionCount + 1) {
        result = 0;
    }
    assertc(result, "Actions didn't increment by 1");
    
    checkFail();
    
    return 0;
}