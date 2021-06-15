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
int btn_state = 0;     // 0 = nothing, 1 = p1, 2 = p2, 3 = both
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
  readBtnState();

  // menu
  if (mode == 0)
  {
    gameMenu();
  }
  // play
  else if (mode < 3)
  {
    setDisplayLine(0, "P1      P2");
    setDisplayLine(1, "          ");
    
    if (btn_state == 3)
    {
      mode = 5;
      digitalWrite(P1_LED_PIN, HIGH);
      digitalWrite(P2_LED_PIN, HIGH);
    }
    else
    {
      if (mode == 1)
      {
        if (btn_state == 1)
        {
          mode = 2;
          digitalWrite(P1_LED_PIN, LOW);
          digitalWrite(P2_LED_PIN, HIGH);
          p1 = p1 + inc;
        }
        else
        {
          setDisplayLine(2, longMsToString(p1, false));
          setDisplayLine(3, longMsToString(p2, true));
          p1 = p1 - DELAY;
          
          if (p1 <= 0)
            mode = 4;
        }
      }
      else if (mode == 2)
      {
        if (btn_state == 2)
        {
          mode = 1;
          digitalWrite(P1_LED_PIN, HIGH);
          digitalWrite(P2_LED_PIN, LOW);
          p2 = p2 + inc;
        }
        else
        {
          setDisplayLine(3, longMsToString(p1, false));
          setDisplayLine(2, longMsToString(p2, true));
          p2 = p2 - DELAY;
          
          if (p2 <= 0)
            mode = 3;
        }
      }
    }
  }
  // end / stand-by
  else
  {
    if (mode == 5)
    {
      setDisplayLine(1, " STAND BY ");
      if (btn_state == 1)
      {
        mode = 2;
        digitalWrite(P1_LED_PIN, LOW);
        digitalWrite(P2_LED_PIN, HIGH);
      }
      else if (btn_state == 2)
      {
        mode = 1;
        digitalWrite(P1_LED_PIN, HIGH);
        digitalWrite(P2_LED_PIN, LOW);
      }
    }
    if (mode == 4)
    {
      oled.clear();
      setDisplayLine(0, "          ");
      setDisplayLine(1, "  P1 WIN  ");
      setDisplayLine(2, "          ");
      setDisplayLine(3, "          ");
      //victoryMusic();
      mode = 0;
      oled.clear();
    }
    else if (mode == 5)
    {
      oled.clear();
      setDisplayLine(0, "          ");
      setDisplayLine(1, "  P2 WIN  ");
      setDisplayLine(2, "          ");
      setDisplayLine(3, "          ");
      //victoryMusic();
      mode = 0;
      oled.clear();
    }
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

void gameMenu()
{
  static int choice = 1;

  if (btn_state == 3)
  {
    mode = 5;
    switch(choice)
    {
      case -3:
        p1 = 3UL * 60000UL;
        inc = 2000;
        break;
      case -2:
        p1 = 2UL * 60000UL;
        inc = 1000;
        break;
      case -1:
        p1 = 1UL * 60000UL;
        inc = 1000;
        break;
      case 0:
        p1 = 5UL * 60000UL;
        inc = 0;
        break;
      case 1:
        p1 = 1UL * 60000UL;
        inc = 0;
        break;
      case 2:
        p1 = 3UL * 60000UL;
        inc = 0;
        break;
      case 3:
        p1 = 5UL * 60000UL;
        inc = 0;
        break;
      case 4:
        p1 = 10UL * 60000UL;
        inc = 0;
        break;
      case 5:
        p1 = 20UL * 60000UL;
        inc = 0;
        break;
      case 6:
        p1 = 30UL * 60000UL;
        inc = 0;
        break;
    }
    p2 = p1;
    return;
  }
  
  else if(btn_state == 2)
    choice++;
  else if (btn_state == 1)
    choice--;

  if (choice < -3)
    choice = -3;
  else if (choice > 6)
    choice = 6;
  
  switch(choice)
  {
    case -3:
      setDisplayLine(0, "3 min | 2");
      break;
    case -2:
      setDisplayLine(0, "2 min | 1");
      break;
    case -1:
      setDisplayLine(0, "1 min | 1");
      break;
    case 0:
      setDisplayLine(0, "5 min diff");
      break;
    case 1:
      setDisplayLine(0, "1 min ");
      break;
    case 2:
      setDisplayLine(0, "3 min ");
      break;
    case 3:
      setDisplayLine(0, "5 min ");
      break;
    case 4:
      setDisplayLine(0, "10 min");
      break;
    case 5:
      setDisplayLine(0, "20 min");
      break;
    case 6:
      setDisplayLine(0, "30 min");
      break;
  }
}
