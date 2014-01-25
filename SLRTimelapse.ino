/*
SLRTimelapse v 0.1

Used for settings time between shutter releases for Timelapse feature and displaying 
amount of pictures taken.
Keypad LCD Shield from here http://www.exp-tech.de/Displays/Arduino-1602-LCD-Keypad-Shield.html

*/
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int picint = 0;     //time between pictures
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
  x = analogRead (0);
  if (x >800){                    //display Main Screen if no Button is pressed
    lcd.home();                   //set cursor to 0,line 0
    lcd.print("Nikon SLR RC Mod");
    lcd.setCursor(0,1);           //set cursor to 0,line 1
    lcd.print("^v=set sel=run");
  }
    if (x <600){                  //display settings if left,right,up or down is pressed
    lcd.home();                   
    lcd.print("Timelapse Mode");
    lcd.setCursor(0,1);
    lcd.print("Set Seconds:");
    lcd.setCursor(13,1);
    lcd.print(picint);
    }
  
  if (x < 200 && x >100){         //increase interval
    delay(150);
    picint++;
    
  }
  else if (x <400 && x >100){     //decrease interval
    delay(150);
    picint--;
  }
  else if (x <800 && x >600 && picint >0){           //run if select is pressed and at least 1 second is set
      for (piccnt = 0; piccnt < 9999; piccnt++){
      lcd.home();
      lcd.print("Running");
      lcd.setCursor(0,1);
      lcd.print(piccnt);
      digitalWrite(focus, HIGH);                //get focus
      delay(200);                               //wait for focus
      digitalWrite(shutter, HIGH);              //shoot
      delay(20);
      digitalWrite(shutter, LOW);
      delay(picint*1000);                       //delay of time set before minus focus delay
    } 
  }
  delay(50);
  lcd.clear();                                  //clear up remaining stuff
}
 
