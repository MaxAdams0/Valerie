#ifndef __DATAMINE_H__
#define __DATAMINE_H__

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <rand.h>

#include <gb/gb.h>

#include "low/types.h"

#define DM_PUZZLE_W 5
#define DM_PUZZLE_H 5

extern uint16_t dm_curs_idx;
extern Node dm_node_hexs[];
extern Text dm_puzzle_text[DM_PUZZLE_W * DM_PUZZLE_H];
extern uint8_t dm_ice_num;
extern bool dm_enabled;
extern const Text DM_TITLE;
extern Text dm_ice;
extern uint8_t dm_tilemap[];

void dmInput(void);
void dmAddText(Text str);
void dmPopPuzzle(void);
void dmUpdateIce(void);

#endif // !__DATAMINE_H__