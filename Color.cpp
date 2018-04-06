#include "Color.h"

//#DEFINITION
////////////////////////////////////////////////// CONSTRUCTEURS

ColorPair::ColorPair() : front(DEFAULT), back(DEFAULT) {}

ColorPair::ColorPair(chtype c){

	chtype color = c & A_COLOR;
	short f = 0, b = 0;

	pair_content(PAIR_NUMBER(color), &f, &b);

	front = (ColorUnit)f;
	back = (ColorUnit)b;
}

ColorPair::ColorPair(ColorUnit front_back){
	front = front_back;
	back = front_back;
}

ColorPair::ColorPair(ColorUnit front, ColorUnit back) {
	this->front = front;
	this->back = back;
}

////////////////////////////////////////////////// METHODES

int ColorPair::pair_num() const{
	return (front + 1) * COLORS + (back + 1) + 1;
}

ColorPair::operator chtype() const{
	
	return COLOR_PAIR(pair_num());
}

////////////////////////////////////////////////// VARIABLE STATIQUES

const ColorPair ColorPair::Default(DEFAULT, DEFAULT);
const ColorPair ColorPair::WhiteBlack(WHITE, BLACK);
const ColorPair ColorPair::WhiteRed(WHITE, RED);
const ColorPair ColorPair::WhiteGreen(WHITE, GREEN);
const ColorPair ColorPair::WhiteBlue(WHITE, BLUE);
const ColorPair ColorPair::WhiteMagenta(WHITE, MAGENTA);
const ColorPair ColorPair::WhiteYellow(WHITE, YELLOW);
const ColorPair ColorPair::WhiteCyan(WHITE, CYAN);

const ColorPair ColorPair::White(WHITE, DEFAULT);
const ColorPair ColorPair::Black(BLACK, DEFAULT);
const ColorPair ColorPair::Red(RED, DEFAULT);
const ColorPair ColorPair::Green(GREEN, DEFAULT);
const ColorPair ColorPair::Blue(BLUE, DEFAULT);
const ColorPair ColorPair::Magenta(MAGENTA, DEFAULT);
const ColorPair ColorPair::Yellow(YELLOW, DEFAULT);
const ColorPair ColorPair::Cyan(CYAN, DEFAULT);

////////////////////////////////////////////////// FONCTIONS DEFINITION

void init_color_pairs(){

	if (has_colors()) {

		start_color();

		use_default_colors(); // -> COLOR_PAIR(0) = DefaultColor (est un extensino de ncurses)

		for (int j = 0; j < COLORS; ++j)
		{
			for (int i = 0; i < COLORS; ++i)
			{
				//init_pair(numero, front, back) (-1 correspond à la couleur par default du terminal)
				init_pair(j * COLORS + i + 1, j - 1, i - 1);
				//init_pair(i, i, -1);
			}
		}
	}
}

//#DEFINITION_END