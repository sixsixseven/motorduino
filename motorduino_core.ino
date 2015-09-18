//Arduino references https://www.arduino.cc/en/Reference/HomePage
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12,11,9,8,7,6,5,4,3,2);

const int			mphPot = A0;
const int			lBlinker = 13;
const int			rBlinker = 10;
const long			interval1k = 250;

float		        gearRatio = 0.015455;

int			        mph = 0;
int			        rpm = 0;
int			        mphPotValue = 0;
int			        blinkerLastVal = 0;
int			        lBlinkerState = 0;
int			        rBlinkerState = 0;
int			        currentBlinker = 0;
int					interval = 0;

unsigned long		currentMillis = 0;
unsigned long		previousMillis = 0;


void setup() {
  pinMode(mphPot,INPUT);
  pinMode(lBlinker,INPUT);
  pinMode(rBlinker,INPUT);
  
  // set up the LCD's number of columns and rows: (123d.circuits.io only?)
  lcd.begin(16,2);
  
  //Place MPH and RPM on the screen.
  lcd.setCursor(10,0);
  lcd.print("mph");
  lcd.setCursor(10,1);
  lcd.print("rpm");
}



void loop() {
  
  //MPH Logic
  mphPotValue = analogRead(mphPot);
  mph = map(mphPotValue,0,1023,0,85);
  lcd.setCursor(8,0);
  lcd.print(mph);
    
  //RPM Logic
  lcd.setCursor(6,1);
  rpm = mph / gearRatio;
  lcd.print(rpm);
  
  //Blinkers
  lBlinkerState = digitalRead(lBlinker);
  rBlinkerState = digitalRead(rBlinker);
  if (lBlinkerState == HIGH || rBlinkerState == HIGH){
    if (lBlinkerState == HIGH) {currentBlinker = 1;}
    else if (rBlinkerState == HIGH) {currentBlinker = 2;}
  } else {currentBlinker = 0;}
  
  switch (currentBlinker){
    case 1:
    currentMillis = millis();
      if (currentMillis - previousMillis >= interval1k) {
    // save the last time the blinker blinked
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    	lcd.setCursor(0,1);
  		lcd.print("<");
    } else {
		lcd.setCursor(0,1);
        lcd.print(" ");
    }
    break;
        
    case 2:
    currentMillis = millis();
      if (currentMillis - previousMillis >= interval1k) {
    // save the last time the blinker blinked
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    	lcd.setCursor(15,1);
  		lcd.print(">");
    } else {
		lcd.setCursor(15,1);
        lcd.print(" ");
    }
    	break;
    
    default:
    	currentBlinker = 0;
    	break;
  }
  
}






