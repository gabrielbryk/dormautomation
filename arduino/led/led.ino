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
int lampon = 0;
int count = 0;

CRGB color=CRGB::White;
CRGB room[NUM_ROOM];
CRGB under[NUM_UNDER];
CRGB shelf[NUM_SHELF];
CRGB desk[NUM_DESK];


void setup() {
  Serial.begin(115200);
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
  runCommand();
}

void loop() {
    //if(count<1000){
      if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.toLowerCase();
        parseCommand(command);
        runCommand();
      }
    //   count = count + 1;
    // }
    // else{
    //   runCommand();
    //   count = 100;
    // }

    
}

void parseCommand(String command){
  String param = command.substring(10);
  Serial.print(command+" "+param);
  if (command.startsWith("program")) {
    program = param.toInt();
  }
  else if (command.startsWith("brightness")) {
    brightness = param.toInt();
  }
  else if (command.startsWith("color")) {
    changeColor(param);
  }
  else if (command.startsWith("routine")){
    allOn();
    if(param.equals("bed")){
      brightness=50;
      changeColor("chill");
      roomon=0;
    }
    else if(param.equals("default")){
      brightness=200;
      changeColor("white"); 
    }
    else if(param.equals("movie")){
      brightness=50;
      changeColor("chill");
    }
    else if(param.equals("chill")){
      brightness=150;
      changeColor("chill");
    }
    else{
      brightness=200;
      changeColor("white"); 
    }
  }
  else if(command.startsWith("on")){
    if(param.equals("room")){
      roomon = 1;
    }
    else if(param.equals("bed")){
      bedon = 1;
    }
    else if(param.equals("desk")){
      deskon = 1;
    }
    else if(param.equals("shelf")){
      shelfon = 1;
    }
    else if(param.equals("power")){
      power = 1;
    }
    else if(param.equals("lamp")){
      lampon = 1;
    }
  }
  else if(command.startsWith("off")){
    if(param.equals("room")){
      roomon = 0;
    }
    else if(param.equals("bed")){
      bedon = 0;
    }
    else if(param.equals("desk")){
      deskon = 0;
    }
    else if(param.equals("shelf")){
      shelfon = 0;
    }
    else if(param.equals("power")){
      power = 0;
    }
    else if(param.equals("lamp")){
      lampon = 0;
    }
  }
}  

void runCommand(){
  FastLED.setBrightness(brightness);
  if(power==0){
    solid(CRGB::Black);
  }
  else{
    if (program == 1) {
    rainbowSpin();
    }
    else if (program == 2) {    
      solid(color);
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
    if(lampon==1){
      lamp();
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
  }
}

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
    for (int i = 0; i < NUM_ROOM; i++) {
      if (roomon) {
        room[i] = c;
      }
      else{
        room[i] = CRGB::Black;
      }
    }
    for (int i = 0; i < NUM_UNDER; i++) {
      if (bedon) {
        under[i] = c;
      }
      else{
        under[i] = CRGB::Black;
      }
    }
    for (int i = 0; i < NUM_SHELF; i++) {
      if (shelfon) {
        shelf[i] = c;
      }
      else{
        shelf[i] = CRGB::Black;
      }
    }
    for (int i = 30; i < NUM_DESK; i++) {
      if (deskon) {
        desk[i] = c;
      }
      else{
        desk[i] = CRGB::Black;
      }
    }
  FastLED.show();
}
//Helper Functions
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

void lamp() {
  for (int i = 30; i < 100; i++) {
    desk[i] = CHSV(0,0,255);
  }
  showStrip();
}

void allOn() {
  roomon=1;
  deskon=1;
  shelfon=1;
  bedon=1;
}

void showStrip() {
  //Turn off part
  //for (int i = 166; i < 174; i++) {
    //under[i] = CHSV(100,100,100);
  //}
  FastLED.show();
}

void changeColor(String c){
  if(c.equals("piss")){
    color= CRGB(255, 200, 0);
  }
  else if(c.equals("sex")){
    //sex pink
    color = CRGB(227, 43, 237);
  }
  else if(c.equals("white")){
    color=CRGB::White;
  }
  else if(c.equals("chill")){
    //purple chill
    color = CRGB(100, 70, 255);
  }
  else if(c.equals("orange")){
    //orangey red
    color = CRGB(245, 43, 7);
  }
  else if(c.equals("teal")){
    //orangey red
    color = CRGB(0, 255, 128);
  }
  else{
    color=CRGB::White;  
  }
}