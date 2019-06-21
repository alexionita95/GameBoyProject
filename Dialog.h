#ifndef DIALOG_H
#define DIALOG_H

#include<Arduino.h>


class Dialog
{
public:
Dialog();
void render();
void setTitle(String value)
{
	title=value;
	render();
}
private:
String title;
int x, y, width, height;

public:
static void show(String title,String message1, String message2)
{
	Shape.fillRect(10,110,220,100,0x0397);
	Text.setTextSize(1);
	Text.setTextColor(TFT_WHITE);
	Text.drawString(title,15,112,2);
	Text.drawString(message1,15,132,1);
	Text.drawString(message2,15,142,1);
	
}
};
#endif