/*
SLRTimelapse v 0.3

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
  pinMode(shutter, OUTPUT);  // must be set low again or there may be burst mode
  
}

void loop() {
   
  int x;                          //button state
  int y;                          //minutes
  int z;                          //seconds
  x = analogRead (0);
  if (x == 1023){                    //display Main Screen if no Button is pressed
    lcd.home();                      //set cursor to 0,line 0
    lcd.print("Nikon SLR RC Mod");
    lcd.setCursor(0,1);              //set cursor to 0,line 1
    lcd.print("^v<>=set sel=run");
  }
  if (x == 144){                    //increase interval if up is pressed
    delay(150);
    picint++;
  }
  else if (x == 330 && picint > 0){ //decrease interval if down is pressed
    delay(150);
    picint--;
        }
  if (x ==144 || x == 330){         //display settings for seconds if up or down is pressed
    lcd.home();
    lcd.print("Timelapse Mode");
    lcd.setCursor(0,1);
    lcd.print("Set Seconds:");
    lcd.setCursor(13,1);
    lcd.print(picint);
    delay(300);
  }
  if ( x == 0 ){                    //increase amount if right is pressed
    delay(150);
    picnr=picnr + 10;
  }
  else if (x == 506 && picnr >0){   //decrease amount if left is pressed
    delay(150);
    picnr=picnr - 10;
  }
  if (x == 0 || (x == 506)){        //display settings for number of pictures if left or right is pressed
    lcd.home();
    lcd.print("Timelapse Mode");
    lcd.setCursor(0,1);
    lcd.print("Nr of Pics:");
    lcd.setCursor(12,1);
    lcd.print(picnr);
    delay(300);
  }
  else if (x == 742 && picint >0 && picnr >0){    //run if select is pressed and at least 1 second is set
    for (piccnt = 0; piccnt < picnr; piccnt++){
      lcd.home();
      lcd.print("Running");
      lcd.setCursor(8,0);
      lcd.print(piccnt);
      lcd.setCursor(13,0);
      lcd.print("of");
      lcd.setCursor(0,1);
      lcd.print(picnr);
      lcd.setCursor(5,1),
      y=(picint*(picnr-piccnt)/60);                //calculate  minutes
      lcd.print(y);
      lcd.setCursor(8,1);
      lcd.print("min");
      lcd.setCursor(12,1);
      z=(((picnr-piccnt)*picint)-(y*60));          //calculate seconds
      lcd.print(z);
      lcd.setCursor(14,1);
      lcd.print("s");
      digitalWrite(focus, HIGH);    //get focus
      delay(200);                   //wait for focus
      digitalWrite(shutter, HIGH);  //shoot
      delay(20);
      digitalWrite(shutter, LOW);
      digitalWrite(focus,LOW);
      delay(picint*1000);           //delay of time set
      lcd.clear();		    //
    } 
    lcd.clear();
    lcd.home();
    lcd.print("Done!");
    delay(1000);
  }
  delay(50);
  lcd.clear();                      //clear up remaining stuff
}
 
