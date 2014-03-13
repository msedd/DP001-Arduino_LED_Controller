/*
  Developer Podcast 
  Folge: DP001-Arduino_LED_Controller
  
  Marko Seifert
  http://www.marko-seifert.de
  Apache 2 License
 
*/

#include <LiquidCrystal.h>

struct RGB {
    byte red;
    byte green;
    byte blue;
};


RGB black = {0,0,0};
RGB white = {255,255,255};
RGB red = {255,0,0};
RGB green = {0,255,0};
RGB blue = {0,0,255};
RGB cyan = {0,255,255};
RGB magenta = {255,0,255};
RGB yellow = {255,255,0};

const int R_LED = 11;
const int G_LED = 12;
const int B_LED = 13;


RGB colors[7]   = {red, green, blue, cyan, magenta, yellow, white};
String strColors[7] = {"red", "green", "blue", "cyan", "magenta", "yellow", "white"};
int currentColorIndex = 0;

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
  
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);     
}

void updateColor(){
  lcd->setCursor(0, 0);
  lcd->print(strColors[currentColorIndex]);
  
  if(currentState == stateOn){
    
    digitalWrite(R_LED, colors[currentColorIndex].red); 
    digitalWrite(G_LED, colors[currentColorIndex].green); 
    digitalWrite(B_LED, colors[currentColorIndex].blue); 
  }
}
void switchOff(){
  digitalWrite(R_LED, black.red); 
  digitalWrite(G_LED, black.green); 
  digitalWrite(B_LED, black.blue); 
}

void onButtonClickCallBack(unsigned int buttonEvent){
  
  lcd->clear();

  switch(buttonEvent){
   case btnRIGHT:
     break;
   case btnUP:
     currentColorIndex = (currentColorIndex+1) %7;
     updateColor();
     break; 
   case btnDOWN: 
     currentColorIndex = (7+currentColorIndex-1) %7;
     updateColor();
     break;
   case btnLEFT: 
     break;
   case btnSELECT: 
     if(currentState == stateOff){
       currentState = stateOn;
       lcd->setCursor(0, 1);
       lcd->print("LEDs an ->");
       lcd->setCursor(11, 1);
       lcd->print("<aus>");
       updateColor();
     }else{
       currentState = stateOff;
       lcd->setCursor(0, 1);
       lcd->print("LEDs aus ->");
       lcd->setCursor(12, 1);
       lcd->print("<an>");
       switchOff();
     
     
     }
     break;
   case btnNONE:
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
