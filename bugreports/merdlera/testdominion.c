#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"

int main(int argc, char *argv[]) {
    
    // initialize variables
    int i = 0, j = 0, n = 0;
    int numPlayers = 0;
    int kingdomCards[10] = {8, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int card = 0;
    char *cardName = (char*)malloc(sizeof(char) * 20);
    int check = 0;
    int seed = 0;
    int result = 1;
    int winners[4];
    
    // do this so I can just put "state" in method calls, much cleaner
    struct gameState G;
    struct gameState *state = &G;
    
    // get seed
    if (argc != 2) {
        printf("NEED ONLY A SEED");
        return 1;
    }
    
    printf("***Initializing Game ***\n");
    
    // seed random
    seed = atoi(argv[1]);
    srand(seed);
    
    // get number of players (from 2 - 4)
    numPlayers = (rand() % 3) + 2;
    
    // get kingdom cards
    for (i = 0; i < 10; i++) {
        card = (rand() % 20) + 7;
        
        // check if card already in deck
        for (j = 0; j < i; j++) {
            if (card == kingdomCards[j]) {
                check = 1;
            } else {
                check = 0;
            }
            
            // if card is in deck @ j, decrement i to choose new card, break out of j loop
            if (check) {
                i--;
                break;
            } else {
                kingdomCards[i] = card;
                char *handCard = (char*)malloc(sizeof(char) * 20);
                cardNumToName(card, cardName);
                cardNumToName(kingdomCards[i], handCard);
                if (i == 0) { printf("Card: %s\nHand: %s\n", cardName, handCard); }
            }
        }
    }
    
    // initialize dominion.c
    result = initializeGame(numPlayers, kingdomCards, seed, state);
    if (result != 0) {
        printf("Game failed to initialize\n");
        return 2;
    }
    
    // print initialized values
    printf("Initialized game with values:\n");
    printf("Players: %i\n", numPlayers);
    printf("Cards: ");
    for (i = 0; i < 10; i++) {
        cardNumToName(kingdomCards[i], cardName);
        if (i == 0) {
            printf("%s", cardName);
        } else {
            printf(", %s", cardName);
        }
    }
    printf("\n");
    
    // start playing game
    printf("***Starting Game***\n");
    
    while (!isGameOver(state)) {
        int currentCard = 0;
        int actualCard = 0;
        int playersTurn = whoseTurn(state);
        printf("Player %i's turn\n", playersTurn + 1);
        
        //start actions
        printf("*Action Phase*\n");
        for (i = 0; i < numHandCards(state); i++) {
            // make sure card is a kingdom card
            if (handCard(i, state) >= adventurer && handCard(i, state) <= treasure_map && handCard(i, state) != feast && handCard(i, state) != tribute) {
                currentCard = i;
                actualCard = handCard(currentCard, state);
                cardNumToName(actualCard, cardName);
                printf("Card: %s\n", cardName);
                break;
            }
        }
        
        // perform actions
        printf("Actions left: %i\n", state->numActions);
        while (state->numActions > 0 && currentCard != 0) {
            cardNumToName(actualCard, cardName);
            
            // select random cards, better than static
            int one = rand() % state->handCount[playersTurn] + 1;
            int two = rand() % state->handCount[playersTurn] + 1;
            int three = rand() % state->handCount[playersTurn] + 1;
            result = playCard(currentCard, one, two, three, state);
            if (result == -1) {
                printf("Error: Could not play %s\n", cardName);
                discardCard(0, playersTurn, state, 0);
                break;
            } else {
                printf("Played: %s\n", cardName);
            }
            
            if (state->numActions == 0) {
                printf("Out of actions! Move to buy phase\n");
                break;
            }
            
            for (i = currentCard; i < numHandCards(state); i++) {
                if (handCard(i, state) >= adventurer && handCard(i, state) <= treasure_map && handCard(i, state) != feast && handCard(i, state) != tribute) {
                    currentCard = i;
                    actualCard = handCard(currentCard, state);
                    cardNumToName(actualCard, cardName);
                    printf("Other Card: %s\n", cardName);
                    break;
                } else {
                    currentCard = 0;
                }
            }
        }
        
        //start buy phase
        printf("*Buy Phase*\n");
        
        // figure out how many coins the user has
        int coins = 0;
        for (i = 0; i < numHandCards(state); i++) {
            if (handCard(i, state) == copper) {
                coins += 1;
            } else if (handCard(i, state) == silver) {
                coins += 2;
            } else if (handCard(i, state) == gold) {
                coins += 3;
            }
        }
        state->coins = coins;
        
        printf("Number of buys: %i\n", state->numBuys);
        
        // perform random buys
        int m = 0;
        while (state->numBuys > 0) {
            do {
                int available = 0;
                while (!available) {
                    // buy random card from kingdom cards
                    int randCard = rand() % 28;
                    // if rand card is a global kingdom card, check if available this round
                    if (randCard >= adventurer) {
                        for (i = 0; i < 10; i++) {
                            if (randCard == kingdomCards[i]) {
                                available = 1;
                                currentCard = randCard;
                                break;
                            }
                        }
                        // if not king card, try to buy
                    } else {
                        available = 1;
                        currentCard = randCard;
                    }
                }
                
                // Move on to buying specific items if taking too long
                m++;
                if (m == 20) {
                    currentCard = gold;
                } else if (m == 21) {
                    currentCard = silver;
                } else if (m > 21) {
                    currentCard = copper;
                }
                
            } while (buyCard(currentCard, state) != 0);
            
            cardNumToName(currentCard, cardName);
            printf("Bought %s\n", cardName);
        }
        
        printf("Out of buys! Next player's turn\n\n");
        endTurn(state);
        
        // stop game if each player has had 100 turns, no winners
        n++;
        if (n > 200) {
            break;
        }
    }
    
    getWinners(winners, state);
    for (i = 0; i < numPlayers; i++) {
        if (winners[i] == 1) {
            printf("Player %i wins!\nScore: %i\n", i + 1, scoreFor(i, state));
            break;
        }
    }
    
    printf("\n****Game Ended****\n");
    
    return 0;
}
