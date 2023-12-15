/*
 SolitairePoker.c
 
 Notes: The 52 cards of a deck are represented as integers: 0 .. 51
 0..12 are clubs Ace, 2, ..., King
 13..25 are diamonds Ace, 2, ..., King
 26..38 are hearts Ace, 2, ..., King
 39..51 are spades Ace, 2, ..., King

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//do not remove
#include "include.code" //Include custom header file (it contains necessary functions)
//A version of the file:include.code is available from the assignment page
//as studentinclude.code which you should save locally as include.code
//include.code contains implementations for seed, instructions, and private_nextcard(int)
//used by shuffle and next card.
//The version used during testing is slightly different but will not affect your efforts.
//For testing you may modify studentinclude.code -- it will not be part of your submission.


// Function to shuffle the deck
//you should call this before each deal (including the first)
void shuffle() {
    private_nextcard(1); // Call a custom function to shuffle
}

// Function to get the next card to be dealt
//call this to deal a card. Do not call rand().
int nextcard() {
    return private_nextcard(0); // Call a custom function to get the next card
}


// Enumeration for different poker hands
enum hands { UNKNOWN, HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT,
    FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH };
char * handNames[] ={ "UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    "FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand

// Enumeration for card suits
enum suits {CLUB, DIAMOND, HEART, SPADE};
char * suitNames[] ={ "CLUB", "DIAMOND", "HEART", "SPADE"}; // Names of card suits

// Enumeration for card ranks
enum ranks {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
char * rankNames[] ={ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
    "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"}; // Names of card ranks

//FUNCTION PROTOTYPES: YOU MUST IMPLEMENT THESE FUNCTIONS

// Function to get the rank of a card
enum ranks getrank(int card);

// Function to get the suit of a card
enum suits getsuit(int card);
        
// Function to evaluate the poker hand
enum hands eval(int []);

// Function to check for a royal flush
int royalflush(int []);

// Function to check for a straight flush
int straightflush(int []);

// Function to check for four of a kind
int fourofkind(int []);

// Function to check for a full house
int fullhouse(int []);

// Function to check for a flush
int flush(int []);

// Function to check for a straight
int straight(int []);

// Function to check for three of a kind
int threekind(int []);

// Function to check for two pairs
int twopair(int []);

// Function to check for a pair
int pair(int []);

//Function to calculate the score
int score(int []);

//Function to draw 5 cards and print result
void drawCards(int []);

//Function to draw new cards
void drawNewCards(int hand[]);



int main(int argc, char ** argv) {
    //do not remove
    seed(argc, argv); // Seed the random number generator
    // Display game instructions
    instructions();

    //TODO:
        //WRITE CODE TO PLAY 10 HANDS OF POKER
            //DEAL 5 CARDS
            //SHOW DEALT HAND
            //DRAW UP TO 3 CARDS
            //SHOW FINAL HAND
            //EVAL REPPORT AND SAVE INFO FOR LATER
        //GENERATE SCORESHEET USING INFO
    
    int gameNum = 0;
    int hand[5];
    int i;
    int scoreArray[10] = {0};
    char handArray[10][15];
    int scoreVal;
    int cardNumArray[50] = {0};
    int num = 0;

    
    while(gameNum < 10){

        int num2 = 0; //used to set the hand index to zero 
        
        shuffle();  //shuffles the deck

        drawCards(hand); //draws 5 cards and prints the result

        drawNewCards(hand);  //prompts the user to draw up to 3 new cards and prints the new cards

        for(i = num; i < (num+5); ++i){    //stores the card numbers in an array (used to print the scoresheet later)
            cardNumArray[i] = hand[num2];
            num2 = num2 + 1;
        }
        scoreVal = score(hand);  //calculates the score

        printf("\n");
            
        enum hands handType = eval(hand);  //evaluates the hand

        strcpy(handArray[gameNum], handNames[handType]); //copies the hand to an array
            
        scoreArray[gameNum] = scoreVal; // copies the score to an array

        printf("Hand %2d: Score:%6d %-13s\n", gameNum+1, scoreArray[gameNum], handArray[gameNum]); //prints the round result

        printf("\n");
        gameNum = gameNum + 1;
        num = num + 5;  //starts card number array at whatever number it was last stopped at (+5 each time)
    
    }


    int totalPoints = 0;

    for(i = 0; i < 10; ++i){
        totalPoints = totalPoints + scoreArray[i];   //calculates the total points using the score array 
    }

    for(i = 0; i < 50; ++i){
        printf("%d\n", cardNumArray[i]);
    }

    printf("\n");

    
    
    printf("********************************************************************************\n");
    printf("***                         S C O R E S H E E T                              ***\n");
    printf("********************************************************************************\n");
    int num2 = 0;
    for(i = 0; i < 50; i = i+5){
        num2 = num2 + 1; //used to print the scoreArray and handArray which both have 10 items (can't use i because it is incremented by 5 and not 1)
        printf("Hand %2d: Score:%6d %-13s [%d %s-%s %d %s-%s %d %s-%s %d %s-%s %d %s-%s]\n", num2, scoreArray[num2-1], handArray[num2-1], 
        cardNumArray[i], suitNames[getsuit(cardNumArray[i])], rankNames[getrank(cardNumArray[i])], 
        cardNumArray[i+1], suitNames[getsuit(cardNumArray[i+1])], rankNames[getrank(cardNumArray[i+1])], 
        cardNumArray[i+2], suitNames[getsuit(cardNumArray[i+2])], rankNames[getrank(cardNumArray[i+2])], 
        cardNumArray[i+3], suitNames[getsuit(cardNumArray[i+3])], rankNames[getrank(cardNumArray[i+3])], 
        cardNumArray[i+4], suitNames[getsuit(cardNumArray[i+4])], rankNames[getrank(cardNumArray[i+4])]);
    }
    printf("==============================================================================\n");
    printf("Total points:      %d\n", totalPoints);
    printf("==============================================================================\n"); 



    return 0;
}

//TODO:
//THE FOLLOWING STUBS NEED TO BE IMPLEMENTED CORRECTLY


//Function to draw 5 cards and print the result
void drawCards(int hand[]){
 
    int i;
    
    for(i = 0; i < 5; ++i){  
        hand[i] = nextcard();
        printf("%d, ", hand[i]);
        }

    printf("\n");

}

//Function to calculate the score
int score(int hand[]){
    
    int score1;
    
    if(royalflush(hand)==1){
        score1 = 50;
            }

    else if(straightflush(hand)==1){
        score1 = 45;
            }

    else if(fourofkind(hand)==1){
        score1 = 40;
            }

    else if(fullhouse(hand)==1){
        score1 = 32;
            }

    else if(flush(hand)==1){
        score1 = 26;
            }

    else if(straight(hand)==1){
        score1 = 17;
            }

    else if(threekind(hand)==1){
        score1 = 11;
            }

    else if(twopair(hand)==1){
        score1 = 7;
            }

    else if(pair(hand)==1){
        score1 = 3;
            }

    else{
        score1 = 1;
            }

    return score1;

}


// Function to get the suit of a card
enum suits getsuit(int card){
    
    if(card >= 0 && card <= 12){
        return CLUB;
    }
            
    else if(card >= 13 && card <= 25){
        return DIAMOND;
    }
            
    else if(card >= 26 && card <= 38){
        return HEART;  
    }             

    else if(card >= 39 && card <= 51){
        return SPADE;
    }

    return 0;
}

// Function to get the rank of a card
enum ranks getrank(int card){
    
    if(card % 13 == 0){
        return ACE;
    }
    else if(card % 13 == 1){
        return TWO;
    }
    else if(card % 13 == 2){
        return THREE;
    }
    else if(card % 13 == 3){
        return FOUR;
    }
    else if(card % 13 == 4){
        return FIVE;
    }
    else if(card % 13 == 5){
        return SIX;
    }
    else if(card % 13 == 6){
        return SEVEN;
    }
    else if(card % 13 == 7){
        return EIGHT;
    }
    else if(card % 13 == 8){
        return NINE;
    }
    else if(card % 13 == 9){
        return TEN;
    }
    else if(card % 13 == 10){
        return JACK;
    }
    else if(card % 13 == 11){
        return QUEEN;
    }
    else if(card % 13 == 12){
        return KING;
    }

    return 0;
}

// Function to evaluate the poker hand
enum hands eval(int hand[]){

    if (royalflush(hand) == 1) {
        return ROYALFLUSH;
    } else if (straightflush(hand) == 1) {
        return STRAIGHTFLUSH;
    } else if (fourofkind(hand) == 1) {
        return QUADS;
    } else if (fullhouse(hand) == 1) {
        return FULLHOUSE;
    } else if (flush(hand) == 1) {
        return FLUSH;
    } else if (straight(hand) == 1) {
        return STRAIGHT;
    } else if (threekind(hand) == 1) {
        return TRIPS;
    } else if (twopair(hand) == 1) {
        return TWOPAIR;
    } else if (pair(hand) == 1) {
        return PAIR;
    } else {
        return HIGHCARD;
    }

}

//Function to draw new cards 
void drawNewCards(int hand[]) {
    int i;

    printf("Select up to three cards to replace [1-5] and press enter\n");

    char str[8];
    
    fgets(str, 7, stdin);

    for(i = 0; i < strlen(str); ++i){
        if(isdigit(str[i])){
            if(str[i] == '1'){
                hand[0] = nextcard();
            }
            else if(str[i] == '2'){
                hand[1] = nextcard();
            }
            else if(str[i] == '3'){
                hand[2] = nextcard();
            }
            else if(str[i] == '4'){
                hand[3] = nextcard();
            }
            else if(str[i] == '5'){
                hand[4] = nextcard();
            }
    }
    }
    
    for(i = 0; i < 5; ++i){
        printf("%d, ", hand[i]);
    }
}


int royalflush(int hand[]) {
    for (int i = 1; i < 5; ++i) {
        if (getsuit(hand[i]) != getsuit(hand[0])) {
            return 0; // Not a royal flush if suits are different
        }
    }

    int ranks[] = {ACE, KING, QUEEN, JACK, TEN};
    
    // Check if all expected ranks are present in the hand
    for (int i = 0; i < 5; ++i) {
        int found = 0;
        for (int j = 0; j < 5; ++j) {
            if (getrank(hand[j]) == ranks[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0; // Not a royal flush if any expected rank is missing
        }
    }

    return 1;
}



int straightflush(int hand[]) {
    int i, j;
    int ranks[5];

    // Check if all cards have the same suit
    int suitCompare = getsuit(hand[0]);
    for (i = 1; i < 5; ++i) {
        if (getsuit(hand[i]) != suitCompare) {
            return 0; 
        }
    }

    // Get card ranks
    for (i = 0; i < 5; ++i) {
        ranks[i] = getrank(hand[i]);
    }

    // Sort the ranks 
    for (i = 0; i < 4; ++i) {
        for (j = i + 1; j < 5; ++j) {
            if (ranks[i] > ranks[j]) {
                // Swap ranks[i] and ranks[j]
                int temp = ranks[i];
                ranks[i] = ranks[j];
                ranks[j] = temp;
            }
        }
    }

    // Check if the sorted ranks are in order
    for (i = 0; i < 4; ++i) {
        if (ranks[i] + 1 != ranks[i + 1]) {
            if (!(i == 0 && ranks[i] == KING && ranks[i + 1] == ACE)) {
                return 0; // Not a straight flush
            }
        }
    }

    return 1;
}


// Function to check for a flush
int flush(int hand[]){
    

    if(getsuit(hand[0]) == getsuit(hand[1]) && getsuit(hand[1]) == getsuit(hand[2]) && getsuit(hand[2]) == getsuit(hand[3]) && getsuit(hand[3]) == getsuit(hand[4])){
        return 1;
    }


    return 0;
}

// Function to check for a straight
int straight(int hand[]){

    int ranks[5];
    
    for (int i = 0; i < 5; ++i) {
        ranks[i] = getrank(hand[i]);
    }

    // Sort ranks in ascending order
    for (int i = 0; i < 5 - 1; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            if (ranks[i] > ranks[j]) {
                int temp = ranks[i];
                ranks[i] = ranks[j];
                ranks[j] = temp;
            }
        }
    }

    // Check for consecutive ranks
    for (int i = 0; i < 5 - 1; ++i) {
        if (ranks[i] + 1 != ranks[i + 1]) {
            // Check for special case: Ace connecting with 2
            if (!(i == 0 && ranks[i] == ACE && ranks[i + 1] == TWO)) {
                return 0;
            }
        }
    }
    

    return 1;
}

// Function to check for four of a kind
int fourofkind(int hand[]){
    int i, j;
    int count;

    for(i = 0; i < 5; ++i){
        count = 1;
        for(j = i + 1; j < 5; ++j){
            if(getrank(hand[i]) == getrank(hand[j])){
                count = count + 1;
                if(count == 4){
                    return 1;
                }
        }
    }
    }
    
    return 0;
}

// Function to check for a full house
int fullhouse(int hand[]){
    
    int rankCount[13] = {0};
    int i, index;
    int check1 = 0;
    int check2 = 0;

    for(i = 0; i < 5; ++i){
        index = getrank(hand[i]);
        rankCount[index] = rankCount[index] + 1;
    }

    for(i = 0; i < 13; ++i){
        if(rankCount[i] == 3){
            check1 = 1;
        }
        if(rankCount[i] == 2){
            check2 = 1;
        }
    }

    if(check1 == 1 && check2 == 1){
        return 1;
    }


    return 0;
}

// Function to check for three of a kind
int threekind(int hand[]){
    int rankCount[13] = {0};
    int i, index;

    for(i = 0; i < 5; ++i){
        index = getrank(hand[i]);
        rankCount[index] = rankCount[index] + 1;
    }

    for(i = 0; i < 13; ++i){
        if(rankCount[i] == 3){
            return 1;
    }
    }

    return 0;
}

// Function to check for two pairs
int twopair(int hand[]){
    int rankCount[13] = {0};
    int i, index;
    int same = 0;

    for(i = 0; i < 5; ++i){
        index = getrank(hand[i]);
        rankCount[index] = rankCount[index] + 1;
    }

    for(i = 0; i < 13; ++i){
        if(rankCount[i] == 2){
            same = same + 1;
        }
    }

    if(same == 2){
        return 1;
    }

    return 0;
}

// Function to check for a pair
int pair(int hand[]){

    int rankCount[13] = {0};
    int i, index;

    for(i = 0; i < 5; ++i){
        index = getrank(hand[i]);
        rankCount[index] = rankCount[index] + 1;
    }

    for(i = 0; i < 13; ++i){
        if(rankCount[i] == 2){
            return 1;
        }
    }
    
    return 0;
}
