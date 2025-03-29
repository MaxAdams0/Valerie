#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <rand.h>
#include "types.h"

#define G_WIDTH 20
#define G_HEIGHT 18

extern uint8_t g_frames;

Text textToHex(Text chars);
uint8_t charToHex(const char ch);// I hate this but also I'm lazy so...
void syncFramecount(void);
void genSeed(void);

#endif // !__GRAPHICS_H__

