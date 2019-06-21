#include<TextBox.h>
#include<Colors.h>
#include<ShapeRenderer.h>
#include<TextRenderer.h>

TextBox::TextBox()
{
	width=240;
	height=95;
	x=0;
	y=204;
	text="";
}
TextBox::TextBox(int _x, int _y, int w, int h)
{
	width=w;
	height=h;
	x=_x;
	y=_y;
	text="";
}
void TextBox::render()
{
	Shape.fillRect(x,y,width,height,TFT_WHITE);
	Shape.drawRect(x,y,width,height,TFT_BLACK);
	Text.setTextSize(1);
	Text.setTextColor(TFT_BLACK);
	Text.drawString(text,x+2,y+2,2);
	
}


