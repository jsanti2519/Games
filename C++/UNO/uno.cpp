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
int cardDropCount = 0, yourDeckCount = 7, pcDeckCount = 7;
bool turns;

void setUp();
void shuffleDeck();
void initialDraw(int&, int);
void removeElement(string[], int, int);


int main() {
  srand(time(NULL));
  setUp();
  shuffleDeck();
  
  int selection;
  int max;
  cout << "Press 0 to Draw 7: "; // fix this. I can type 3 and still proceeds.
  cin >> selection;
  initialDraw(max, selection);

  while(pcDeckCount > 0 || yourDeckCount > 0) {
    int baz = cardDrop[cardDropCount].find(" ");
    if(!turns) { //that means it's the computer's turn.
      for(int j = 0; j < pcDeckCount; j++) {
        int waldo = pcDeck[j].find(" "); 
        if(pcDeck[j] == "Wild +4" || pcDeck[j] == "Wild Card") {
          effects(turns); turns = true; pcDeckCount--; cardDropCount++;
          break;
        }
        //Line below in English: If color matches with color OR if number matches with number.
        else if((pcDeck[j].substr(0, waldo) == cardDrop[cardDropCount].substr(0, baz) || (pcDeck[j].substr(waldo, 2) == cardDrop[cardDropCount].substr(baz, 2)))) {
          if(pcDeck[j].substr(waldo, 2) == " +2") { //if color matches and it's a +2.
            for(int k = 0; k < 2; k++) yourDeck[yourDeckCount++] = shuffle[max--];
            pcDeckCount--; cardDropCount++; turns = true; //PC drops the +2 card. Your turn.
            break; 
          }
          else if(pcDeck[j].substr(waldo, 7) == " Reverse" || pcDeck[j].substr(waldo, 5) == " Skip") {
            pcDeckCount--; cardDropCount++; turns = false; //PC drops the reverse/skip card. PC goes again.
            break;
          }
          else {
            cardDrop[cardDropCount] = pcDeck[j];
            pcDeckCount--; cardDropCount++; turns = true;
            break;
          }
        } // matching colors/numbers else if bracket.
      } // for loop bracket.
    } // if(false) bracket.
    if(pcDeckCount == 1) cout << "PC: UNO!";
    
    if(turns) {
      cout << "Here are your sets. Choose one: \n";
      for(int i = 0; i < yourDeckCount; i++) {
        cout << i + 1 << "). " << yourDeck[i] << endl;
      }
      cin >> selection; selection--;
      int fred = yourDeck[selection].find(" "); 
      if(yourDeck[selection] == "Wild Card" || yourDeck[selection] == "Wild +4") {
        effects(!turns); yourDeckCount--; cardDropCount++; turns = false;
      }
      else if(yourDeck[selection].substr(0, fred) == cardDrop[cardDropCount].substr(0, baz) || yourDeck[selection].substr(fred, 2) == cardDrop[cardDropCount].substr(baz, 2) {
        if(yourDeck[selection].substr(fred, 2) == " +2") {
          for(int k = 0; k < 2; k++) pcDeck[pcDeckCount++] = shuffle[max--];
          yourDeckCount--; cardDropCount++; turns = false;
        }
        else if(yourDeck[selection].substr(fred, 2) == " Reverse" || yourDeck[selection].substr(fred, 2) == " Skip") {
          yourDeckCount--; cardDropCount++; turns = true; //You go again.
        }
        else {
          cardDrop[cardDropCount] = yourDeck[selection];
          yourDeckCount--; cardDropCount++; turns = false;
        } //inner else bracket
      } //outer else if bracket
    } // true / false bracket
    if(yourDeckCount == 1) {
      string uno;
      cout << "Type UNO";
      cin >> uno;
      if(uno != "UNO" || uno != "uno") yourDeck[++yourDeckCount] == shuffle[max--];
    }
        
  } //while loop bracket
  if(pcDeckCount == 0) cout << "PC: UNO OUT! You lose";
  else cout << "Uno out! You win!";
              
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
  for(int i = 0; i < 108; i++) index[i] = i;
  shuffleIndex[0] = index[rand() % 108];
  for(int j = 1; j < 108; j++) {
    bool repeats = true;
    while(repeats) {
      shuffleIndex[j] = index[rand() % 108];
      for(int k = 0; k < j; k++) {
        if(shuffleIndex[k] == shuffleIndex[j]) {
          repeats = true; break;
        }
        else repeats = false;
      }
    }
  }
    for(int l = 0; l < 108; l++) shuffle[l] = deck[shuffleIndex[l]];
}

void initialDraw(int &foo, int &bar) { //foo linked with max in main(), while bar is linked with selection variable.
  cout << "Your sets are: \n";
  for(int i = 0; i < yourDeckCount; i++) {
    foo = 107 - i;
    yourDeck[i] = shuffle[foo];
    cout << i + 1 << "). " << yourDeck[i] << "\n";
    removeElement(shuffle, 108, foo); //removes element in position where max is.
  }
  
  for(int j = 0; j < pcDeckCount; j++) { //Computer's initial draw.
    foo = 100 - j;
    pcDeck[j] = shuffle[foo];
    removeElement(shuffle, 108, foo);
  }

  cout << "\n\nSelect a number to draw: "; //your first turn.
  cin >> bar; bar--; cout << "\n\n";
  for(int k = 0; k < yourDeckCount; k++) {
    if(k >= bar) yourDeck[k] = yourDeck[k + 1];
  }
  cardDrop[cardDropCount++] = yourDeck[bar];
  turns = false;
}

void effects(int &qux) { //linked with max.
  int n = rand() % pcDeckCount;
  int randColors = rand() % 4;
  for(int i = 0; i < pcDeckCount; i++) {
    cardDrop[cardDropCount] = pcDeck[n]; // necessary??
    if(pcDeck[n] == "Wild +4") {
      cout << "I dropped a Wild + 4. I'm picking " << colors[randColors];
      cardDrop[cardDropCount] = colors[randColors]; cardDropCount++;
      for(int j = 0; j < yourDeckCount + 4; j++) { //double check this again.
        yourDeck[yourDeckCount + j + 1] = deck[qux];
        qux--;
      }
      break;
    }
    else if(pcDeck[n] == "Wild Card") {
      cout << "I dropped a Wild Card: I'm picking " << colors[randColors];
      cardDrop[cardDropCount] = colors[randColors]; cardDropCount++;
      break;
    }
  }

void removeElement(string a[], int cap, int pos) {
  for(int i = 0; i < cap; i++) {
    if(i >= pos) a[i] = " ";
  }
}
