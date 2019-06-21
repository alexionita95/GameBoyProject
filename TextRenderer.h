#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include<hardware/HardwareSetupConfig.h>
#include<Arduino.h>

#ifdef LOAD_GLCD
  #include <Fonts/glcdfont.c>
#endif
#ifdef LOAD_FONT2
  #include <Fonts/Font16.h>
#endif

#ifdef LOAD_FONT4
  #include <Fonts/Font32rle.h>
  #define LOAD_RLE
#endif

#ifdef LOAD_FONT6
  #include <Fonts/Font64rle.h>
  #ifndef LOAD_RLE
    #define LOAD_RLE
  #endif
#endif

#ifdef LOAD_FONT7
  #include <Fonts/Font7srle.h>
  #ifndef LOAD_RLE
    #define LOAD_RLE
  #endif
#endif

#ifdef LOAD_FONT8
  #include <Fonts/Font72rle.h>
  #ifndef LOAD_RLE
    #define LOAD_RLE
  #endif
#elif defined LOAD_FONT8N
  #define LOAD_FONT8
  #include <Fonts/Font72x53rle.h>
  #ifndef LOAD_RLE
    #define LOAD_RLE
  #endif
#endif

#include <pgmspace.h>

#define TL_DATUM 0 // Top left (default)
#define TC_DATUM 1 // Top centre
#define TR_DATUM 2 // Top right
#define ML_DATUM 3 // Middle left
#define CL_DATUM 3 // Centre left, same as above
#define MC_DATUM 4 // Middle centre
#define CC_DATUM 4 // Centre centre, same as above
#define MR_DATUM 5 // Middle right
#define CR_DATUM 5 // Centre right, same as above
#define BL_DATUM 6 // Bottom left
#define BC_DATUM 7 // Bottom centre
#define BR_DATUM 8 // Bottom right
#define L_BASELINE  9 // Left character baseline (Line the 'A' character would sit on)
#define C_BASELINE 10 // Centre character baseline
#define R_BASELINE 11 // Right character baseline

const  uint8_t widtbl_null[1] = {0};
PROGMEM const uint8_t chr_null[1] = {0};
PROGMEM const uint8_t* const chrtbl_null[1] = {chr_null};

typedef struct {
    const uint8_t *chartbl;
    const uint8_t *widthtbl;
    uint8_t height;
    uint8_t baseline;
    } fontinfo;

// Now fill the structure
const PROGMEM fontinfo fontdata [] = {
  #ifdef LOAD_GLCD
   { (const uint8_t *)font, widtbl_null, 0, 0 },
  #else
   { (const uint8_t *)chrtbl_null, widtbl_null, 0, 0 },
  #endif
   // GLCD font (Font 1) does not have all parameters
   { (const uint8_t *)chrtbl_null, widtbl_null, 8, 7 },

  #ifdef LOAD_FONT2
   { (const uint8_t *)chrtbl_f16, widtbl_f16, chr_hgt_f16, baseline_f16},
  #else
   { (const uint8_t *)chrtbl_null, widtbl_null, 0, 0 },
  #endif

   // Font 3 current unused
   { (const uint8_t *)chrtbl_null, widtbl_null, 0, 0 },

  #ifdef LOAD_FONT4
   { (const uint8_t *)chrtbl_f32, widtbl_f32, chr_hgt_f32, baseline_f32},
  #else
   { (const uint8_t *)chrtbl_null, widtbl_null, 0, 0 },
  #endif

   // Font 5 current unused
   { (const uint8_t *)chrtbl_null, widtbl_null, 0, 0 },

  #ifdef LOAD_FONT6
   { (const uint8_t *)chrtbl_f64, widtbl_f64, chr_hgt_f64, baseline_f64},
  #else
   { (const uint8_t *)chrtbl_null, widtbl_null, 0, 0 },
  #endif

  #ifdef LOAD_FONT7
   { (const uint8_t *)chrtbl_f7s, widtbl_f7s, chr_hgt_f7s, baseline_f7s},
  #else
   { (const uint8_t *)chrtbl_null, widtbl_null, 0, 0 },
  #endif

  #ifdef LOAD_FONT8
   { (const uint8_t *)chrtbl_f72, widtbl_f72, chr_hgt_f72, baseline_f72}
  #else
   { (const uint8_t *)chrtbl_null, widtbl_null, 0, 0 }
  #endif
};

class TextRenderer
{
public:
TextRenderer();
  
  
  void setTextSize(uint8_t s);
  void setTextFont(uint8_t f);
  void setTextColor(uint16_t c);
  void setTextColor(uint16_t c, uint16_t b);
  int16_t  drawNumber(long long_num, int32_t poX, int32_t poY, uint8_t font),
           drawNumber(long long_num, int32_t poX, int32_t poY),
           drawFloat(float floatNumber, uint8_t decimal, int32_t poX, int32_t poY, uint8_t font),
           drawFloat(float floatNumber, uint8_t decimal, int32_t poX, int32_t poY),

           // Handle char arrays
           drawString(const char *string, int32_t poX, int32_t poY, uint8_t font),
           drawString(const char *string, int32_t poX, int32_t poY),
           drawCenterString(const char *string, int32_t dX, int32_t poY, uint8_t font), // Deprecated, use setTextDatum() and drawString()
           drawRightString(const char *string, int32_t dX, int32_t poY, uint8_t font),  // Deprecated, use setTextDatum() and drawString()

           // Handle String type
           drawString(const String& string, int32_t poX, int32_t poY, uint8_t font),
           drawString(const String& string, int32_t poX, int32_t poY),
           drawCenterString(const String& string, int32_t dX, int32_t poY, uint8_t font), // Deprecated, use setTextDatum() and drawString()
           drawRightString(const String& string, int32_t dX, int32_t poY, uint8_t font);  // Deprecated, use setTextDatum() and drawString()

  int16_t  textWidth(const char *string, uint8_t font),
           textWidth(const char *string),
           textWidth(const String& string, uint8_t font),
           textWidth(const String& string),
           fontHeight(int16_t font),
           fontHeight(void),
		   drawChar(uint16_t uniCode, int32_t x, int32_t y, uint8_t font),
		   drawChar(uint16_t uniCode, int32_t x, int32_t y);
  void drawChar(int32_t x, int32_t y, uint16_t c, uint32_t color, uint32_t bg, uint8_t size);
  uint16_t decodeUTF8(uint8_t *buf, uint16_t *index, uint16_t remaining);
  uint16_t decodeUTF8(uint8_t c);		   
		   
private:
  int32_t padX;
  uint32_t textcolor, textbgcolor;
  uint8_t  textfont,  // Current selected font
           textsize,  // Current font size multiplier
           textdatum; // Text reference datum
  uint8_t  decoderState = 0;   // UTF8 decoder state
  uint16_t decoderBuffer;      // Unicode code-point buffer
  uint32_t fontsloaded;
  bool isDigits;
	
};
extern TextRenderer Text;
#endif