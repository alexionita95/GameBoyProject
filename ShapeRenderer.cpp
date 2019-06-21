#include<ShapeRenderer.h>

#include<DisplayDriver.h>

ShapeRenderer::ShapeRenderer()
{
}

void ShapeRenderer::drawPixel(int32_t x, int32_t y, uint32_t color)
{
  // Range checking
  if ((x < 0) || (y < 0) ||(x >= Display.width()) || (y >= Display.height())) return;

  Display.spi_begin();

  // No need to send x if it has not changed (speeds things up)
  if (Display.addr_col != x) {

    DC_C;

    SPI1U1 = (CMD_BITS << SPILMOSI) | (CMD_BITS << SPILMISO);
    SPI1W0 = TFT_CASET<<(CMD_BITS + 1 - 8);
    SPI1CMD |= SPIBUSY;
    while(SPI1CMD & SPIBUSY) {}

    DC_D;

    SPI1U1 = (31 << SPILMOSI) | (31 << SPILMISO);
    // Load the two coords as a 32 bit value and shift in one go
    uint32_t xswap = (x >> 8) | (uint16_t)(x << 8);
    SPI1W0 = xswap | (xswap << 16);
    SPI1CMD |= SPIBUSY;
    while(SPI1CMD & SPIBUSY) {}
    Display.addr_col = x;
  }

  // No need to send y if it has not changed (speeds things up)
  if (Display.addr_row != y) {

    DC_C;

    SPI1U1 = (CMD_BITS << SPILMOSI) | (CMD_BITS << SPILMISO);

    SPI1W0 = TFT_PASET<<(CMD_BITS + 1 - 8);
    SPI1CMD |= SPIBUSY;
    while(SPI1CMD & SPIBUSY) {}

    DC_D;

    SPI1U1 = (31 << SPILMOSI) | (31 << SPILMISO);
    // Load the two coords as a 32 bit value and shift in one go
    uint32_t yswap = (y >> 8) | (uint16_t)(y << 8);
    SPI1W0 = yswap | (yswap << 16);
    SPI1CMD |= SPIBUSY;
    while(SPI1CMD & SPIBUSY) {}

    Display.addr_row = y;
  }

  DC_C;

  SPI1U1 = (CMD_BITS << SPILMOSI) | (CMD_BITS << SPILMISO);

  SPI1W0 = TFT_RAMWR<<(CMD_BITS + 1 - 8);
  SPI1CMD |= SPIBUSY;
  while(SPI1CMD & SPIBUSY) {}

  DC_D;

  SPI1U1 = (15 << SPILMOSI) | (15 << SPILMISO);

  SPI1W0 = (color >> 8) | (color << 8);
  SPI1CMD |= SPIBUSY;
  while(SPI1CMD & SPIBUSY) {}

  Display.spi_end();
}


void ShapeRenderer::fillScreen(uint32_t color)
{
  fillRect(0, 0,Display.width(), Display.height(), color);
}

void ShapeRenderer::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color)
{
  // Clipping
  if ((x >= Display.width()) || (y >= Display.height())) return;
  
  if (x < 0) { w += x; x = 0; }
  if (y < 0) { h += y; y = 0; }

  if ((x + w) > Display.width())  w = Display.width()  - x;
  if ((y + h) > Display.height()) h = Display.height() - y;

  if ((w < 1) || (h < 1)) return;

  Display.spi_begin();

  Display.setWindow(x, y, x + w - 1, y + h - 1);

  Display.writeBlock(color, w * h);
  
  Display.spi_end();
}

void ShapeRenderer::drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
{
  Display.spi_begin();

  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y + h - 1, w, color);
  // Avoid drawing corner pixels twice
  drawFastVLine(x, y+1, h-2, color);
  drawFastVLine(x + w - 1, y+1, h-2, color);

  Display.spi_end();
}
void ShapeRenderer::drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)
{
  // Clipping
  if ((y < 0) || (x >= Display.width()) || (y >= Display.height())) return;

  if (x < 0) { w += x; x = 0; }

  if ((x + w) > Display.width())  w = Display.width()  - x;

  if (w < 1) return;

  Display.spi_begin();

  Display.setWindow(x, y, x + w - 1, y);

  Display.writeBlock(color, w);
  
  Display.spi_end();
}

void ShapeRenderer::drawFastVLine(int32_t x, int32_t y, int32_t h, uint32_t color)
{
  // Clipping
  if ((x < 0) || (x >= Display.width()) || (y >= Display.height())) return;

  if (y < 0) { h += y; y = 0; }

  if ((y + h) > Display.height()) h = Display.height() - y;

  if (h < 1) return;

  Display.spi_begin();

  Display.setWindow(x, y, x, y + h - 1);

  Display.writeBlock(color, h);
  
  Display.spi_end();
}


ShapeRenderer Shape;