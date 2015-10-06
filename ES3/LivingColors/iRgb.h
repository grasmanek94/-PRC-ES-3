#ifndef IRGB_H
#define IRGB_H

enum ERGBOutput
{
	Led,
	Serialp
};

class iRgb
{
private:
public:

	//virtual void Init() = 0;
	virtual void SetColor(int hue) = 0;

};

#endif


