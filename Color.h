#ifndef _COLOR_H_
#define _COLOR_H_

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED // pour utilisé les fonction wide character et cchar_t
#endif

extern "C"{
#include <ncursesw/curses.h>
}

//#DECLARATION
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS COLORPAIR

enum ColorUnit{
	DEFAULT = -1, //La couleur par default du terminal a l'initialisation de ncurses
	
	BLACK = COLOR_BLACK,
	WHITE = COLOR_WHITE,

	RED = COLOR_RED,
	GREEN = COLOR_GREEN,
	BLUE = COLOR_BLUE,
		
	CYAN = COLOR_CYAN,
	MAGENTA = COLOR_MAGENTA,
	YELLOW = COLOR_YELLOW
};

class ColorPair
{
public:
	ColorUnit front;
	ColorUnit back;

	ColorPair();
	ColorPair(chtype);
	ColorPair(ColorUnit front_back);
	ColorPair(ColorUnit front, ColorUnit back);

/* Renvoie le numéro correspondant à la paire de couleur composée de front et back */
	int pair_num() const;

/* Convertie en chtype la paire de couleur composée de front et back */
	operator chtype() const;

	static const ColorPair Default;
	static const ColorPair WhiteBlack;
	static const ColorPair WhiteRed;
	static const ColorPair WhiteGreen;
	static const ColorPair WhiteBlue;
	static const ColorPair WhiteMagenta;
	static const ColorPair WhiteYellow;
	static const ColorPair WhiteCyan;

	static const ColorPair White;
	static const ColorPair Black;
	static const ColorPair Red;
	static const ColorPair Green;
	static const ColorPair Blue;
	static const ColorPair Magenta;
	static const ColorPair Yellow;
	static const ColorPair Cyan;
};

////////////////////////////////////////////////// FONCTIONS DECLARATION

/* Initialise toutes les pairs de couleurs possible en fonction du terminal */
void init_color_pairs();

/* Change les valeurs de rouge vert et bleu associée à une couleur */
void color_rgb(ColorUnit color, short r, short g, short b);

//#DECLARATION_END

#endif
