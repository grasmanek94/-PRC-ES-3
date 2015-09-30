#include "Led.h"

/*
Example blink using OO concepts
 
 modified 24-9-2015
 by Peter Dingemans
 */

Led led1(13);
Led led2(9);
Led led3(11);
Led led4(10);

// the setup function runs once when you press reset or power the board
void setup()
{
  led1.Blink(3);
  led2.Blink(2);
  led3.Blink(3);  
  led4.Blink(5); 
}

// the loop function runs over and over again forever
void loop()
{
  while (true)
  {
    led1.beActive(); 
    led2.beActive();    
    led3.beActive();
    led4.beActive();
  }
}


