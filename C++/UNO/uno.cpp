#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string deck[108], shuffle[108], yourDeck[100], pcDeck[100], cardDrop[108];
string colors[4] = {"Red", "Yellow", "Blue", "Green"};
string numbers[12] = {" 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", " +2", " Skip", " Reverse"};
string zero = " 0";
string WildCards[2] = {"Wild +4", "Wild Card"};

void setUp();
void shuffleDeck();
void initialDraw(int&);
void removeElement(string[], int, int);


int main() {
  srand(time(NULL));
  setUp();
  shuffleDeck();
  
  int selection;
  int max;
  cout << "Press 0 to Draw 7: ";
  cin >> selection;
  initialDraw(max);
  
  //for(int k = 0; k < 108; k++) cout << shuffle[k] << "\n"; receiving what I did not expect...
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

void initialDraw(int &max) {
  cout << "Your sets are: \n";
  for(int i = 0; i < 7; i++) {
    max = 107 - i;
    yourDeck[i] = shuffle[max];
    cout << yourDeck[i] << "\n";
    removeElement(shuffle, 108, max); //removes element in position where max is.
  }
  cout << "\n\n";
  
  //max should be 101 now.
  
  for(int j = 0; j < 7; j++) {
    max = 101 - j;
    pcDeck[j] = shuffle[max];
    removeElement(shuffle, 108, max);
  }
  //max becomes 95.
}

void removeElement(string a[], int cap, int pos) {
  for(int i = 0; i < cap; i++) {
    if(i >= pos) a[i] = a[i + 1];
  }
}
