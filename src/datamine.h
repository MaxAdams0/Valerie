#ifndef __DATAMINE_H__
#define __DATAMINE_H__

#include <stdint.h>
#include "types.h"
#include "gb.h"
#include "scr_text.h"

#define DM_PUZZLE_W 10
#define DM_PUZZLE_H 10

uint8_t dm_curs_idx = 0;
uint8_t dm_ice_perc = 99;

const st_str dm_txt_datamine = { .text="DATAMINE", .pos={ 1, 1 }};
const st_str dm_txt_ice = { .text="99%", .pos={ 16, 1 }};

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

void dm_input(void) {
	gb_jp_input = joypad();
	if (gb_jp_input & J_UP) { // cursor up 1 if not on top row
		dm_curs_idx -= (dm_curs_idx > GB_SCR_H) ? GB_SCR_H : 0;
	}
	if (gb_jp_input & J_DOWN) { // cursor down 1 if not on bottom row
		dm_curs_idx += (dm_curs_idx < GB_SCR_H * (GB_SCR_W - 1)) ? GB_SCR_H : 0;
	}
	if (gb_jp_input & J_LEFT) { // cursor left 1 if not on first column
		dm_curs_idx -= (dm_curs_idx % GB_SCR_W == 1) ? 1 : 0;
	}
	if (gb_jp_input & J_RIGHT) { // cursor right 1 if not on last column
		dm_curs_idx += (dm_curs_idx % GB_SCR_W == 0) ? 1 : 0;
	}
}

void dm_add_text(st_str str) {
	for (uint8_t i = 0; i < strlen(str.text); i++) {
		uint8_t map_index = str.pos.y * GB_SCR_W + (str.pos.x + i);
		dm_tilemap[map_index] = str.text[i];
	}
}

#endif // !__DATAMINE_H__