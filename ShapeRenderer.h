#ifndef SHAPERENDERER_H
#define SHAPERENDERER_H
#include<Arduino.h>
class ShapeRenderer
{
public:
	ShapeRenderer();
	void drawPixel(int32_t x, int32_t y, uint32_t color);
	void fillScreen(uint32_t color);
	
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
	void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
	
	void drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color);
	void drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color);
};
extern ShapeRenderer Shape;
#endif