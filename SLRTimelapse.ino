/*
SLRTimelapse v 0.3.1

Used for setting time between shutter releases and number of pictures taken for Timelapse feature.
It's displaying amount of pictures taken and the time left while running.
Keypad LCD Shield from here http://www.exp-tech.de/Displays/Arduino-1602-LCD-Keypad-Shield.html
Button Values
Up=144
Down=330
Left=506
Right=0
Select=742
*/
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int picint = 0;     //time between pictures
int picnr = 0;      //number of pictures to take
int piccnt = 0;     //picture counter
int focus = 2;      //Pin to Camera Focus
int shutter = 3;    //Pin to Camera Shutter

void setup() {
  lcd.begin(16, 2);          // set up the LCD's number of columns and rows
  pinMode(focus, OUTPUT);    // focus, must be high before shutter can be released
  pinMode(shutter, OUTPUT);  // must be set low again or there maybe burst mode

}

void loop() {
   
  int x;                          //button state
  int y;                          //minutes
  int z;                          //seconds
  x = analogRead (0);

  switch (x) {
    default:  //display Main Screen if no Button is pressed
      delay(300);
      lcd.home();                   //set cursor to 0,line 0
      lcd.print("Nikon SLR RC Mod");
      lcd.setCursor(0,1);           //set cursor to 0,line 1
      lcd.print("^v<>=set sel=run");
    break;

    case 0:    //increase amount and show settings if right is pressed
      lcd.clear();
      picnr= picnr +10;
      lcd.home();
      lcd.print("Timelapse Mode");
      lcd.setCursor(0,1);
      lcd.print("Nr of Pics:");
      lcd.setCursor(12,1);
      lcd.print(picnr);
      delay(200);
    break;

    case 506: //decrease amount and show settings if left is pressed
      lcd.clear();
      if(picnr >0){
        picnr= picnr -10;
      }
      lcd.home();
      lcd.print("Timelapse Mode");
      lcd.setCursor(0,1);
      lcd.print("Nr of Pics:");
      lcd.setCursor(12,1);
      lcd.print(picnr);
      delay(200);
    break;

    case 144:  //increase interval and show settings if up is pressed
      lcd.clear();
      picint++;
      lcd.home();
      lcd.print("Timelapse Mode");
      lcd.setCursor(0,1);
      lcd.print("Set Seconds:");
      lcd.setCursor(13,1);
      lcd.print(picint);
      delay(200);
    break;

    case 330:  //decrease interval and show settings if down is pressed
      lcd.clear();
      if (picint >0 && x== 330){
        picint--;
      }
      lcd.home();
      lcd.print("Timelapse Mode");
      lcd.setCursor(0,1);
      lcd.print("Set Seconds:");
      lcd.setCursor(13,1);
      lcd.print(picint);
      delay(200);
    break;

    case 742: //start shooting if at least one second and 10 pics are selected, otherwise show min requirements
      if(picnr >0 && picint >0){
        for (piccnt = 0; piccnt < picnr; piccnt++){
          lcd.clear();
          lcd.home();
          lcd.print("Pic");
          lcd.setCursor(4,0);
          lcd.print(piccnt);
          lcd.setCursor(9,0);
          lcd.print("of");
          lcd.setCursor(12,0);
          lcd.print(picnr);
          lcd.setCursor(0,1),
          y=(picint*(picnr-piccnt)/60);             //calculate  minutes
          lcd.print(y);
          lcd.setCursor(2,1);
          lcd.print("min");
          lcd.setCursor(6,1);
          z=(((picnr-piccnt)*picint)-(y*60));       //calculate seconds
          lcd.print(z);
          lcd.setCursor(8,1);
          lcd.print("sec left");
          digitalWrite(focus, HIGH);                //get focus
          delay(200);                               //wait for focus
          digitalWrite(shutter, HIGH);              //shoot
          delay(20);
          digitalWrite(shutter, LOW);
          digitalWrite(focus,LOW);
          delay((picint*1000)-220);                       //delay of time set minus focus wait and shutter delay    
        }
        lcd.clear();
        lcd.home();
        lcd.print("Done!");
        delay(1000);
      }
      else{
        lcd.home();
        lcd.print("min. 10 pics and");
        lcd.setCursor(0,1);
        lcd.print("1sec must be set");
        delay(3000);
      }
    break;
  }
}
