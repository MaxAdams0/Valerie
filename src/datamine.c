#include "datamine.h"

#include "low/graphics.h"
#include "low/input.h"

uint16_t dm_curs_idx = 0; // uint8_t only -> 255, need >360
Node dm_node_hexs[] = { {"BD"},{"E9"},{"55"},{"1C"},{"7A"} };
Text dm_puzzle_text[DM_PUZZLE_W * DM_PUZZLE_H];
uint8_t dm_ice_num = 99;
bool dm_enabled = false;
const Text DM_TITLE = { .text="DATAMINE", .pos={ 1, 1 }};
Text dm_ice = { .text="99%", .pos={ 16, 1 }};
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
	if (inpKeyPressed(inp_current, inp_last, J_UP)) { // cursor up 1 if not on top row
		dm_curs_idx -= (dm_curs_idx > G_HEIGHT) ? G_HEIGHT : 0;
	}
	if (inpKeyPressed(inp_current, inp_last, J_DOWN)) { // cursor down 1 if not on bottom row
		dm_curs_idx += (dm_curs_idx < G_HEIGHT * (G_WIDTH - 1)) ? G_HEIGHT : 0;
	}
	if (inpKeyPressed(inp_current, inp_last, J_LEFT)) { // cursor left 1 if not on first column
		dm_curs_idx -= (dm_curs_idx % G_WIDTH == 1) ? 1 : 0;
	}
	if (inpKeyPressed(inp_current, inp_last, J_RIGHT)) { // cursor right 1 if not on last column
		dm_curs_idx += (dm_curs_idx % G_WIDTH == 0) ? 1 : 0;
	}
}

void dmAddText(Text text) { 
	for (uint8_t i = 0; i < strlen(text.text); i++) {
		uint16_t map_index = (text.pos.y * G_WIDTH) + (text.pos.x + i);
		dm_tilemap[map_index] = text.text[i];
	}
}

void dmPopPuzzle(void) {
	Vec2 node_pos = {3,3};
	
	for (uint8_t row = 0; row < DM_PUZZLE_H; row++) {
		for (uint8_t col = 0; col < DM_PUZZLE_W; col++) {
			Text node_text;
			strcpy(node_text.text, dm_node_hexs[rand() % 5].text);
			node_text.pos.x = node_pos.x;
			node_text.pos.y = node_pos.y;
			
			dmAddText(textToHex(node_text));
			node_pos.x += 3;
		}
		node_pos.x = 3;
		node_pos.y += 2;
	}
}

void dmUpdateIce(void) {
	if (!dm_enabled) return;
	
	if (g_frames % 8 == 0) {
		dm_ice_num = (dm_ice_num==0) ? 0 : dm_ice_num-1; // cap bottom to 0
		
		// update text
		int tens = dm_ice_num / 10;
		int ones = dm_ice_num % 10;

		dm_ice.text[0] = '0' + tens;
		dm_ice.text[1] = '0' + ones;
		dm_ice.text[2] = '%';
		dm_ice.text[3] = '\0';
	}
}
