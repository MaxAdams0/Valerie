#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdint.h>

#define inpKeyPressed(cur, last, button) (cur & button && !(last & button))
#define inpKeyHeld(var, button) (var & button)

extern uint8_t inp_current;
extern uint8_t inp_last;

#endif // !__INPUT_H__

