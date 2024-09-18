#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <gb/gb.h>
#include <gb/cgb.h> // color
#include <gb/metasprites.h>

#include "gb.h"
#include "types.h"
#include "datamine.h"
#include "scr_text.h"

// text tileset
#include "../res/text_set.h"
const UWORD text_pal[] = { // temp
	RGB8(0, 7, 18), RGB8(250, 211, 17), RGB_BLACK, RGB_BLACK
};

void main(void) {	
	cpu_fast();
	
	set_bkg_palette(0, 1, text_pal);
	set_bkg_data(0, text_set_TILE_COUNT, text_set_tiles);
	dm_add_text(st_text2hex(dm_txt_datamine));
	dm_add_text(st_text2hex(dm_txt_ice));
	set_bkg_tiles(0, 0, 20, 18, (const uint8_t *)dm_tilemap);
	
	DISPLAY_ON;
	SHOW_SPRITES;
	
	// main loop
	while(1) {	
		wait_vbl_done();
		gb_frames++;
	}
}