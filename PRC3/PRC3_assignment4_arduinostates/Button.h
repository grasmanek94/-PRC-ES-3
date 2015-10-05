#ifndef BUTTON_H
#define BUTTON_H

class Button
{
  public:
    Button(int pin);
    ~Button();
    bool Pressed();
    
  private:
    int ButtonPin;
    long prevTime;
};

#endif
