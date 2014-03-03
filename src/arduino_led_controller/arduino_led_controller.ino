/*
  Developer Podcast 
  Folge: DP001-Arduino_LED_Controller
  
  Marko Seifert
  http://www.marko-seifert.de
  Apache 2 License
 
*/

#include <LiquidCrystal.h>

LiquidCrystal* lcd ;
enum BtnKey {btnRIGHT, btnUP, btnDOWN, btnLEFT, btnSELECT, btnNONE};
int oldkey = btnNONE;

enum state{stateOn,stateOff};
int currentState = stateOff;

void setup() {
  lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
  lcd->clear();
  lcd->begin(16, 2);
  lcd->setCursor(0, 0);
  lcd->print("DP001:");
  lcd->setCursor(0, 1);
  lcd->print("A-LED-Controller");


}

void onButtonClickCallBack(unsigned int buttonEvent){
  
  lcd->clear();
  lcd->setCursor(0, 1);

  switch(buttonEvent){
   case btnRIGHT:
     lcd->print("btnRIGHT");
     break;
   case btnUP:
     lcd->print("btnUP");
     break; 
   case btnDOWN: 
     lcd->print("btnDOWN");
     break;
   case btnLEFT: 
     lcd->print("btnLEFT");
     break;
   case btnSELECT: 
     if(currentState == stateOff){
       currentState = stateOn;
       lcd->setCursor(0, 0);
       lcd->print("LEDs an");
       lcd->setCursor(0, 1);
       lcd->print("[aus]");
     }else{
       currentState = stateOff;
       lcd->setCursor(0, 0);
       lcd->print("LEDs aus");
       lcd->setCursor(0, 1);
       lcd->print("[an]");
     
     }
     break;
   case btnNONE:
     lcd->print("btnNONE");
     break;
  }
  

  
}
void readButtonValue() {

  int adc_key_in = analogRead(0);
  
  int key = transform(adc_key_in);
  if (key != oldkey) {
    delay(50);
    adc_key_in = analogRead(0);
    key = transform(adc_key_in);
    if (key != oldkey) {
      oldkey = key;
      if (key != btnNONE) {
        //debugEvent(adc_key_in);
        onButtonClickCallBack(key);
      }
    }
  }
}
void debugEvent(unsigned int event){
  lcd->clear();
  lcd->setCursor(0, 1);
  char buffer[16];
  sprintf(buffer, "Event: %d", event);
  lcd->print(buffer);
}
int transform(unsigned int input) {
  if (input > 1000)		
    return btnNONE;
  else if (input < 50)
    return btnRIGHT;
  else if (input < 195)
    return btnUP;
  else if (input < 380)
    return btnDOWN;
  else if (input < 555)
    return btnLEFT;
  else if (input < 790)
    return btnSELECT;
  else
    return btnNONE;
}

void loop() {
  
  readButtonValue();
 
}
