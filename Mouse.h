#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "Vector2.h"
 
extern "C"{
#include <ncursesw/curses.h>
}

//#DECLARATION
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS MOUSE

class Mouse {

public:

	static MEVENT event;

	enum Button { Left, Right, Middle };
	enum Wheel { ScrollUp, ScrollDown };

	static Vector2i get_position();

	static bool is_pressed(Button button);
	static bool is_released(Button button);
	static bool is_scrolling(Wheel wheel);
};

//#DECLARATION_END

#endif

