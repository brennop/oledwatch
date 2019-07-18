/*
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 *
 * @created: 2014-08-12
 * @author: Neven Boyanov
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ----------------------------------------------------------------------------

#include <avr/pgmspace.h>

// ----------------------------------------------------------------------------

#define SMALL_WIDTH 6
#define SMALL_HEIGHT 8

const uint8_t smallfont [] PROGMEM = {
  0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, // 0
  0x42, 0x7F, 0x40, 0x00, 0x00, 0x00, // 1
  0x42, 0x61, 0x51, 0x49, 0x46, 0x00, // 2
  0x22, 0x41, 0x49, 0x49, 0x36, 0x00, // 3
  0x18, 0x14, 0x52, 0x7F, 0x50, 0x00, // 4
  0x27, 0x45, 0x45, 0x45, 0x39, 0x00, // 5
  0x3E, 0x45, 0x45, 0x45, 0x38, 0x00, // 6
  0x01, 0x01, 0x71, 0x09, 0x07, 0x00, // 7
  0x36, 0x49, 0x49, 0x49, 0x36, 0x00, // 8
  0x0E, 0x51, 0x51, 0x51, 0x3E, 0x00, // 9
  0x66, 0x66, 0x00, 0x00, 0x00, 0x00, // :
  0x60, 0xE0, 0x00, 0x00, 0x00, 0x00, // ; aka ,
  0x38, 0x44, 0xC4, 0x44, 0x48, 0x00, // < aka ç
  0x38, 0x44, 0x45, 0x24, 0x7C, 0x00, // = aka á
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, // > aka |
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ? aka ' '
  0x3E, 0x41, 0x5D, 0x55, 0x5E, 0x00, 
  0x38, 0x44, 0x44, 0x24, 0x7C, 0x00, 
  0x7F, 0x44, 0x44, 0x44, 0x38, 0x00, 
  0x38, 0x44, 0x44, 0x44, 0x48, 0x00, 
  0x38, 0x44, 0x44, 0x44, 0x7F, 0x00, 
  0x38, 0x54, 0x54, 0x54, 0x58, 0x00, 
  0x08, 0x7E, 0x09, 0x01, 0x00, 0x00, 
  0x38, 0x44, 0x44, 0x44, 0xFC, 0x00, 
  0x7F, 0x04, 0x04, 0x04, 0x78, 0x00, 
  0x04, 0x7D, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x04, 0xFD, 0x00, 0x00, 0x00, 
  0x7F, 0x10, 0x18, 0x24, 0x40, 0x00, 
  0x01, 0x7F, 0x40, 0x00, 0x00, 0x00, 
  0x7C, 0x04, 0x7C, 0x04, 0x78, 0x00, 
  0x7C, 0x08, 0x04, 0x04, 0x78, 0x00, 
  0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 
  0xFC, 0x44, 0x44, 0x44, 0x38, 0x00, 
  0x38, 0x44, 0x44, 0x44, 0xFC, 0x00, 
  0x7C, 0x08, 0x04, 0x04, 0x08, 0x00, 
  0x48, 0x54, 0x54, 0x54, 0x24, 0x00, 
  0x04, 0x3F, 0x44, 0x44, 0x00, 0x00, 
  0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00, 
  0x0C, 0x30, 0x40, 0x30, 0x0C, 0x00, 
  0x3C, 0x40, 0x38, 0x40, 0x3C, 0x00, 
  0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 
  0x3C, 0x40, 0x40, 0x40, 0xFC, 0x00, 
  0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 
};

// ----------------------------------------------------------------------------