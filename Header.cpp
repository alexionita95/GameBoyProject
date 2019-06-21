#include<Header.h>
#include<Colors.h>
#include<ShapeRenderer.h>
#include<TextRenderer.h>
#include "ESP8266WiFi.h"

Header::Header()
{
	width=240;
	height=95;
	x=0;
	y=204;
	title="";
}

void Header::render()
{
	Shape.fillRect(0,0,240,40,0x0397);
	Text.setTextSize(1);
	Text.setTextColor(TFT_WHITE);
	Text.drawCenterString(title,120,15,4);
	Shape.fillRect(0,0,240,10,TFT_BLACK);
	if(WiFi.status() != WL_CONNECTED)
	{
		Text.setTextColor(TFT_RED);
		Text.drawRightString("Offline",240,0,1);
	}
	else
	{
		Text.setTextColor(TFT_GREEN);
		Text.drawRightString("Online",240,0,1);
	}
	
}

Header Top;

