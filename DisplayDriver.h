#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include<hardware/HardwareSetupConfig.h>

#ifndef TAB_COLOUR
  #define TAB_COLOUR 0
#endif
// If the frequency is not defined, set a default
#ifndef SPI_FREQUENCY
  #define SPI_FREQUENCY  20000000
#endif

// If the frequency is not defined, set a default
#ifndef SPI_READ_FREQUENCY
  #define SPI_READ_FREQUENCY SPI_FREQUENCY
#endif

#define TFT_SPI_MODE SPI_MODE0



#include<Arduino.h>
#include <pgmspace.h>
#include <SPI.h>

#ifndef TFT_DC
  #define DC_C // No macro allocated so it generates no code
  #define DC_D // No macro allocated so it generates no code
#else
  #if defined (ESP8266) && (TFT_DC == 16)
    #define DC_C digitalWrite(TFT_DC, LOW)
    #define DC_D digitalWrite(TFT_DC, HIGH)
  #else
    #define DC_C GPOC=Display.dcpinmask
    #define DC_D GPOS=Display.dcpinmask
  #endif
#endif

#ifndef TFT_CS
  #define CS_L // No macro allocated so it generates no code
  #define CS_H // No macro allocated so it generates no code
#else
  #if defined (ESP8266) && (TFT_CS == 16)
    #define CS_L digitalWrite(TFT_CS, LOW)
    #define CS_H digitalWrite(TFT_CS, HIGH)
  #else
    #define CS_L GPOC=Display.cspinmask
    #define CS_H GPOS=Display.cspinmask
  #endif
#endif

#if defined (TFT_SPI_OVERLAP)
  #undef TFT_CS
  #define SPI1U_WRITE (SPIUMOSI | SPIUSSE | SPIUCSSETUP | SPIUCSHOLD)
  #define SPI1U_READ  (SPIUMOSI | SPIUSSE | SPIUCSSETUP | SPIUCSHOLD | SPIUDUPLEX)
#else
  #ifdef ESP8266
    #define SPI1U_WRITE (SPIUMOSI | SPIUSSE)
    #define SPI1U_READ  (SPIUMOSI | SPIUSSE | SPIUDUPLEX)
  #endif
#endif

#ifdef ESP8266
  // Concatenate two 16 bit values for the SPI 32 bit register write
  #define SPI_32(H,L) ( (H)<<16 | (L) )
  #define COL_32(H,L) ( (H)<<16 | (L) )
#endif

#if defined ESP8266
  #define tft_Write_8(C)   SPI.write(C)
  #define tft_Write_16(C)  SPI.write16(C)
  #define tft_Write_32(C)  SPI.write32(C)
#endif

#ifndef TFT_MISO
  #define TFT_MISO -1
#endif
  
#define CMD_BITS 8-1
  
#include<Colors.h>
  
class DisplayDriver {

public:
DisplayDriver(int16_t w = TFT_WIDTH, int16_t h = TFT_HEIGHT);
void init();
void setRotation(uint8_t m);


  void spi_begin();
  void spi_end();
  void writecommand(uint8_t c),
       writedata(uint8_t d);
  void setWindow(int32_t xs, int32_t ys, int32_t xe, int32_t ye);
  void writeBlock(uint16_t color, uint32_t repeat);

int16_t width(void)
{
  return _width;
}

int16_t height(void)
{
  return _height;
}

int32_t  addr_row, addr_col;
	uint32_t cspinmask, dcpinmask;
private:


protected:
  int32_t  _init_width, _init_height; // Display w/h as input, used by setRotation()
  int32_t  _width, _height;           // Display w/h as modified by current rotation
  
  bool     locked, inTransaction; // Transaction and mutex lock flags for ESP32
  uint8_t rotation;
  
  bool booted;
};
extern DisplayDriver Display;
#endif