#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h> // snprintf

#include <gb/gb.h>
#include <gb/cgb.h> // color
#include <gb/metasprites.h>

#include "all.h"

// text tileset
#include "../res/text_set.h"
const UWORD text_pal[] = { // temp
	RGB8(0, 7, 18), RGB8(250, 211, 17), RGB_BLACK, RGB_BLACK
};

void main(void) {	
	cpu_fast();
	snd_init();
	
	set_bkg_palette(0, 1, text_pal);
	set_bkg_data(0, text_set_TILE_COUNT, text_set_tiles);
	dm_add_text(g_text_text2hex(dm_txt_datamine));
	
	DISPLAY_ON;
	SHOW_SPRITES;
	
	// Game Loop
	while(1) { 
		inp_current = joypad();
		dm_update_ice();
		
		if (inp_if_press(inp_current, inp_last, J_A)) {
			snd_test_sound();
		}
		
		set_bkg_tiles(0, 0, 20, 18, (const uint8_t *)dm_tilemap);
		
		g_sync_framecount();
		inp_last = inp_current;
		wait_vbl_done();
	}
}