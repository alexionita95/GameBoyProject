#ifndef HEADER_H
#define HEADER_H

#include<Arduino.h>


class Header
{
public:
Header();
void render();
void setTitle(String value)
{
	title=value;
	render();
}
private:
String title;
int x, y, width, height;


};
extern Header Top;
#endif