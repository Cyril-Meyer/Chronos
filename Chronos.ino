/*
 * Chronos
 */

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define I2C_ADDRESS 0x3C
#define RST_PIN -1

#define P1_BTN_PIN 9
#define P2_BTN_PIN 8
#define P1_LED_PIN 7
#define P2_LED_PIN 6

#define DELAY 100

SSD1306AsciiWire oled;

long p1 = 0;  // time left for player 1 (ms)
long p2 = 0;  // time left for player 2 (ms)
long inc = 0; // time increment (ms)
int mode = 0;          // 0 = menu, 1 = p1, 2 = p2, 3 = p1win, 4 = p2win, 5 = stand-by
int game_mode = 0;     // 0 = normal, 1 = diff
int btn_state = 0;     // 0 = nothing, 1 = p1, 2 = p2, 3 = both
int btn_change = 0;
char L[4][11];
unsigned long t0;
unsigned long t1;

void setup()
{
  Serial.begin(9600);
  
  pinMode(P1_BTN_PIN, INPUT);
  pinMode(P2_BTN_PIN, INPUT);
  pinMode(P1_LED_PIN, OUTPUT);
  pinMode(P2_LED_PIN, OUTPUT);
  
  digitalWrite(P1_LED_PIN, LOW);
  digitalWrite(P2_LED_PIN, LOW);

  Wire.begin();
  Wire.setClock(400000L);
  
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);
  oled.clear();
  oled.set2X();

  for(int i = 0 ; i < 4 ; ++i)
  {
    for(int j = 0 ; j < 10 ; ++j)
    {
      L[i][j] = ' ';
    }
    L[i][10] = 0;
  }
}

void loop()
{
  t0 = millis();
  btn_change = (int)readBtnState();

  // menu
  if (mode == 0)
  {
    gameMenu();
  }
  // play
  else if (mode < 3)
  {
    gamePlay();
  }
  // end / stand-by
  else
  {
    gamePause();
  }
  
  t1 = millis();
  int td = (t1 - t0);
  // only delay if loop take less than delay
  if (td < DELAY)
    delay(DELAY - td);
}

bool readBtnState()
{
  int new_btn_state = digitalRead(P1_BTN_PIN) + 2*digitalRead(P2_BTN_PIN);
  if (new_btn_state == btn_state)
    return false;
  else
    btn_state = new_btn_state;
  return true;
}
