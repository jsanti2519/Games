class global {
  static String deck[] = new String[108], shuffle[] = new String[108];
  static String colors[] = {"Red", "Yellow", "Blue", "Green"};
  static String numbers[] = {" 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", " +2", " Skip", " Reverse"};
  static String zero = " 0";
  static String WildCards[] = {"Wild +4", "Wild Card"};
}

class Main {

  public static void setUp() {
    int colorCount = 0, numCount = 0, twice = 1;
    for(int i = 0; i < 96; i++) {
      global.deck[i] = global.colors[colorCount] + global.numbers[numCount++];
      if(numCount == 12 && twice == 2) {
        colorCount++; numCount++; twice = 1;
      }
      else if(numCount == 12) {
        numCount = 0; twice++;
      }
    }
    colorCount = 0; //resetting the count to zero for colors[].
    for(int j = 96; j < 100; j++) {
      global.deck[j] = global.colors[colorCount++] + global.zero;
    }
    for(int k = 100; k < 108; k++) {
      if(k < 104) global.deck[k] = global.WildCards[0];
      else global.deck[k] = global.WildCards[1];
    }
  }



  public static void main(String args[]) {
    setUp();
    for(int i = 0; i < 108; i++) System.out.println(global.deck[i]);
  }
}
