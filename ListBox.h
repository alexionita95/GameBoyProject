#ifndef LISTBOX_H
#define LISTBOX_H

#include<Arduino.h>


class ListBox
{
public:
ListBox();
ListBox(int _x,int _y, int _width, int _height, int itemC);
void addItem(const char* item);
void render();
void update();
int getSelectedIndex()
{
	return selectedIndex;
}
char* getSelectedItem()
{
	return items[selectedIndex];
}
void setSelectedIndex(int value)
{
	lastIndex=selectedIndex;
	selectedIndex=value;
	if(selectedIndex >currentItemCount-1)
		selectedIndex=currentItemCount-1;
	
	if(selectedIndex < 0)
		selectedIndex=0;
}
void setItemCount(int value)
{
	itemCount=value;
	currentItemCount=0;
	items = (char**)malloc(itemCount*sizeof(char*));
}
private:
int x, y, width, height;
int selectedIndex;
int lastIndex;
int itemCount;
int currentItemCount;
char** items;
bool inited;


int visibleStart;
int visibleEnd;

void calculateVisibleItems();

};
#endif