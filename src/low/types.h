#ifndef __TYPES_H__
#define __TYPES_H__

typedef struct {
	int8_t x, y;
} t_vec2;

typedef struct {
	uint8_t text[40]; // 40 = 2 full rows of tiles
	t_vec2 pos;
} g_text;

#endif // !__TYPES_H__