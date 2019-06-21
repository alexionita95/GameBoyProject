#include<Footer.h>
#include<Colors.h>
#include<ShapeRenderer.h>
#include<TextRenderer.h>

Footer::Footer()
{
	width=240;
	height=95;
	x=0;
	y=204;
	topText="";
	bottomText="";

}

void Footer::render()
{
	Text.setTextColor(TFT_WHITE);
	Shape.fillRect(0,300,240,20,0x0397);
	Text.drawString(topText,5,302,1);
	Text.drawString(bottomText,5,312,1);
}

Footer Bottom;

