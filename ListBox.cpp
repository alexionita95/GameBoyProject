#include<ListBox.h>
#include<Colors.h>
#include<ShapeRenderer.h>
#include<TextRenderer.h>
ListBox::ListBox()
{
}
ListBox::ListBox(int _x,int _y, int _width, int _height, int itemC)
{
	x=_x;
	y=_y;
	width=_width;
	height=_height;
	itemCount=itemC;
	if(itemCount != 0)
		items = (char**)malloc(itemCount*sizeof(char*));
	inited=false;
	selectedIndex=0;
	lastIndex=0;
	currentItemCount=0;
	visibleStart=-1;
	calculateVisibleItems();
	
}
void ListBox::addItem(const char* item)
{
	items[currentItemCount]=(char*)malloc(strlen(item)*sizeof(char));
	strcpy(items[currentItemCount],item);
	currentItemCount++;
	calculateVisibleItems();
}
void ListBox::render()
{
if(visibleStart >=0){
  int gap=Text.fontHeight(2);
  Shape.fillRect(x,y,width,height+2,0x31A6);

  for(int i=visibleStart;i<visibleEnd;++i)
  {
	Text.setTextColor(TFT_WHITE);
    Text.drawString(String(i+1)+". "+items[i],x+10,y+(i-visibleStart)*gap,2);
  }
  inited=true;
}
}
void ListBox::update()
{
if(visibleStart >=0 && currentItemCount != 0){
	if(selectedIndex < visibleStart || selectedIndex > visibleEnd-1)
	{
		calculateVisibleItems();
		render();
	}
	int gap=Text.fontHeight(2);
	int lastY=lastIndex-visibleStart;
	if(lastY>=0){
	Shape.fillRect(x+1,y+lastY*gap,width-2,gap,0x31A6);
    Text.setTextColor(TFT_WHITE);
    Text.drawString(String(lastIndex+1)+". "+items[lastIndex],x+10,y+lastY*gap,2);
	}
    Shape.fillRect(x+1,y+(selectedIndex-visibleStart)*gap,width-2,gap,0x0397);
    Text.setTextColor(TFT_BLACK);
    Text.drawString(String(selectedIndex+1)+". "+items[selectedIndex],x+10,y+(selectedIndex-visibleStart)*gap,2);
}
}


void ListBox::calculateVisibleItems()
{
	int gap=Text.fontHeight(2);
	int maxCount=(int)(height/gap);
	if(maxCount > currentItemCount)
		visibleEnd=currentItemCount;
	if(selectedIndex >= visibleEnd-1)
	{
		visibleEnd=selectedIndex+1;
		visibleStart=visibleEnd-maxCount;
	}
	if(selectedIndex < visibleStart)
	{
		visibleStart=selectedIndex;
		visibleEnd=visibleStart+maxCount;
	}
	if(visibleStart <= 0)
	{
		visibleStart=0;
		int end=visibleStart+maxCount;
		visibleEnd=end > currentItemCount ? currentItemCount:end;
		
	}
	else
	{
		int end=visibleStart+maxCount;
		visibleEnd=end > currentItemCount ? currentItemCount:end;
	}
	if(visibleEnd > currentItemCount)
	{
		visibleEnd=currentItemCount;
		int start= visibleEnd - maxCount;
		visibleStart=(start < 0) ? 0:start;
	}
}
