#include<Keyboard.h>
#include<Colors.h>
#include<ShapeRenderer.h>
#include<TextRenderer.h>

Keyboard::Keyboard()
{
	width=240;
	height=95;
	x=0;
	y=204;
	selCol=0;
	selRow=0;
	lastRow=0;
	lastCol=0;
	currentWord="";
	caps=false;
}

void Keyboard::render()
{
	uint16_t keyBg=0x0A0C;
	uint16_t boardBg=0x0397;
	int gap=Text.fontHeight(2);
	Shape.fillRect(x,y,width-1,height-1,boardBg);
	Shape.drawRect(x,y,width,height,TFT_BLACK);
	for(int i=0;i<5;++i)
	{
		for(int j=0;j<13;++j)
		{
			int localX = x+4+j*(gap+2);
			int localY = y+4+i*(gap+2);
			Shape.fillRect(localX,localY,gap,gap,keyBg);
			Text.setTextColor(TFT_WHITE);
			char k=keys[i][j];
			if('a'<=k && k <='z')
			{
				if(caps)
				k-=32;
			}
			Text.drawCenterString(String(k),localX+gap/2,localY,2);
		}
	}
}
void Keyboard::update()
{
	uint16_t keyBg=0x0A0C;
	uint16_t selKeyBg=0x6DDD;
	uint16_t boardBg=0x0397;
	int gap=Text.fontHeight(2);
	int localX = x+4+lastCol*(gap+2);
	int localY = y+4+lastRow*(gap+2);
	int newX = x+4+selCol*(gap+2);
	int newY = y+4+selRow*(gap+2);
	Shape.fillRect(localX,localY,gap,gap,keyBg);
	Shape.fillRect(newX,newY,gap,gap,selKeyBg);
	Text.setTextColor(TFT_WHITE);
	char k=keys[lastRow][lastCol];
	if('a'<=k && k <='z'){
		if(caps)
				k-=32;
	}
	Text.drawCenterString(String(k),localX+gap/2,localY,2);
	k=keys[selRow][selCol];
	if('a'<=k && k <='z')
		if(caps)
				k-=32;
	Text.drawCenterString(String(k),newX+gap/2,newY,2);
}
Keyboard Keys;
