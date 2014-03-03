/*
  Developer Podcast 
  Folge: DP001-Arduino_LED_Controller
  
  Marko Seifert
  http://www.marko-seifert.de
  Apache 2 License
 
*/

#include <LiquidCrystal.h>

LiquidCrystal* lcd ;

void setup() {
  lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
  lcd->clear();
  lcd->begin(16, 2);
  lcd->setCursor(0, 0);
  lcd->print("DP001:");
  lcd->setCursor(0, 1);
  lcd->print("A-LED-Controller");


}
void loop() {
 
}
