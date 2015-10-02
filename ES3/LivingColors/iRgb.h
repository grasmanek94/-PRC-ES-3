#ifndef IRGB_H
#define IRGB_H

class iRgb
{
private:
public:
	enum EOutput
	{
		Led,
		Serialp
	};
	//virtual void Init() = 0;
	virtual void SetColor(int hue) = 0;

};

typedef iRgb::EOutput ERGBOutput;
#endif


