/*if flip = 0, then that's your turn (heads). If flip = 1, then that's the computer's turn (tails). */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

string deck[200], shuffle[200], cardDrop[200], yourDeck[100], pcDeck[100];
string colors[] = {"Red", "Blue", "Green", "Yellow"};
string numbers[] = {" 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9"};
string addOn[] = {" Skip", " +2", " Reverse"};
string wild[] = {"Wild +4", "Wild Card"};
string zero = " 0";
int index[200], shuffleIndex[200], cardDropCount = 0, yourDeckCount = 0, pcDeckCount = 0;

void setUp() {
   int colorCount = 0, numCount = 0, trial = 0;
   for(int i = 0; i < 72; i++) {
      deck[i] = colors[colorCount] + numbers[numCount++];
      if(numCount == 9 && trial != 1) {
         numCount = 0;
         trial = 1;
      }
      else if(numCount == 9 && trial == 1) {
         numCount = 0;
         colorCount++; 
	 trial = 0;
      }
      index[i] = i;
   }

   colorCount = 0;

   for(int i = 72; i < 76; i++) {
      deck[i] = colors[colorCount++] + zero; //adding the zeros for every color.
      index[i] = i;
   }

   colorCount = 0; numCount = 0; trial = 0;

   for(int i = 76; i < 100; i++) { //there's two of each action card. That's why "trial" is implemented.
      deck[i] = colors[colorCount] + addOn[numCount++];
      if(numCount == 3 && trial == 0) {
         numCount = 0;
         trial = 1;
      }
      else if(numCount == 3 && trial == 1) {
         numCount = 0;
         colorCount++;
         trial = 0;
      }
      index[i] = i;
   }

   for(int i = 100; i < 108; i++) {
      if(i <= 103) deck[i] = wild[0];
      else deck[i] = wild[1];
      index[i] = i;
   }
}

void shuffleDeck() {
  shuffleIndex[0] = index[rand() % 108]; //Each index is different. But certain strings are the same property. That's why index gets randomized.
  for(int i = 1; i < 108; i++) {
    bool repeats = true;
    while(repeats) {
      shuffleIndex[i] = index[rand() % 108];
      for(int k = 0; k < i; k++) {
        if(shuffleIndex[k] == shuffleIndex[i]) {
          repeats = true;
          break;
        }
        repeats = false;
      }
    }
  }
  for(int i = 0; i < 108; i++) shuffle[i] = deck[shuffleIndex[i]];
}

int count = 107;

void initialDraw() {
  cout << "This is your set: \n\n";

  int i = 0;
  while(i < 7) {
     yourDeck[i] = shuffle[count];
     shuffle[count] = "";
     cout << i + 1 << "). " << yourDeck[i] << endl;
     i++; count--;
     yourDeckCount++; //this will keep track of the size of your deck. Same goes with pc's deck.
  }

  i = 0;
  while(i < 7) {
     pcDeck[i] = shuffle[count];
     shuffle[count] = "";
     i++; count--;
     pcDeckCount = i + 1; //keeps track of size of PC's deck
  }
}

int flip;
int choice = -1; //in case it's your turn.

void firstTurn() {
  cout << endl << endl << "Flip a coin: (Press ENTER to flip)";
  cin.get();
  flip = rand() % 2;

//PC's turn.
  if(flip == 1) {
    cout << "Tails. PC starts.";
    int n = rand() % 7;
    for(int i = 0; i < pcDeckCount; i++) {
      if(pcDeck[i] == pcDeck[n]) {
        pcDeck[i] = pcDeck[i + 1];
        pcDeckCount--;
      }
    }
    cardDrop[cardDropCount++] = pcDeck[n]; 
  }

//Your turn.
  else {
    cout << "Heads. You start. Select a number. " << endl;
    while(choice < 1 || choice > yourDeckCount) cin >> choice;

    cardDrop[cardDropCount++] = yourDeck[choice - 1];
    for(int i = 0; i < yourDeckCount; i++) {
      if(yourDeck[i] == yourDeck[choice - 1]) {
        yourDeck[i] = yourDeck[i + 1];
      }
    }
    yourDeckCount--;
  }
}

void yourTurn() { //Not finished yet
  cout << endl << endl << "The card placed on the table is " << cardDrop[cardDropCount - 1] << ". ";

  flip = 0; //indicates that the PC will go afterwards.
  choice = -1;
  cout << "Here are your cards. Select a number. (Type 0 to draw)" << endl << endl;
  for(int i = 0; i < yourDeckCount; i++) cout << i + 1 << "). " << yourDeck[i] << endl;
  while(choice < 0 || choice > yourDeckCount) cin >> choice;
  if(choice == 0) {
    yourDeck[yourDeckCount++] = shuffle[count--]; //yourDeckCount is after the maximum index position.
    cout << endl << endl << "You drew. Here are your new sets. " << endl << endl;
    for(int i = 0; i < yourDeckCount; i++) cout << i + 1 << "). " << yourDeck[i] << endl;
  }
  else {
    cardDrop[cardDropCount++] = yourDeck[choice - 1];
    for(int i = 0; i < yourDeckCount; i++) {
      if(yourDeck[i] == yourDeck[choice - 1]) yourDeck[i] = yourDeck[i + 1];
      yourDeck[yourDeckCount - 1] = ""; //the last index position
    }
    yourDeckCount--;
  }
  cout << endl << endl << cardDrop[cardDropCount - 1] << " is on the table. Here are your new sets. \n";
  for(int i = 0; i < yourDeckCount; i++) cout << i + 1 << "). " << yourDeck[i] << endl;
}

int main() {
  srand(time(NULL));
  setUp();
  shuffleDeck();
  initialDraw();
  firstTurn();
  if(flip == 1) yourTurn();
 // else pcTurn();

  return 0;
}
