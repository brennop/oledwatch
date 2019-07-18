#include "ssd1306.h"
#include <Wire.h>
#include <Time.h>
// ============================================================================

#define SETBUTTON 3
#define UPBUTTON 4
#define NUMFIELDS 6 // fields + none

const uint8_t vertical[] = {1,1,1,1};

int settingUp;
bool setPressed;
bool upPressed;

void setup() {
  // put your setup code here, to run once:
  pinMode(SETBUTTON, INPUT_PULLUP);
  pinMode(UPBUTTON, INPUT_PULLUP);

  oled.begin();
  oled.clear(); // all black
  settingUp = 0; // not setting up the clock

  setPressed = false;
  upPressed = false;
}

void loop() {
  handleInput();

  // Show Clock
  oled.setFont(BIG);
  oled.setCursor(28, 2); // Clock offset
  printNumber(hour(), settingUp % NUMFIELDS == 1);
  oled.setCursor(28, 4);
  printNumber(minute(), settingUp % NUMFIELDS == 2);

  // Show Date
  oled.setFont(SMALL);
  oled.setCursor(56, 2);
  oled.print(F(">"));
  printDay();
  
  oled.setCursor(56, 3);
  oled.print(F(">"));
  printNumber(day(), settingUp % NUMFIELDS == 3);
  oled.setCursor(80, 3);
  oled.print(F("DE"));

  oled.setCursor(56, 4);
  oled.print(F(">"));
  printMonth(settingUp % NUMFIELDS == 4);

  oled.setCursor(56, 5);
  oled.print(F(">"));
  printNumber(year(), settingUp % NUMFIELDS == 5);

}

void printNumber(int n, bool invert){
  if(invert) oled.setInvert(true);
  
  if(n < 10)
    oled.print(0);
  oled.print(n);

  oled.setInvert(false);
}

void handleInput(){  
  if(digitalRead(SETBUTTON) == LOW){
    if(!setPressed){
      setPressed = true;
      settingUp++;
    }
  }else{
      setPressed = false;
  }

  if(digitalRead(UPBUTTON) == LOW){
    if(!upPressed){
      upPressed = true;
      
      int adjustment = 0;
      switch(settingUp % NUMFIELDS){
         case 1: // hour
          adjustment = 3600;
          break;
         case 2: // minutes
          adjustment = 60;
          break;
         case 3: // day
          setTime(now() + 86400);
          break;
         case 4:
          setTime(hour(), minute(), second(), day(), month() + 1, year());
          break;
         case 5:
          setTime(hour(), minute(), second(), day(), month(), year() + 1);
          break;
      }
  
       adjustTime(adjustment);
    }else{
      upPressed = false;
    }
  }
}


// without padding: 5892
// with 5936
void printDay(){ // does not return a char* for memory sake
  switch(weekday()){
    case 1:
      oled.print(F("DOMINGO;"));
      break;
    case 2:
      oled.print(F("SEGUNDA;"));
      break;
    case 3:
      oled.print(F("TER<A;??")); // "<" = "ç"
      break;
    case 4:
      oled.print(F("QUARTA;?"));
      break;
    case 5:
      oled.print(F("QUINTA;?"));
      break;
    case 6:
      oled.print(F("SEXTA;??"));
      break;
    case 7:
      oled.print(F("S=BADO;?")); // "=" = á
      break;
  }
}

void printMonth(bool selected){
  if(selected) oled.setInvert(true);
  
  switch(month()){
    case 1:
      oled.print(F("JANEIRO??"));
      break;
    case 2:
      oled.print(F("FEVEREIRO"));
      break;
    case 3:
      oled.print(F("MAR<O????"));
      break;
    case 4:
      oled.print(F("ABRIL????"));
      break;
    case 5:
      oled.print(F("MAIO?????"));
      break;
    case 6:
      oled.print(F("JUNHO????"));
      break;
    case 7:
      oled.print(F("JULHO????"));
      break;
    case 8:
      oled.print(F("AGOSTO???"));
      break;
    case 9:
      oled.print(F("SETEMBRO?"));
      break;
    case 10:
      oled.print(F("OUTUBRO??"));
      break;
    case 11:
      oled.print(F("NOVEMBRO?"));
      break;
    case 12:
      oled.print(F("DEZEMBRO?"));
      break;
  }

  oled.setInvert(false);
}
