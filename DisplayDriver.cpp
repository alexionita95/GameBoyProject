#include <DisplayDriver.h>


void DisplayDriver::spi_begin(void){
#if defined (SPI_HAS_TRANSACTION) && defined (SUPPORT_TRANSACTIONS) && !defined(ESP32_PARALLEL)
  if (locked) {locked = false; spi.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE)); CS_L;}
#else
  CS_L;
#endif
#ifdef ESP8266
  SPI1U = SPI1U_WRITE;
#endif
}

void DisplayDriver::spi_end(void){
#if defined (SPI_HAS_TRANSACTION) && defined (SUPPORT_TRANSACTIONS) && !defined(ESP32_PARALLEL)
  if(!inTransaction) {if (!locked) {locked = true; CS_H; spi.endTransaction();}}
  #ifdef ESP8266
    SPI1U = SPI1U_READ;
  #endif
#else
  if(!inTransaction) CS_H;
#endif
}

void DisplayDriver::writecommand(uint8_t c)
{
  spi_begin(); // CS_L;

  DC_C;

  tft_Write_8(c);

  DC_D;

  spi_end();  // CS_H;
}
void DisplayDriver::writedata(uint8_t d)
{
  spi_begin(); // CS_L;

  DC_D;        // Play safe, but should already be in data mode

  tft_Write_8(d);

  CS_L;        // Allow more hold time for low VDI rail

  spi_end();   // CS_H;
}


void DisplayDriver::setWindow(int32_t xs, int32_t ys, int32_t xe, int32_t ye)
{
  //spi_begin(); // Must be called before setWimdow

#ifdef CGRAM_OFFSET
  xs+=colstart;
  xe+=colstart;
  ys+=rowstart;
  ye+=rowstart;
#endif

  // Column addr set
  DC_C;

  SPI1U1 = (CMD_BITS << SPILMOSI) | (CMD_BITS << SPILMISO);

  SPI1W0 = TFT_CASET;
  SPI1CMD |= SPIBUSY;

  addr_col = 0xFFFF;
  addr_row = 0xFFFF;
  
  while(SPI1CMD & SPIBUSY) {}

  DC_D;

  SPI1U1 = (31 << SPILMOSI) | (31 << SPILMISO);
  // Load the two coords as a 32 bit value and shift in one go
  SPI1W0 = (xs >> 8) | (uint16_t)(xs << 8) | ((uint8_t)(xe >> 8)<<16 | (xe << 24));
  SPI1CMD |= SPIBUSY;
  while(SPI1CMD & SPIBUSY) {}

  // Row addr set
  DC_C;

  SPI1U1 = (CMD_BITS << SPILMOSI) | (CMD_BITS << SPILMISO);

  SPI1W0 = TFT_PASET;
  SPI1CMD |= SPIBUSY;
  while(SPI1CMD & SPIBUSY) {}

  DC_D;

  SPI1U1 = (31 << SPILMOSI) | (31 << SPILMISO);
  // Load the two coords as a 32 bit value and shift in one go
  SPI1W0 = (ys >> 8) | (uint16_t)(ys << 8) | ((uint8_t)(ye >> 8)<<16 | (ye << 24));
  SPI1CMD |= SPIBUSY;
  while(SPI1CMD & SPIBUSY) {}

  // write to RAM
  DC_C;

  SPI1U1 = (CMD_BITS << SPILMOSI) | (CMD_BITS << SPILMISO);
  SPI1W0 = TFT_RAMWR;
  SPI1CMD |= SPIBUSY;
  while(SPI1CMD & SPIBUSY) {}

  DC_D;

  SPI1U1 = (15 << SPILMOSI) | (15 << SPILMISO);
  //spi_end();
}

void DisplayDriver::writeBlock(uint16_t color, uint32_t repeat)
{
  uint16_t color16 = (color >> 8) | (color << 8);
  uint32_t color32 = color16 | color16 << 16;

  SPI1W0 = color32;
  SPI1W1 = color32;
  SPI1W2 = color32;
  SPI1W3 = color32;
  if (repeat > 8)
  {
    SPI1W4 = color32;
    SPI1W5 = color32;
    SPI1W6 = color32;
    SPI1W7 = color32;
  }
  if (repeat > 16)
  {
    SPI1W8 = color32;
    SPI1W9 = color32;
    SPI1W10 = color32;
    SPI1W11 = color32;
  }
  if (repeat > 24)
  {
    SPI1W12 = color32;
    SPI1W13 = color32;
    SPI1W14 = color32;
    SPI1W15 = color32;
  }
  if (repeat > 31)
  {
    SPI1U1 = (511 << SPILMOSI);
    while(repeat>31)
    {
#if defined SPI_FREQUENCY && (SPI_FREQUENCY == 80000000)
      if(SPI1CMD & SPIBUSY) // added to sync with flag change
#endif
      while(SPI1CMD & SPIBUSY) {}
      SPI1CMD |= SPIBUSY;
      repeat -= 32;
    }
    while(SPI1CMD & SPIBUSY) {}
  }

  if (repeat)
  {
    repeat = (repeat << 4) - 1;
    SPI1U1 = (repeat << SPILMOSI);
    SPI1CMD |= SPIBUSY;
    while(SPI1CMD & SPIBUSY) {}
  }

}


DisplayDriver::DisplayDriver(int16_t w, int16_t h)
{

#ifdef TFT_CS
  digitalWrite(TFT_CS, HIGH); // Chip select high (inactive)
  pinMode(TFT_CS, OUTPUT);
#endif

#ifdef TFT_DC
  digitalWrite(TFT_DC, HIGH); // Data/Command high = data mode
  pinMode(TFT_DC, OUTPUT);
#endif

#ifdef TFT_RST
  if (TFT_RST >= 0) {
    digitalWrite(TFT_RST, HIGH); // Set high, do not share pin with another SPI device
    pinMode(TFT_RST, OUTPUT);
  }
#endif

_init_width  = _width  = w; // Set by specific xxxxx_Defines.h file or by users sketch
_init_height = _height = h; // Set by specific xxxxx_Defines.h file or by users sketch
rotation  = 0;
  
locked = true;        // ESP32 transaction mutex lock flags
inTransaction = false;

addr_row = 0xFFFF;
addr_col = 0xFFFF;
booted   = true;

}
void DisplayDriver::init()
{
if(booted)
{	
#ifdef TFT_CS
	cspinmask = (uint32_t) digitalPinToBitMask(TFT_CS);
#endif

#ifdef TFT_DC
	dcpinmask = (uint32_t) digitalPinToBitMask(TFT_DC);
#endif
  

SPI.begin(); // This will set HMISO to input
  
inTransaction = false;
locked = true;

SPI.setBitOrder(MSBFIRST);
SPI.setDataMode(TFT_SPI_MODE);
SPI.setFrequency(SPI_FREQUENCY);

#ifdef TFT_DC
	digitalWrite(TFT_DC, HIGH); // Data/Command high = data mode
    pinMode(TFT_DC, OUTPUT);
#endif
	booted = false;
    spi_end();
}
	spi_begin();
	
#ifdef TFT_RST
  if (TFT_RST >= 0) {
    digitalWrite(TFT_RST, HIGH);
    delay(5);
    digitalWrite(TFT_RST, LOW);
    delay(20);
    digitalWrite(TFT_RST, HIGH);
  }
  else writecommand(TFT_SWRST); // Software reset
#else
  writecommand(TFT_SWRST); // Software reset
#endif

	spi_end();

  delay(150); // Wait for reset to complete

  spi_begin();
  
  #if   defined (ILI9341_DRIVER)
    #include "hardware/ILI9341_Init.h"
  #endif

#ifdef TFT_INVERSION_ON
  writecommand(TFT_INVON);
#endif

#ifdef TFT_INVERSION_OFF
  writecommand(TFT_INVOFF);
#endif

  spi_end();

  setRotation(rotation);


}

void DisplayDriver::setRotation(uint8_t m)
{

  spi_begin();

#if   defined (ILI9341_DRIVER)
    #include "hardware/ILI9341_Rotation.h"
#endif

  delayMicroseconds(10);

  spi_end();

  addr_row = 0xFFFF;
  addr_col = 0xFFFF;
}




DisplayDriver Display;