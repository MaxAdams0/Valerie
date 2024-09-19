#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "types.h"
// ================================================================================================
#define G_WIDTH 20
#define G_HEIGHT 18
// ================================================================================================
uint8_t gb_frames = 0;
// ================================================================================================
g_text g_str2hex(g_text chars);
void g_sync_framecount(void);
uint8_t g_text_char2hex(const char ch);
// ================================================================================================
g_text g_text_text2hex(g_text chars) {
	g_text hex = { .text="", .pos={chars.pos.x, chars.pos.y} };
	
	for (uint8_t i = 0; i < strlen(chars.text); i++) {
		hex.text[i] = g_text_char2hex(chars.text[i]);
	}
	
	return hex;
}

void g_sync_framecount(void) {
	switch (gb_frames) {
		case 60: // max = 59
			gb_frames = 0; // min = 0
			break;
		default:
			gb_frames++;
			break;
	}
}

uint8_t g_text_char2hex(const char ch) {
	switch (ch) {
		case ' ': return 0x00;
		case '0': return 0x01;
		case '1': return 0x02;
		case '2': return 0x03;
		case '3': return 0x04;
		case '4': return 0x05;
		case '5': return 0x06;
		case '6': return 0x07;
		case '7': return 0x08;
		case '8': return 0x09;
		case '9': return 0x0A;
		case 'A': return 0x0B;
		case 'B': return 0x0C;
		case 'C': return 0x0D;
		case 'D': return 0x0E;
		case 'E': return 0x0F;
		case 'F': return 0x10;
		case 'G': return 0x11;
		case 'H': return 0x12;
		case 'I': return 0x13;
		case 'J': return 0x14;
		case 'K': return 0x15;
		case 'L': return 0x16;
		case 'M': return 0x17;
		case 'N': return 0x18;
		case 'O': return 0x19;
		case 'P': return 0x1A;
		case 'Q': return 0x1B;
		case 'R': return 0x1C;
		case 'S': return 0x1D;
		case 'T': return 0x1E;
		case 'U': return 0x1F;
		case 'V': return 0x20;
		case 'W': return 0x21;
		case 'X': return 0x22;
		case 'Y': return 0x23;
		case 'Z': return 0x24;
		case '?': return 0x25;
		case '!': return 0x26;
		case '.': return 0x27;
		case '/': return 0x28;
		case '%': return 0x29;
		default: return 0x00;
	}
}

#endif // !__GRAPHICS_H__

