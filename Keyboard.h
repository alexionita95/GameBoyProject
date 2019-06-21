#ifndef KEYBOARD_H
#define KEYBOARD_H_H

#include<Arduino.h>


class Keyboard
{
public:
Keyboard();
void render();
void update();
void setSelKey(int i, int j)
{
	lastRow=selRow;
	lastCol=selCol;
	selRow=i;
	selCol=j;
	if(selCol < 0)
		selCol=0;
	if(selRow < 0)
		selRow=0;
	
	if(selCol > 12)
		selCol=12;
	if(selRow > 4)
		selRow = 4;
}
int getSelRow()
{
	return selRow;
}
int getSelCol()
{
	return selCol;
}
String getCurrentWord()
{
	return currentWord;
}
void addToCurrentWord()
{
	if(selRow== 4&& selCol==4)
	{
		caps=!caps;
		render();
		update();
	}
	else{
		char c=keys[selRow][selCol];
	if(caps)
		if('a'<=c && c <='z')
		currentWord+=(char)(c-32);
		else
			currentWord+=(char)(c);
	else
		currentWord+=keys[selRow][selCol];
	}
}
void backspace()
{
	if(currentWord.length() != 0)
	currentWord.remove(currentWord.length()-1);
}
private:
String currentWord;
int x, y, width, height;
int selRow;
int selCol;
int lastCol;
int lastRow;
bool inited;
bool caps;
char keys[5][13]=
{{'1','2','3','4','5','6','7','8','9','0','-','_','='},
{'q','w','e','r','t','y','u','i','o','p','[',']','\\'}, 
{'a','s','d','f','g','h','l',';',':','‘','“','(',')'},
{'z','x','c','v','b','n','m',',','.','<','>','/','?'},
{'!','@','#','$','s',' ',' ',' ','+','%','^','&','*'}}; 

};
extern Keyboard Keys;
#endif