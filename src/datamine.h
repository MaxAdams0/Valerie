#ifndef __DATAMINE_H__
#define __DATAMINE_H__

#include <stdint.h>
#include <stdbool.h>

#include "low/types.h"
#include "low/graphics.h"
#include "low/input.h"
// ================================================================================================
#define DM_PUZZLE_W 10
#define DM_PUZZLE_H 10
// ================================================================================================
uint16_t dm_curs_idx = 0; // uint8_t only -> 255, need >360
uint8_t dm_ice_num = 99;
bool dm_enabled = false;

const g_text dm_txt_datamine = { .text="DATAMINE", .pos={ 1, 1 }};
g_text dm_txt_ice = { .text="99%", .pos={ 16, 1 }};

uint8_t dm_tilemap[] = {
	0x2C,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2D,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2A,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,0x2A,
	0x2F,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2B,0x2E
};
// ================================================================================================
void dm_input(void);
void dm_add_text(g_text str);
void dm_update_ice_num(uint8_t newval);
// ================================================================================================
void dm_input(void) {
	if (inp_if_press(inp_current,inp_last,J_UP)) { // cursor up 1 if not on top row
		dm_curs_idx -= (dm_curs_idx > G_HEIGHT) ? G_HEIGHT : 0;
	}
	if (inp_if_press(inp_current,inp_last,J_DOWN)) { // cursor down 1 if not on bottom row
		dm_curs_idx += (dm_curs_idx < G_HEIGHT * (G_WIDTH - 1)) ? G_HEIGHT : 0;
	}
	if (inp_if_press(inp_current,inp_last,J_LEFT)) { // cursor left 1 if not on first column
		dm_curs_idx -= (dm_curs_idx % G_WIDTH == 1) ? 1 : 0;
	}
	if (inp_if_press(inp_current,inp_last,J_RIGHT)) { // cursor right 1 if not on last column
		dm_curs_idx += (dm_curs_idx % G_WIDTH == 0) ? 1 : 0;
	}
	
	if (inp_if_press(inp_current,inp_last,J_START)) {
		dm_enabled = true;
	}
}

void dm_add_text(g_text text) {
	for (uint8_t i = 0; i < strlen(text.text); i++) {
		uint8_t map_index = text.pos.y * G_WIDTH + (text.pos.x + i);
		dm_tilemap[map_index] = text.text[i];
	}
}

void dm_update_ice_num(uint8_t newval) {
	int tens = newval / 10;
    int ones = newval % 10;

    dm_txt_ice.text[0] = '0' + tens;
    dm_txt_ice.text[1] = '0' + ones;
    dm_txt_ice.text[2] = '%';
    dm_txt_ice.text[3] = '\0';
}

void dm_update_ice(void) {
	if (!dm_enabled) return;
	
	if (gb_frames % 8 == 0) {
		dm_ice_num--;
		dm_update_ice_num(dm_ice_num);
	}
	
	dm_add_text(g_text_text2hex(dm_txt_ice));
}

#endif // !__DATAMINE_H__