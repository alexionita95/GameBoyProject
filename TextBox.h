#ifndef TEXTBOX_H
#define TEXTBOX_H

#include<Arduino.h>


class TextBox
{
public:
TextBox();
TextBox(int _x, int _y, int w, int h);
void render();
void setText(String value)
{
	text=value;
	render();
}
private:
String text;
int x, y, width, height;


};
#endif