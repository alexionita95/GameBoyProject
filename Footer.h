#ifndef FOOTER_H
#define FOOTER_H

#include<Arduino.h>


class Footer
{
public:
Footer();
void render();
void update();
void setTopText(String value)
{
	topText=value;
	render();
}
void setBottomText(String value)
{
	bottomText=value;
	render();
}
private:
String topText;
String bottomText;
int x, y, width, height;
};
extern Footer Bottom;
#endif