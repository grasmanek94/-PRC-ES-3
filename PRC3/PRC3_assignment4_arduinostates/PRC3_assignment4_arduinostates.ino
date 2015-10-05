#include "Led.h"
#include "Button.h"

/*
Example blink using OO concepts
 
 modified 24-9-2015
 by Peter Dingemans
 */
Led led1(9);
Led led2(13);
Led led3(11);
Led led4(10);
Button button1(8);
Timer buttonTimer;
int led1s = 0;
//long timeNow = 0;


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  led1.Blink(4);
  led2.Blink(2);
  led3.Blink(3);  
  led4.Blink(5); 
}

// the loop function runs over and over again forever
void loop() {
  while (true) {
    switch (led1s) {
      case 1:
        if (buttonTimer.Elapsed()) {

          led1.Off();
        }
        if (button1.Pressed()) {
          led1s = 0;
        }
        break;
      default:
        if (button1.Pressed()) {
          led1s = 1;
          buttonTimer.Start(5000);
          led1.On();

        }
        led1.beActive();
        break;
    }
    
    led2.beActive();
    led3.beActive();
    led4.beActive();
  }
}

