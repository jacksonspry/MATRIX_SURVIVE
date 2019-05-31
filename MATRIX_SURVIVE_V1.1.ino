

/*
   Author: Jackson Spry

  Warning*** bugs inclue but are not limited to:
           >can spwan impossible walls (two too close together going the same direction)
            but I thought that the shared cooldown would take care of it. not sure why it is not working?
           >frames are super fast when there are few obsticales on the screen. (a variable delay could solve this, but I kinda like it)
           >score display is still kind of messed up

*/
#include <LedControl.h>
#include "binary.h"
LedControl lc = LedControl(7, 5, 6, 4);
int x = 7, y = 2, add = 1, x1 = 0, f = 0;
byte hf[8] = {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100};
byte tit3[7] = {B01110100, B10000100, B10000100, B01100100, B00010100, B00010100, B11100011};
byte tit2[7] = {B10111001, B10100101, B10100101, B10111001, B10101000, B10100100, B00100100};
byte tit1[7] = {B00101110, B00100100, B00100100, B00100100, B11000100, B11000100, B11001110};
byte tit0[7] = {B10010111, B10010100, B10010100, B10010111, B01100100, B01100100, B01100111};
int rand1, needrand1;
int spawn1 = 0, mgo1 = 1000, show1 = 0, sc1 = 0, sc2 = 0, sc3 = 0, m = 0, f1 = -1, f2 = -1, f3 = -1, f4 = -1, cooldown1 = 0, cooloff1 = 0, on1;
int spawn2 = 0, mgo2 = 1000, show2 = 0, sc11 = 0, sc21 = 0, sc31 = 0, n = 0, f11 = -1, f21 = -1, f31 = -1, f41 = -1, cooloff2 = 0, on2, cooldown3 = 0;
int spawn3 = 0, mgo3 = 1000, show3 = 0, sc12 = 0, sc22 = 0, sc32 = 0, v = 0, f12 = 8, f22 = 8, f32 = 8, f42 = 8, cooldown2 = 0, cooloff3 = 0, on3;
int spawn4 = 0, mgo4 = 1000, show4 = 0, sc13 = 0, sc23 = 0, sc33 = 0, b = 0, f13 = 8, f23 = 8, f33 = 8, f43 = 8, cooloff4 = 0, on4 = 0, cooldown4 = 0;
int gameover = 0;
String score = String(0);
int score3 = 0, score4 = 0, score2 = 0, display1 = 0;
const int ledR = 3, ledG = 16;

//Pin connected to ST_CP of 74HC595 //bit shift module used to connect the 4-digit 7-segment display
int latchPin = 13;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;
int d2 = 8, d3 = 9, d4 = 10;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(4));
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  lc.shutdown(2, false);
  lc.shutdown(3, false);
  lc.setIntensity(0, 6);
  lc.setIntensity(1, 6);
  lc.setIntensity(2, 6);
  lc.setIntensity(3, 6);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  lc.setRow(3, 0, tit3[0]);
  lc.setRow(3, 1, tit3[1]);
  lc.setRow(3, 2, tit3[2]);
  lc.setRow(3, 3, tit3[3]);
  lc.setRow(3, 4, tit3[4]);
  lc.setRow(3, 5, tit3[5]);
  lc.setRow(3, 6, tit3[6]);
  lc.setRow(2, 0, tit2[0]);
  lc.setRow(2, 1, tit2[1]);
  lc.setRow(2, 2, tit2[2]);
  lc.setRow(2, 3, tit2[3]);
  lc.setRow(2, 4, tit2[4]);
  lc.setRow(2, 5, tit2[5]);
  lc.setRow(2, 6, tit2[6]);
  lc.setRow(1, 0, tit1[0]);
  lc.setRow(1, 1, tit1[1]);
  lc.setRow(1, 2, tit1[2]);
  lc.setRow(1, 3, tit1[3]);
  lc.setRow(1, 4, tit1[4]);
  lc.setRow(1, 5, tit1[5]);
  lc.setRow(1, 6, tit1[6]);
  lc.setRow(0, 0, tit0[0]);
  lc.setRow(0, 1, tit0[1]);
  lc.setRow(0, 2, tit0[2]);
  lc.setRow(0, 3, tit0[3]);
  lc.setRow(0, 4, tit0[4]);
  lc.setRow(0, 5, tit0[5]);
  lc.setRow(0, 6, tit0[6]);
  delay(1000);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  lc.setIntensity(0, 15);
  lc.setIntensity(1, 15);
  lc.setIntensity(2, 15);
  lc.setIntensity(3, 15);
}
void eraseplayer() {       //Its so much because I just clear a 1 pixel area around the sprite every time to clean it up
  if (x == 0) {           //could definitley be improved by just removing whats left behind specifically each frame
    lc.setLed(add - 1, y - 1, 0, 0);
    lc.setLed(add - 1, y, 0, 0);
    lc.setLed(add - 1, y + 1, 0, 0);
    lc.setLed(add - 1, y + 2, 0, 0);
    lc.setLed(add - 1, y + 3, 0, 0);
  }
  if (x == 5) {
    lc.setLed(add + 1, y - 1, 7, 0);
    lc.setLed(add + 1, y, 7, 0);
    lc.setLed(add + 1, y + 1, 7, 0);
    lc.setLed(add + 1, y + 2, 7, 0);
    lc.setLed(add + 1, y + 3, 7, 0);
  }
  if (x < 6) {
    lc.setLed(add, y + 1, x1 - 1, 0);
    lc.setLed(add, y - 1 , x1 + 1, 0);
    lc.setLed(add, y, x1 + 1, 0);
    lc.setLed(add, y + 1, x1 + 1, 0);
    lc.setLed(add, y + 2, x1 + 1, 0);
    lc.setLed(add, y + 3, x1 + 1, 0);
    lc.setLed(add, y + 3, x1, 0);
    lc.setLed(add, y + 3, x1 - 1, 0);
    lc.setLed(add, y + 3, x1 - 2, 0);
    lc.setLed(add, y + 3, x1 - 3, 0);
    lc.setLed(add, y + 2, x1 - 3, 0);
    lc.setLed(add, y + 1, x1 - 3, 0);
    lc.setLed(add, y, x1 - 3, 0);
    lc.setLed(add, y - 1, x1 - 3, 0);
    lc.setLed(add, y - 1, x1 - 2, 0);
    lc.setLed(add, y - 1, x1 - 1, 0);
    lc.setLed(add, y - 1, x1, 0);
  }
  if (x == 6) {
    lc.setLed(add, y, 2, 0);
    lc.setLed(add, y + 1, 2, 0);
    lc.setLed(add, y + 2, 2, 0);
    lc.setLed(add, y + 3, 2, 0);
    lc.setLed(add, y - 1, 2, 0);
    lc.setLed(add, y + 1, 0, 0);
    lc.setLed(add + 1, y - 1, 6, 0);
    lc.setLed(add + 1, y, 6, 0);
    lc.setLed(add + 1, y + 1, 6, 0);
    lc.setLed(add + 1, y + 2, 6, 0);
    lc.setLed(add + 1, y + 3, 6, 0);
    lc.setLed(add + 1, y - 1, 7, 0);
    lc.setLed(add + 1, y + 3, 7, 0);
    lc.setLed(add, y - 1, 0, 0);
    lc.setLed(add, y - 1, 1, 0);
    lc.setLed(add, y - 1, 2, 0);
    lc.setLed(add, y + 3, 0, 0);
    lc.setLed(add, y + 3, 1, 0);
    lc.setLed(add, y + 3, 2, 0);
  }
  if (x == 7) {
    lc.setLed(add, y, 1, 0);
    lc.setLed(add, y + 1, 1, 0);
    lc.setLed(add, y + 2, 1, 0);
    lc.setLed(add, y + 3, 1, 0);
    lc.setLed(add, y - 1, 1, 0);
    lc.setLed(add + 1, y - 1, 5, 0);
    lc.setLed(add + 1, y, 5, 0);
    lc.setLed(add + 1, y + 1, 5, 0);
    lc.setLed(add + 1, y + 2, 5, 0);
    lc.setLed(add + 1, y + 3, 5, 0);
    lc.setLed(add + 1, y - 1, 6, 0);
    lc.setLed(add + 1, y + 3, 6, 0);
    lc.setLed(add + 1, y + 3, 7, 0);
    lc.setLed(add + 1, y - 1, 7, 0);
    lc.setLed(add, y - 1, 0, 0);
    lc.setLed(add, y + 3, 0, 0);
    lc.setLed(add + 1, y + 1, 7, 0);
  }
}
void drawplayer() {
  if (x < 6) {
    lc.setLed(add, y, x1, 1);
    lc.setLed(add, y + 1, x1, 1);
    lc.setLed(add, y + 2, x1, 1);
    lc.setLed(add, y, x1 - 1, 1);
    lc.setLed(add, y, x1 - 2, 1);
    lc.setLed(add, y + 1, x1 - 2, 1);
    lc.setLed(add, y + 2, x1 - 1, 1);
    lc.setLed(add, y + 2, x1 - 2, 1);
  }

  if (x == 6) {
    lc.setLed(add, y, x1, 1);
    lc.setLed(add, y + 1, x1, 1);
    lc.setLed(add, y + 2, x1, 1);
    lc.setLed(add, y, x1 - 1, 1);
    lc.setLed(add + 1, y, 7, 1);
    lc.setLed(add + 1, y + 1, 7, 1);
    lc.setLed(add, y + 2, x1 - 1, 1);
    lc.setLed(add + 1, y + 2, 7, 1);
    lc.setLed(add, y, x1, 1);
  }
  if (x == 7) {
    lc.setLed(add, y, x1, 1);
    lc.setLed(add, y + 1, x1, 1);
    lc.setLed(add, y + 2, x1, 1);
    lc.setLed(add + 1, y, 7, 1);
    lc.setLed(add + 1, y, 6, 1);
    lc.setLed(add + 1, y + 1, 6, 1);
    lc.setLed(add + 1, y + 2, 7, 1);
    lc.setLed(add + 1, y + 2, 6, 1);
  }
}

void loop() {
  if (f == 50) {
    digitalWrite(ledG, HIGH);
  }
  delay (1);
  f = f + 1;
  score = f;
  Serial.print("\n");
  Serial.print(f);
  Serial.print("__");
  Serial.print(cooldown1);
  Serial.print(":");
  Serial.print(cooldown2);

  //COORDINATES FROM JOYSTICK
  if (analogRead(0) < 470) {
    if (add == 3) {
      if (x < 5) {
        x = x + 1;
      }
      else {}
    }
    else {
      x = x + 1;
    }
  }
  if (analogRead(0) > 550) {
    if (add == 0) {
      if (x > 0) {
        x = x - 1;
      }
      else {}
    }
    else {
      x = x - 1;
    }
  }
  if (analogRead(1) > 550 && y < 5) {
    y = y + 1;

  }
  if (analogRead(1) < 470 && y >= 1) {
    y = y - 1;
  }
  //WARPING PLAYER TO NEW SCREEN (causes overlap)
  if (x == 8) {
    add = add + 1;
    x = 0;
  }
  if (x == -1) {
    add = add - 1;
    x = 7;
  }
  x1 = -(x - 7);

  eraseplayer();
  drawplayer();


  //WALL SPAWN //super huge could be better
  if (f > 3) {
    needrand1 = 1;
  }
  if (needrand1 == 1) {
    rand1 = random(1, 20);
  }
  if (rand1 == 1 && cooldown1 == 0) {
    rand1 = 0;
    spawn1 = 1;
    cooldown1 = 1;
    cooldown2 = 1;
  }
  if (spawn1 == 1) {
    mgo1 = 8;
    spawn1 = 0;
    show1 = 1;
  }
  if (show1 == 1) {
    lc.setLed(3, 0, 0, 1);
    lc.setLed(3, 1, 0, 1);
    lc.setLed(3, 2, 0, 1);
    lc.setLed(3, 3, 0, 1);
    m = m + 1;
    if (y < 4 && x1 == 2 && add == 3) {
      gameover = 1;
    }
  }
  if (m > mgo1) {
   
    cooloff1 = 1;
    show1 = 0;
    on1 = 1;
    m = 0;
    mgo1 = 0;
  }
  if (on1 == 1) {
    f1 = f1 + 1;
    lc.setLed(3, 0, f1 - 2, 0);
    lc.setLed(3, 1, f1 - 2, 0);
    lc.setLed(3, 2, f1 - 2 , 0);
    lc.setLed(3, 3, f1 - 2, 0);
    lc.setLed(3, 0, f1 - 1, 1);
    lc.setLed(3, 1, f1 - 1, 1);
    lc.setLed(3, 2, f1 - 1, 1);
    lc.setLed(3, 3, f1 - 1, 1);
    lc.setLed(3, 0, f1, 1);
    lc.setLed(3, 1, f1, 1);
    lc.setLed(3, 2, f1, 1);
    lc.setLed(3, 3, f1, 1);
    if (y < 4 && ((x1 - 3) < f1) && (x1 + 2 > f1) && add == 3) {
      gameover = 1;
    }
    if (y < 4 && ((x1 + 5) < f1) && (x1 + 10 > f1) && add == 2) {
      gameover = 1;
    }
  }

  if (cooloff1 == 1) {
    cooldown1 = 0;
    cooloff1 = 0;
    cooldown2 = 0;
  }
  if (f1 > 7) {
    on1 = 0;
    f1 = -1;
    sc1 = 1;
  }
  if (sc1 == 1) {
    f2 = f2 + 1;
    lc.setLed(3, 0, f2 + 6, 0);
    lc.setLed(3, 1, f2 + 6, 0);
    lc.setLed(3, 2, f2 + 6 , 0);
    lc.setLed(3, 3, f2 + 6, 0);
    lc.setLed(2, 0, f2 - 2, 0);
    lc.setLed(2, 1, f2 - 2, 0);
    lc.setLed(2, 2, f2 - 2 , 0);
    lc.setLed(2, 3, f2 - 2, 0);
    lc.setLed(2, 0, f2 - 1, 1);
    lc.setLed(2, 1, f2 - 1, 1);
    lc.setLed(2, 2, f2 - 1, 1);
    lc.setLed(2, 3, f2 - 1, 1);
    lc.setLed(2, 0, f2, 1);
    lc.setLed(2, 1, f2, 1);
    lc.setLed(2, 2, f2, 1);
    lc.setLed(2, 3, f2, 1);
    if (y < 4 && ((x1 - 3) < f2) && (x1 + 2 > f2) && add == 2) {
      gameover = 1;
    }
    if (y < 4 && ((x1 + 5) < f2) && (x1 + 10 > f2) && add == 1) {
      gameover = 1;
    }
  }
  if (f2 > 7) {
    f2 = -1;
    sc1 = 0;
    sc2 = 1;
  }
  if (sc2 == 1) {
    f3 = f3 + 1;
    lc.setLed(2, 0, f3 + 6, 0);
    lc.setLed(2, 1, f3 + 6, 0);
    lc.setLed(2, 2, f3 + 6 , 0);
    lc.setLed(2, 3, f3 + 6, 0);
    lc.setLed(1, 0, f3 - 2, 0);
    lc.setLed(1, 1, f3 - 2, 0);
    lc.setLed(1, 2, f3 - 2 , 0);
    lc.setLed(1, 3, f3 - 2, 0);
    lc.setLed(1, 0, f3 - 1, 1);
    lc.setLed(1, 1, f3 - 1, 1);
    lc.setLed(1, 2, f3 - 1, 1);
    lc.setLed(1, 3, f3 - 1, 1);
    lc.setLed(1, 0, f3, 1);
    lc.setLed(1, 1, f3, 1);
    lc.setLed(1, 2, f3, 1);
    lc.setLed(1, 3, f3, 1);
    if (y < 4 && ((x1 - 3) < f3) && (x1 + 2 > f3) && add == 1) {
      gameover = 1;
    }
    if (y < 4 && ((x1 + 5) < f3) && (x1 + 10 > f3) && add == 0) {
      gameover = 1;
    }
  }
  if (f3 > 7) {
    f3 = -1;
    sc2 = 0;
    sc3 = 1;
  }
  if (sc3 == 1) {
    f4 = f4 + 1;
    lc.setLed(1, 0, f4 + 6, 0);
    lc.setLed(1, 1, f4 + 6, 0);
    lc.setLed(1, 2, f4 + 6 , 0);
    lc.setLed(1, 3, f4 + 6, 0);
    lc.setLed(0, 0, f4 - 2, 0);
    lc.setLed(0, 1, f4 - 2, 0);
    lc.setLed(0, 2, f4 - 2 , 0);
    lc.setLed(0, 3, f4 - 2, 0);
    lc.setLed(0, 0, f4 - 1, 1);
    lc.setLed(0, 1, f4 - 1, 1);
    lc.setLed(0, 2, f4 - 1, 1);
    lc.setLed(0, 3, f4 - 1, 1);
    lc.setLed(0, 0, f4, 1);
    lc.setLed(0, 1, f4, 1);
    lc.setLed(0, 2, f4, 1);
    lc.setLed(0, 3, f4, 1);
    if (y < 4 && ((x1 - 3) < f4) && (x1 + 2 > f4) && add == 0) {
      gameover = 1;
    }
  }
  if (f4 > 8) {
    f4 = -1;
    sc3 = 0;
  }

  //SECOND WALL                          //SECOND WALL
  if (rand1 == 2 && cooldown2 == 0) {
    spawn2 = 1;
    cooldown1 = 1;
    cooldown2 = 1;
    rand1 = 0;
  }
  if (spawn2 == 1) {
    mgo2 = 6;
    spawn2 = 0;
    show2 = 1;
  }
  if (show2 == 1) {
    lc.setLed(3, 4, 0, 1);
    lc.setLed(3, 5, 0, 1);
    lc.setLed(3, 6, 0, 1);
    lc.setLed(3, 7, 0, 1);
    if (y > 1 && x1 == 2 && add == 3) {
      gameover = 1;
    }
    n = n + 1;
  }
  if (n > 7){
    
  }
  if (n > mgo2) {
    cooloff2 = 1;
    show2 = 0;
    on2 = 1;
    n = 0;
    mgo2 = 0;
  }
  if (on2 == 1) {
    f11 = f11 + 1;
    lc.setLed(3, 4, f11 - 2, 0);
    lc.setLed(3, 5, f11 - 2, 0);
    lc.setLed(3, 6, f11 - 2 , 0);
    lc.setLed(3, 7, f11 - 2, 0);
    lc.setLed(3, 4, f11 - 1, 1);
    lc.setLed(3, 5, f11 - 1, 1);
    lc.setLed(3, 6, f11 - 1, 1);
    lc.setLed(3, 7, f11 - 1, 1);
    lc.setLed(3, 4, f11, 1);
    lc.setLed(3, 5, f11, 1);
    lc.setLed(3, 6, f11, 1);
    lc.setLed(3, 7, f11, 1);
    if (y > 1 && ((x1 - 3) < f11) && (x1 + 2 > f11) && add == 3) {
      gameover = 1;
    }
    if (y > 1 && ((x1 + 5) < f11) && (x1 + 10 > f11) && add == 2) {
      gameover = 1;
    }
  }

  if (cooloff2 == 1) {
    cooldown1 = 0;
    cooldown2 = 0;
    cooloff2 = 0;
  }

  if (f11 > 7) {
    on2 = 0;
    f11 = -1;
    sc11 = 1;
  }

  if (sc11 == 1) {
    f21 = f21 + 1;
    lc.setLed(3, 4, f21 + 6, 0);
    lc.setLed(3, 5, f21 + 6, 0);
    lc.setLed(3, 6, f21 + 6 , 0);
    lc.setLed(3, 7, f21 + 6, 0);
    lc.setLed(2, 4, f21 - 2, 0);
    lc.setLed(2, 5, f21 - 2, 0);
    lc.setLed(2, 6, f21 - 2 , 0);
    lc.setLed(2, 7, f21 - 2, 0);
    lc.setLed(2, 4, f21 - 1, 1);
    lc.setLed(2, 5, f21 - 1, 1);
    lc.setLed(2, 6, f21 - 1, 1);
    lc.setLed(2, 7, f21 - 1, 1);
    lc.setLed(2, 4, f21, 1);
    lc.setLed(2, 5, f21, 1);
    lc.setLed(2, 6, f21, 1);
    lc.setLed(2, 7, f21, 1);
    if (y > 1 && ((x1 - 3) < f21) && (x1 + 2 > f21) && add == 2) {
      gameover = 1;
    }
    if (y > 1 && ((x1 + 5) < f21) && (x1 + 10 > f21) && add == 1) {
      gameover = 1;
    }
  }
  if (f21 > 7) {
    f21 = -1;
    sc11 = 0;
    sc21 = 1;
  }
  if (sc21 == 1) {
    f31 = f31 + 1;
    lc.setLed(2, 4, f31 + 6, 0);
    lc.setLed(2, 5, f31 + 6, 0);
    lc.setLed(2, 6, f31 + 6 , 0);
    lc.setLed(2, 7, f31 + 6, 0);
    lc.setLed(1, 4, f31 - 2, 0);
    lc.setLed(1, 5, f31 - 2, 0);
    lc.setLed(1, 6, f31 - 2 , 0);
    lc.setLed(1, 7, f31 - 2, 0);
    lc.setLed(1, 4, f31 - 1, 1);
    lc.setLed(1, 5, f31 - 1, 1);
    lc.setLed(1, 6, f31 - 1, 1);
    lc.setLed(1, 7, f31 - 1, 1);
    lc.setLed(1, 4, f31, 1);
    lc.setLed(1, 5, f31, 1);
    lc.setLed(1, 6, f31, 1);
    lc.setLed(1, 7, f31, 1);
    if (y > 1 && ((x1 - 3) < f31) && (x1 + 2 > f31) && add == 1) {
      gameover = 1;
    }
    if (y > 1 && ((x1 + 5) < f31) && (x1 + 10 > f31) && add == 0) {
      gameover = 1;
    }
  }
  if (f31 > 7) {
    f31 = -1;
    sc21 = 0;
    sc31 = 1;
  }
  if (sc31 == 1) {
    f41 = f41 + 1;
    lc.setLed(1, 4, f41 + 6, 0);
    lc.setLed(1, 5, f41 + 6, 0);
    lc.setLed(1, 6, f41 + 6 , 0);
    lc.setLed(1, 7, f41 + 6, 0);
    lc.setLed(0, 4, f41 - 2, 0);
    lc.setLed(0, 5, f41 - 2, 0);
    lc.setLed(0, 6, f41 - 2 , 0);
    lc.setLed(0, 7, f41 - 2, 0);
    lc.setLed(0, 4, f41 - 1, 1);
    lc.setLed(0, 5, f41 - 1, 1);
    lc.setLed(0, 6, f41 - 1, 1);
    lc.setLed(0, 7, f41 - 1, 1);
    lc.setLed(0, 4, f41, 1);
    lc.setLed(0, 5, f41, 1);
    lc.setLed(0, 6, f41, 1);
    lc.setLed(0, 7, f41, 1);
    if (y > 1 && ((x1 - 3) < f41) && (x1 + 2 > f41) && add == 0) {
      gameover = 1;
    }
  }
  if (f41 > 8) {
    f41 = -1;
    sc31 = 0;
  }

  if (rand1 == 3 && cooldown3 == 0) {     //THIRD WALL (top right)
    rand1 = 0;
    spawn3 = 1;
    cooldown3 = 1;
    cooldown4 = 1;
  }
  if (spawn3 == 1) {
    mgo3 = 6;
    spawn3 = 0;
    show3 = 1;
  }
  if (show3 == 1) {
    lc.setLed(0, 0, 7, 1);
    lc.setLed(0, 1, 7, 1);
    lc.setLed(0, 2, 7, 1);
    lc.setLed(0, 3, 7, 1);
    v = v + 1;
  }
  if (v > mgo3) {
    cooloff3 = 1;
    show3 = 0;
    on3 = 1;
    v = 0;
    mgo3 = 0;
  }

  if (on3 == 1) {
    f12 = f12 - 1;
    lc.setLed(0, 0, f12 + 2, 0);
    lc.setLed(0, 1, f12 + 2, 0);
    lc.setLed(0, 2, f12 + 2 , 0);
    lc.setLed(0, 3, f12 + 2, 0);
    lc.setLed(0, 0, f12 + 1, 1);
    lc.setLed(0, 1, f12 + 1, 1);
    lc.setLed(0, 2, f12 + 1, 1);
    lc.setLed(0, 3, f12 + 1, 1);
    lc.setLed(0, 0, f12, 1);
    lc.setLed(0, 1, f12, 1);
    lc.setLed(0, 2, f12, 1);
    lc.setLed(0, 3, f12, 1);
    if (y < 4 && ((x1 - 4) < f12) && (x1 + 1 > f12) && add == 0) {
      gameover = 1;
    }

  }
  if (cooloff3 == 1) {
    cooldown4 = 0;
    cooldown3 = 0;
    cooloff3 = 0;
  }
  if (f12 < 0) {
    on3 = 0;
    f12 = 8;
    sc12 = 1;
  }
  if (sc12 == 1) {
    f22 = f22 - 1;
    lc.setLed(0, 0, f22 - 6, 0);
    lc.setLed(0, 1, f22 - 6, 0);
    lc.setLed(0, 2, f22 - 6 , 0);
    lc.setLed(0, 3, f22 - 6, 0);
    lc.setLed(1, 0, f22 + 2, 0);
    lc.setLed(1, 1, f22 + 2, 0);
    lc.setLed(1, 2, f22 + 2 , 0);
    lc.setLed(1, 3, f22 + 2, 0);
    lc.setLed(1, 0, f22 + 1, 1);
    lc.setLed(1, 1, f22 + 1, 1);
    lc.setLed(1, 2, f22 + 1, 1);
    lc.setLed(1, 3, f22 + 1, 1);
    lc.setLed(1, 0, f22, 1);
    lc.setLed(1, 1, f22, 1);
    lc.setLed(1, 2, f22, 1);
    lc.setLed(1, 3, f22, 1);
    if (y < 4 && (x1 + 4 < f22) && add == 0) {
      gameover = 1;
    }
    if (y < 4 && ((x1 - 4) < f22) && (x1 + 1 > f22) && add == 1) {
      gameover = 1;
    }

  }
  if (f22 < 0) {
    f22 = 8;
    sc12 = 0;
    sc22 = 1;
  }
  if (sc22 == 1) {
    f32 = f32 - 1;
    lc.setLed(1, 0, f32 - 6, 0);
    lc.setLed(1, 1, f32 - 6, 0);
    lc.setLed(1, 2, f32 - 6 , 0);
    lc.setLed(1, 3, f32 - 6, 0);
    lc.setLed(2, 0, f32 + 2, 0);
    lc.setLed(2, 1, f32 + 2, 0);
    lc.setLed(2, 2, f32 + 2 , 0);
    lc.setLed(2, 3, f32 + 2, 0);
    lc.setLed(2, 0, f32 + 1, 1);
    lc.setLed(2, 1, f32 + 1, 1);
    lc.setLed(2, 2, f32 + 1, 1);
    lc.setLed(2, 3, f32 + 1, 1);
    lc.setLed(2, 0, f32, 1);
    lc.setLed(2, 1, f32, 1);
    lc.setLed(2, 2, f32, 1);
    lc.setLed(2, 3, f32, 1);
    if (y < 4 && (x1 + 4 < f32) && add == 1) {
      gameover = 1;
    }
    if (y < 4 && ((x1 - 4) < f32) && (x1 + 1 > f32) && add == 2) {
      gameover = 1;
    }
  }
  if (f32 < 0) {
    f32 = 8;
    sc22 = 0;
    sc32 = 1;
  }
  if (sc32 == 1) {
    f42 = f42 - 1;
    lc.setLed(2, 0, f42 - 6, 0);
    lc.setLed(2, 1, f42 - 6, 0);
    lc.setLed(2, 2, f42 - 6 , 0);
    lc.setLed(2, 3, f42 - 6, 0);
    lc.setLed(3, 0, f42 + 2, 0);
    lc.setLed(3, 1, f42 + 2, 0);
    lc.setLed(3, 2, f42 + 2 , 0);
    lc.setLed(3, 3, f42 + 2, 0);
    lc.setLed(3, 0, f42 + 1, 1);
    lc.setLed(3, 1, f42 + 1, 1);
    lc.setLed(3, 2, f42 + 1, 1);
    lc.setLed(3, 3, f42 + 1, 1);
    lc.setLed(3, 0, f42, 1);
    lc.setLed(3, 1, f42, 1);
    lc.setLed(3, 2, f42, 1);
    lc.setLed(3, 3, f42, 1);
    if (y < 4 && (x1 + 4 < f42) && add == 2) {
      gameover = 1;
    }
    if (y < 4 && ((x1 - 4) < f42) && (x1 + 1 > f42) && add == 3) {
      gameover = 1;
    }
  }
  if (f42 < 0) {
    f42 = 8;
    sc32 = 0;
  }

  // FOURTH WALL                                    //FOURTH WALL
  if (rand1 == 4 && cooldown4 == 0) {
    spawn4 = 1;
    cooldown4 = 1;
    cooldown3 = 1;
    rand1 = 0;
  }
  if (spawn4 == 1) {
    mgo4 = 6;
    show4 = 1;
    spawn4 = 0;
  }
  if (show4 == 1) {
    lc.setLed(0, 4, 7, 1);
    lc.setLed(0, 5, 7, 1);
    lc.setLed(0, 6, 7, 1);
    lc.setLed(0, 7, 7, 1);
    b = b + 1;
  }
  if (b > mgo4) {
    cooloff4 = 1;
    show4 = 0;
    on4 = 1;
    b = 0;
    mgo4 = 0;
  }
  if (on4 == 1) {
    f13 = f13 - 1;
    lc.setLed(0, 4, f13 + 2, 0);
    lc.setLed(0, 5, f13 + 2, 0);
    lc.setLed(0, 6, f13 + 2 , 0);
    lc.setLed(0, 7, f13 + 2, 0);
    lc.setLed(0, 4, f13 + 1, 1);
    lc.setLed(0, 5, f13 + 1, 1);
    lc.setLed(0, 6, f13 + 1, 1);
    lc.setLed(0, 7, f13 + 1, 1);
    lc.setLed(0, 4, f13, 1);
    lc.setLed(0, 5, f13, 1);
    lc.setLed(0, 6, f13, 1);
    lc.setLed(0, 7, f13, 1);
    if (y > 1 && ((x1 - 4) < f13) && (x1 + 1 > f13) && add == 0) {
      gameover = 1;
    }
  }

  if (cooloff4 == 1) {
    cooldown4 = 0;
    cooloff4 = 0;
    cooldown3 == 0;
  }

  if (f13 < 0) {

    f13 = 8;
    sc13 = 1;
    on4 = 0;
  }

  if (sc13 == 1) {
    f23 = f23 - 1;
    lc.setLed(0, 4, f23 - 6, 0);
    lc.setLed(0, 5, f23 - 6, 0);
    lc.setLed(0, 6, f23 - 6 , 0);
    lc.setLed(0, 7, f23 - 6, 0);
    lc.setLed(1, 4, f23 + 2, 0);
    lc.setLed(1, 5, f23 + 2, 0);
    lc.setLed(1, 6, f23 + 2 , 0);
    lc.setLed(1, 7, f23 + 2, 0);
    lc.setLed(1, 4, f23 + 1, 1);
    lc.setLed(1, 5, f23 + 1, 1);
    lc.setLed(1, 6, f23 + 1, 1);
    lc.setLed(1, 7, f23 + 1, 1);
    lc.setLed(1, 4, f23, 1);
    lc.setLed(1, 5, f23, 1);
    lc.setLed(1, 6, f23, 1);
    lc.setLed(1, 7, f23, 1);
    if (y > 1 && (x1 + 4 < f23) && add == 0) {
      gameover = 1;
    }
    if (y > 1 && ((x1 - 4) < f23) && (x1 + 1 > f23) && add == 1) {
      gameover = 1;
    }
  }
  if (f23 < 0) {
    f23 = 8;
    sc13 = 0;
    sc23 = 1;
  }
  if (sc23 == 1) {
    f33 = f33 - 1;
    lc.setLed(1, 4, f33 - 6, 0);
    lc.setLed(1, 5, f33 - 6, 0);
    lc.setLed(1, 6, f33 - 6 , 0);
    lc.setLed(1, 7, f33 - 6, 0);
    lc.setLed(2, 4, f33 + 2, 0);
    lc.setLed(2, 5, f33 + 2, 0);
    lc.setLed(2, 6, f33 + 2 , 0);
    lc.setLed(2, 7, f33 + 2, 0);
    lc.setLed(2, 4, f33 + 1, 1);
    lc.setLed(2, 5, f33 + 1, 1);
    lc.setLed(2, 6, f33 + 1, 1);
    lc.setLed(2, 7, f33 + 1, 1);
    lc.setLed(2, 4, f33, 1);
    lc.setLed(2, 5, f33, 1);
    lc.setLed(2, 6, f33, 1);
    lc.setLed(2, 7, f33, 1);
    if (y > 1 && (x1 + 4 < f33) && add == 1) {
      gameover = 1;
    }
    if (y > 1 && ((x1 - 4) < f33) && (x1 + 1 > f33) && add == 2) {
      gameover = 1;
    }
  }
  if (f33 < 0) {
    f33 = 8;
    sc23 = 0;
    sc33 = 1;
  }
  if (sc33 == 1) {
    f43 = f43 - 1;
    lc.setLed(2, 4, f43 - 6, 0);
    lc.setLed(2, 5, f43 - 6, 0);
    lc.setLed(2, 6, f43 - 6 , 0);
    lc.setLed(2, 7, f43 - 6, 0);
    lc.setLed(3, 4, f43 + 2, 0);
    lc.setLed(3, 5, f43 + 2, 0);
    lc.setLed(3, 6, f43 + 2 , 0);
    lc.setLed(3, 7, f43 + 2, 0);
    lc.setLed(3, 4, f43 + 1, 1);
    lc.setLed(3, 5, f43 + 1, 1);
    lc.setLed(3, 6, f43 + 1, 1);
    lc.setLed(3, 7, f43 + 1, 1);
    lc.setLed(3, 4, f43, 1);
    lc.setLed(3, 5, f43, 1);
    lc.setLed(3, 6, f43, 1);
    lc.setLed(3, 7, f43, 1);
    if (y > 1 && (x1 + 4 < f43) && add == 2) {
      gameover = 1;
    }
    if (y > 1 && ((x1 - 4) < f43) && (x1 + 1 > f43) && add == 3) {
      gameover = 1;
    }
  }
  if (f43 < -1) {
    f43 = 8;
    sc33 = 0;
  }
  drawplayer();
  while (gameover == 1) {
    digitalWrite(ledR, HIGH);
    while (score.length() == 2) {
      Serial.print("\n");
      Serial.print(score3);
      Serial.print("__");
      Serial.print(score4);
      score3 = score.charAt(0) - 48;
      if (score3 == 1) {
        display1 = 134;
      }
      if (score3 == 2) {
        display1 = 219;
      }
      if (score3 == 3) {
        display1 = 207;
      }
      if (score3 == 4) {
        display1 = 230;
      }
      if (score3 == 5) {
        display1 = 237;
      }
      if (score3 == 6) {
        display1 = 253;
      }
      if (score3 == 7) {
        display1 = 135;
      }
      if (score3 == 8) {
        display1 = 255;
      }
      if (score3 == 9) {
        display1 = 231;
      }
      if (score3 == 0) {
        display1 = 191;
      }
      digitalWrite(d4, HIGH);
      digitalWrite(d2, HIGH);
      digitalWrite(d3, LOW);
      updateShiftRegister();
      score4 = score.charAt(1) - 48;
      if (score4 == 1) {
        display1 = 134;
      }
      if (score4 == 2) {
        display1 = 219;
      }
      if (score4 == 3) {
        display1 = 207;
      }
      if (score4 == 4) {
        display1 = 230;
      }
      if (score4 == 5) {
        display1 = 237;
      }
      if (score4 == 6) {
        display1 = 253;
      }
      if (score4 == 7) {
        display1 = 135;
      }
      if (score4 == 8) {
        display1 = 255;
      }
      if (score4 == 9) {
        display1 = 231;
      }
      if (score4 == 0) {
        display1 = 191;
      }
      digitalWrite(d4, LOW);
      digitalWrite(d3, HIGH);
      updateShiftRegister();

      if (digitalRead(2) == 1) {
        gameover = 0;
        score = 1;
        f = 0;
      }
    }
    while (score.length() == 3) {
      score2 = score.charAt(0) - 48;
      if (score2 == 1) {
        display1 = 134;
      }
      if (score2 == 2) {
        display1 = 219;
      }
      if (score2 == 3) {
        display1 = 207;
      }
      if (score2 == 4) {
        display1 = 230;
      }
      if (score2 == 5) {
        display1 = 237;
      }
      if (score2 == 6) {
        display1 = 253;
      }
      if (score2 == 7) {
        display1 = 135;
      }
      if (score2 == 8) {
        display1 = 255;
      }
      if (score2 == 9) {
        display1 = 231;
      }
      if (score2 == 0) {
        display1 = 191;
      }
      digitalWrite(d4, HIGH);
      digitalWrite(d2, LOW);
      digitalWrite(d3, HIGH);
      updateShiftRegister();
      score3 = score.charAt(1) - 48;
      if (score3 == 1) {
        display1 = 134;
      }
      if (score3 == 2) {
        display1 = 219;
      }
      if (score3 == 3) {
        display1 = 207;
      }
      if (score3 == 4) {
        display1 = 230;
      }
      if (score3 == 5) {
        display1 = 237;
      }
      if (score3 == 6) {
        display1 = 253;
      }
      if (score3 == 7) {
        display1 = 135;
      }
      if (score3 == 8) {
        display1 = 255;
      }
      if (score3 == 9) {
        display1 = 231;
      }
      if (score3 == 0) {
        display1 = 191;
      }
      digitalWrite(d4, HIGH);
      digitalWrite(d2, HIGH);
      digitalWrite(d3, LOW);
      updateShiftRegister();
      score4 = score.charAt(2) - 48;
      if (score4 == 1) {
        display1 = 134;
      }
      if (score4 == 2) {
        display1 = 219;
      }
      if (score4 == 3) {
        display1 = 207;
      }
      if (score4 == 4) {
        display1 = 230;
      }
      if (score4 == 5) {
        display1 = 237;
      }
      if (score4 == 6) {
        display1 = 253;
      }
      if (score4 == 7) {
        display1 = 135;
      }
      if (score4 == 8) {
        display1 = 255;
      }
      if (score4 == 9) {
        display1 = 231;
      }
      if (score4 == 0) {
        display1 = 191;
      }
      digitalWrite(d4, LOW);
      digitalWrite(d2, HIGH);
      digitalWrite(d3, HIGH);
      updateShiftRegister();

      if (digitalRead(2) == 1) {
        gameover = 0;
        score = 1;
        f = 0;
        x = 7;
        y = 2;
        add = 1;
        x1 = 0;
        f = 0;
        needrand1 = 0;
        spawn1 = 0;
        mgo1 = 1000;
        show1 = 0;
        sc1 = 0;
        sc2 = 0;
        sc3 = 0;
      }
    }
  }
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, display1);
  digitalWrite(latchPin, HIGH);
  Serial.print("register");
  Serial.print("___");
  Serial.print(display1);

}
