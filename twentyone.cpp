/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  int n = NUM_CARDS;
  for(int i = n - 1; i > 0; i--){
    int j = rand() % (i + 1);
    int valueAtJ = cards[j];
    int valueAtI = cards[i];
    cards[j] = valueAtI;
    cards[i] = valueAtJ;
  }
}



/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
  /******** You complete ****************/
  int typeIndex = id % 13; //takes the modulo based off the ammount of cards there are in a suit of cards
  int suitIndex = id / 13;

  cout << type[typeIndex] << "-" << suit[suitIndex];
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int cardValue = value[id%13];
  return cardValue;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for(int i = 0; i<=numCards; i++){
    printCard(hand[i]);
    cout << " ";
  }
  cout << endl;

}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  //find out if ace will be 1 or 11
  //ace should be 1 if phand is more than 21 at 11
  int sumOfHand = 0;
  for(int i = 0; i <= numCards; i++){
      sumOfHand += cardValue(hand[i]);
  }

  for (int i = 0; i <= numCards; i++) {
    if (cardValue(hand[i]) == 11) {
      if (sumOfHand > 21) {
        sumOfHand = sumOfHand - 10;
      }
    }
  }
  return sumOfHand; 
}

int dealCard(int hand[], int cards[], int dealtCards, int handIndex) {
  hand[handIndex] = cards[dealtCards];
  return getBestScore(hand, handIndex);
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/

  /* Initiate cards */
  int dealtCardsIndex = -1; 
  int playerHandIndex = -1;
  int dealerHandIndex = -1;

  for (int i = 0; i < 52; i++) {
    cards[i] = i;
  }

  shuffle(cards);

  /* Deals out the first hand for dealer and player */
  playerHandIndex++;
  dealtCardsIndex++;
  phand[playerHandIndex] = cards[dealtCardsIndex];
  dealerHandIndex++;
  dealtCardsIndex++;
  dhand[dealerHandIndex] = cards[dealtCardsIndex];
  playerHandIndex++;
  dealtCardsIndex++;
  phand[playerHandIndex] = cards[dealtCardsIndex];
  dealerHandIndex++;
  dealtCardsIndex++;
  dhand[dealerHandIndex] = cards[dealtCardsIndex];


  /* Prints starting cards */
  cout << "Dealer:" << " ? ";
  printCard(dhand[1]);
  cout << endl;
  cout << "Player: ";
  printHand(phand, playerHandIndex);



  char userInput; 
  while (userInput != 'h' || userInput != 's') { //checks to see if the user wants to hit or stand and if so continues with the while loop 
    int initialScore = getBestScore(phand, playerHandIndex);
    if (initialScore != 21) {
      cout << "Type 'h' to hit and 's' to stay:" << endl; //asks user if they want to ht or stand 
      cin >> userInput;
    }
    if (userInput == 'h') { //the if command that runs if the user puts in h for hit 
      dealtCardsIndex++;
      playerHandIndex++;
      int score = dealCard(phand, cards, dealtCardsIndex, playerHandIndex);
      cout << "Player: ";
      printHand(phand, playerHandIndex);
      if (score > 21 ) { // if command if the player busts and gets a score over 21
        cout << "Player busts"; 
        cout << endl;
        cout << "Lose " << getBestScore(phand, playerHandIndex) << " " << getBestScore(dhand, dealerHandIndex);
        cout << endl;
        cout << endl;
        cout << "Play again? [y/n]" << endl; //asks the user if they want to play again or not 
        cin >> userInput;
        if (userInput == 'y') {
          std::fill_n(cards, 52, 0);
          std::fill_n(dhand, 9, 0);
          std::fill_n(phand, 9, 0);
          dealtCardsIndex = -1; 
          playerHandIndex = -1;
          dealerHandIndex = -1;

          for (int i = 0; i < 52; i++) {
            cards[i] = i;
          }

          shuffle(cards); //shuffles cards again if the user wants to play again 

          /* Deals out the first hand for dealer and player */
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];


          /* Prints starting cards */
          cout << "Dealer:" << " ? ";
          printCard(dhand[1]);
          cout << endl;
          cout << "Player: ";
          printHand(phand, playerHandIndex);
            
        } else {
          break;
        }
      } 
      if (score == 21) { //if statement if the dealer has a score of 21 
        int dealerScore = getBestScore(dhand, dealerHandIndex);
        while (dealerScore < 17) {
          dealtCardsIndex++;
          dealerHandIndex++;
          int localScore = dealCard(dhand, cards, dealtCardsIndex, dealerHandIndex);
          dealerScore = localScore;
        }
        cout << "Dealer: ";
        printHand(dhand, dealerHandIndex);
        cout << "Win " << getBestScore(phand, playerHandIndex) << " "  <<  getBestScore(dhand, dealerHandIndex);
        cout << endl; 
        cout << endl;
        cout << "Play again? [y/n]" << endl; //asks the user to play again if they want 
        cin >> userInput;
        if (userInput == 'y') {
          std::fill_n(cards, 52, 0);
          std::fill_n(dhand, 9, 0);
          std::fill_n(phand, 9, 0);
          dealtCardsIndex = -1; 
          playerHandIndex = -1;
          dealerHandIndex = -1;

          for (int i = 0; i < 52; i++) {
            cards[i] = i;
          }

          shuffle(cards);

          /* Deals out the first hand for dealer and player */
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];


          /* Prints starting cards */
          cout << "Dealer:" << " ? ";
          printCard(dhand[1]);
          cout << endl;
          cout << "Player: ";
          printHand(phand, playerHandIndex);
            
        } 
          else{
            break;
          }
      }
    } 
    else if (userInput == 's' || initialScore == 21) { // if statement if the user decides to stand instead of hit 
      int dealerScorecalc = getBestScore(dhand, dealerHandIndex);
      while (dealerScorecalc < 17) {
        dealtCardsIndex++;
        dealerHandIndex++;
        int localScore = dealCard(dhand, cards, dealtCardsIndex, dealerHandIndex);
        dealerScorecalc = localScore;
      }
      cout << "Dealer: ";
      printHand(dhand, dealerHandIndex); 
      int playerScore = getBestScore(phand, playerHandIndex);
      int dealerScore = getBestScore(dhand, dealerHandIndex);
      if (dealerScore > 21 ) {
        cout << "Dealer busts";
        cout << endl;  
        cout << "Win " << playerScore << " " << dealerScore;
        cout << endl; 
        cout << endl;
        cout << "Play again? [y/n]" << endl;
        cin >> userInput;
        if (userInput == 'y') {
          std::fill_n(cards, 52, 0);
          std::fill_n(dhand, 9, 0);
          std::fill_n(phand, 9, 0);
          dealtCardsIndex = -1; 
          playerHandIndex = -1;
          dealerHandIndex = -1;

          for (int i = 0; i < 52; i++) {
            cards[i] = i;
          }

          shuffle(cards);

          /* Deals out the first hand for dealer and player */
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];


          /* Prints starting cards */
          cout << "Dealer:" << " ? ";
          printCard(dhand[1]);
          cout << endl;
          cout << "Player: ";
          printHand(phand, playerHandIndex);
            
        } 
          else {
            break;
          }
      } 
      else if (playerScore > dealerScore) {
        cout << "Win " << playerScore << " " << dealerScore;
        cout << endl;  
        cout << endl;
        cout << "Play again? [y/n]" << endl;
        cin >> userInput;
        if (userInput == 'y') {
          std::fill_n(cards, 52, 0);
          std::fill_n(dhand, 9, 0);
          std::fill_n(phand, 9, 0);
          dealtCardsIndex = -1; 
          playerHandIndex = -1;
          dealerHandIndex = -1;

          for (int i = 0; i < 52; i++) {
            cards[i] = i;
          }

          shuffle(cards);

          /* Deals out the first hand for dealer and player */
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];


          /* Prints starting cards */
          cout << "Dealer:" << " ? ";
          printCard(dhand[1]);
          cout << endl;
          cout << "Player: ";
          printHand(phand, playerHandIndex);
            
        } 
        else {
          break;
        }
      } 
      else if (playerScore == dealerScore) { //if the there is a tie between the player and the dealer 
        cout << "Tie " << playerScore << " " << dealerScore;
        cout << endl;
        cout << endl;
        cout << "Play again? [y/n]" << endl;
        cin >> userInput;
        if (userInput == 'y') {
          std::fill_n(cards, 52, 0);
          std::fill_n(dhand, 9, 0);
          std::fill_n(phand, 9, 0);
          dealtCardsIndex = -1; 
          playerHandIndex = -1;
          dealerHandIndex = -1;

          for (int i = 0; i < 52; i++) {
            cards[i] = i;
          }

          shuffle(cards);

          /* Deals out the first hand for dealer and player */
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];


          /* Prints starting cards */
          cout << "Dealer:" << " ? ";
          printCard(dhand[1]);
          cout << endl;
          cout << "Player: ";
          printHand(phand, playerHandIndex);
            
        } 
        else {
          break;
        }
      } 
      else {
        cout << "Lose " << playerScore << " " << dealerScore; //if the player looses and then asks the user if they want to play again 
        cout << endl;
        cout << endl;
        cout << "Play again? [y/n]" << endl;
        cin >> userInput;
        if (userInput == 'y') {
          std::fill_n(cards, 52, 0);
          std::fill_n(dhand, 9, 0);
          std::fill_n(phand, 9, 0);
          dealtCardsIndex = -1; 
          playerHandIndex = -1;
          dealerHandIndex = -1;

          for (int i = 0; i < 52; i++) {
            cards[i] = i;
          }

          shuffle(cards);

          /* Deals out the first hand for dealer and player */
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];
          playerHandIndex++;
          dealtCardsIndex++;
          phand[playerHandIndex] = cards[dealtCardsIndex];
          dealerHandIndex++;
          dealtCardsIndex++;
          dhand[dealerHandIndex] = cards[dealtCardsIndex];

          /* Prints starting cards */
          cout << "Dealer:" << " ? ";
          printCard(dhand[1]);
          cout << endl;
          cout << "Player: ";
          printHand(phand, playerHandIndex);   
        } 
        else {
          break;
        }
      }
    } 
    else {
      break;
    }
  }
  return 0;
}
