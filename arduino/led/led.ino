#include <FastLED.h>


#define LED_PIN1     7 //Room
#define LED_PIN2     8 //Under Bed
#define LED_PIN3     9 //Shelf
#define LED_PIN4     10 //Desk

#define NUM_ROOM 592
#define NUM_UNDER 350
#define NUM_SHELF 100
#define NUM_DESK 180

int program = 2;
int brightness = 180;
int power = 1;

int deskon = 1;
int roomon = 1;
int shelfon = 1;
int bedon = 1;

int color = 1;
//0 white
//1 purple vibe
//2 sex pink
//3 organy red
//4 greenish teal
//5 yellowish
CRGB room[NUM_ROOM];
CRGB under[NUM_UNDER];
CRGB shelf[NUM_SHELF];
CRGB desk[NUM_DESK];


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN1, GRB>(room, NUM_ROOM);
  FastLED.addLeds<WS2811, LED_PIN2, GRB>(under, NUM_UNDER);
  FastLED.addLeds<WS2811, LED_PIN3, GRB>(shelf, NUM_SHELF);
  FastLED.addLeds<WS2811, LED_PIN4, GRB>(desk, NUM_DESK);
  for (int i = 0; i < NUM_ROOM; i++) {
    room[i] = CRGB::Black;
  }
  for (int i = 0; i < NUM_UNDER; i++) {
    under[i] = CRGB::Black;
  }
  for (int i = 0; i < NUM_SHELF; i++) {
    desk[i] = CRGB::Black;
  }
  for (int i = 0; i < NUM_DESK; i++) {
    desk[i] = CRGB::Black;
  }
}
void loop() {
  if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n');
      Serial.print("You sent me: ");
      Serial.println(data);
  if (program == 1) {
    rainbowSpin();
  }
  else if (program == 2) {
    FastLED.setBrightness(brightness);
    CRGB c;
    if (color == 1) {
      c = CRGB(100, 70, 255);
    }
    else if (color == 2) {
      c = CRGB(227, 43, 237);
    }
    else if (color == 3) {
      c = CRGB(245, 43, 7);
    }
    else if (color == 4) {
      c = CRGB(0, 255, 128);
    }
    else if (color == 5) {
      c = CRGB(255, 200, 0);
    }
    else if (color == 6) {
      c = CRGB(255, 219, 89);
    }
    else {
      //c = CRGB(255, 255, 255);
      c = CRGB::White;
    }
    solid(c);
  }
  else if (program == 3) {
    flash();
  }
  else if (program == 4) {
    rainbowSolid();
  }
  else {
    delay(1000);
}
  }
  //checkSerial();

}

void checkSerial() {
  if (Serial.available() > 10) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
    if (command.startsWith("program")) {
      program = command.substring(7).toInt();
      Serial.print(program);
    }
    else if (command.equals("brightness")) {
      brightness = command.substring(8).toInt();
    }
    else if (command.equals("on")) {
      power = 1;
    }
    else if (command.equals("off")) {
      power = 0;
    }
  }
}
//Programs
void rainbowSpin() {
  for (int hue = 0; hue < 255; hue++) {
    room[0] = CHSV(hue , 255 , brightness);
    under[0] = CHSV(hue , 255 , brightness);
    shelf[0] = CHSV(hue , 255 , brightness);
    desk[0] = CHSV(hue , 255 , brightness);

    shift(room, NUM_ROOM);
    shift(under, NUM_UNDER);
    shift(under, NUM_UNDER);
    shift(shelf, NUM_SHELF);
    shift(desk, NUM_DESK);

    delay(10);
    showStrip();
    checkSerial();
  }
}

//Programs
void rainbowSolid() {
  for (int hue = 0; hue < 255; hue += 1) {


    solid(CHSV(hue , 255 , 255));

    delay(1);
    showStrip();
  }
}
void flash() {
  int f = 500;
  solid(CRGB::Red);
  delay(f);
  solid(CRGB::Blue);
  delay(f);
  solid(CRGB::Green);
  delay(f);

}
void solid(CRGB c) {
  if (roomon) {
    for (int i = 0; i < NUM_ROOM; i++) {
      room[i] = c;
      // room[i] = CRGB::Black;
    }
  }
  if (bedon) {
    for (int i = 0; i < NUM_UNDER; i++) {
      under[i] = c;
      //under[i] = CRGB::Black;
    }
  }
  if (shelfon) {
    for (int i = 0; i < NUM_SHELF; i++) {
      shelf[i] = c;
      //desk[i] = CRGB::Black;
    }
  }
  if (deskon) {
    for (int i = 30; i < NUM_DESK; i++) {
      desk[i] = c;
      //desk[i] = CRGB::Black;
    }
  }
  FastLED.show();
}
//helper functions
void shift(CRGB arr[], int num) {
  CRGB last = arr[num];
  for (int i = num - 1; i > 0; i--) {
    arr[i] = arr[i - 1];
  }
  //arr[0] = last;
}

void shift(CRGB arr[], int num, int skipstart, int skipend) {
  CRGB tmp = arr[0];
  for (int i = num; i > 0; i--) {
    if (i == skipend) {
      arr[i] = arr[skipstart];
      i = skipstart;
    }
    arr[i] = arr[i - 1];
  }


}
void showStrip() {
  //Turn off part
  for (int i = 166; i < 174; i++) {
    //under[i] = CHSV(100,100,100);
  }
  FastLED.show();
}
