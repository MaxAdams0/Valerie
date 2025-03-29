#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

typedef struct {
	int8_t x, y;
} Vec2;

typedef struct {
	char text[40]; // 40 = 2 full rows of tiles
	Vec2 pos;
} Text;

typedef struct {
	char text[3];
} Node;

#endif // !__TYPES_H__