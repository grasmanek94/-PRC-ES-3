#ifndef ISENSOR_H
#define ISENSOR_H

class ISensor {
  private:
    int _Min;
    int _Max;
  public:
    ISensor(int _Min, int _Max):_Min(_Min), _Max(_Max) {}
    virtual int GetValue();
    virtual int GetMin();
    virtual int GetMax();
};

#endif
