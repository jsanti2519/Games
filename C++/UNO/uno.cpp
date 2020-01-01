#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string deck[108], shuffle[108];
string colors[4] = {"Red", "Yellow", "Blue", "Green"};
string numbers[12] = {" 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", " +2", " Skip", " Reverse"};
string zero = " 0";
string WildCards[2] = {"Wild +4", "Wild Card"};

void setUp();
void shuffleDeck();


int main() {
  srand(time(NULL));
  setUp();
  shuffleDeck();

  

  for(int k = 0; k < 108; k++) cout << shuffle[k] << "\n";

  return 0;
}

void setUp() {
  int colorCount = 0, numCount = 0, twice = 1;
  for(int i = 0; i < 96; i++) {
    deck[i] = colors[colorCount] + numbers[numCount++];
    if(numCount == 12 && twice == 2) {
      colorCount++; numCount = 0; twice = 1;
    }
    else if(numCount == 12) {
      numCount = 0; twice++;
    }
  }
  colorCount = 0; //resetting the count to zero for colors[].
  for(int j = 96; j < 100; j++) {
    deck[j] = colors[colorCount++] + zero;
  }
  for(int k = 100; k < 108; k++) {
    if(k < 104) deck[k] = WildCards[0];
    else deck[k] = WildCards[1];
  }
}

void shuffleDeck() {
  shuffle[0] = deck[rand() % 108];
  for(int i = 1; i < 108; i++) {
    bool repeats = true;
    while(repeats) {
      shuffle[i] = deck[rand() % 108];
      for(int k = 0; k < i; k++) {
        if(shuffle[k] == shuffle[i]) break;
        repeats = false;
      }
    }
  }
}

//set up deck (A)
//shuffle cards (A)
//distribute cards to each person. (I)
// 
