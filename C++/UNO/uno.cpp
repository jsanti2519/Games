#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string deck[108], shuffle[108], yourDeck[100], pcDeck[100], cardDrop[108];
string colors[4] = {"Red", "Yellow", "Blue", "Green"};
string numbers[12] = {" 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", " +2", " Skip", " Reverse"};
string zero = " 0";
string WildCards[2] = {"Wild +4", "Wild Card"};
int index[108], shuffleIndex[108];

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
  
  for(int k = 0; k < 108; k++) cout << shuffle[k] << "\n";
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
  for(int i = 0; i < 108; i++) index[i] = i;
  shuffleIndex[0] = index[rand() % 108];
  for(int j = 1; j < 108; j++) {
    bool repeats = true;
    while(repeats) {
      shuffleIndex[j] = index[rand() % 108];
      for(int k = 0; k < i; k++) {
        if(shuffleIndex[k] == shuffleIndex[j]) {
          repeats = true; break;
        }
        else repeats = false;
      }
    }
  }
    for(int l = 0; l < 108; l++) shuffle[l] = deck[shuffleIndex[l]];
}

void initialDraw(int &foo) { //foo linked with max in main().
  cout << "Your sets are: \n";
  for(int i = 0; i < 7; i++) {
    foo = 107 - i;
    yourDeck[i] = shuffle[foo];
    cout << yourDeck[i] << "\n";
    removeElement(shuffle, 108, foo); //removes element in position where max is.
  }
  cout << "\n\n";
  
  for(int j = 0; j < 7; j++) {
    foo = 100 - j;
    pcDeck[j] = shuffle[foo];
    removeElement(shuffle, 108, foo);
  }
  //max becomes 94.
}

void removeElement(string a[], int cap, int pos) {
  for(int i = 0; i < cap; i++) {
    if(i >= pos) a[i] = " ";
  }
}
