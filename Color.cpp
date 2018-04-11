#include "Color.h"

//#DEFINITION
////////////////////////////////////////////////// CONSTRUCTEURS

Color::Color() : r(), g(), b() {}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}

////////////////////////////////////////////////// VARIABLES STATIQUES

const Color Color::Black(0, 0, 0);
const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Yellow(255, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Magenta(255, 0, 255);
const Color Color::Cyan(0, 255, 255);
const Color Color::White(255, 255, 255);

////////////////////////////////////////////////// OPERATEURS

bool operator==(const Color& left, const Color& right){
	return left.r == right.r && left.g == right.g && left.b == right.b; 
}

bool operator!=(const Color& left, const Color& right){
	return !(left == right);
}

//faire attention au cas ou l'addition depasse 255
Color operator+(const Color& left, const Color& right){
	return Color(std::min(((int)left.r + right.r) / 2, 255), std::min(((int)left.g + right.g) / 2, 255), std::min(((int)left.b + right.b) / 2, 255));
}

//faire attention au cas ou a soustraction est negative
Color operator-(const Color& left, const Color& right){
	return Color(std::max(((int)left.r - right.r) / 2, 0), std::max(((int)left.g - right.g) / 2, 0), std::max(((int)left.b - right.b) / 2, 0));
}

//faire attention au cas ou la multiplication depasse 255
Color operator*(const Color& left, const Color& right){
	return Color(((int)left.r * right.r) / 255, ((int)left.g * right.g) / 255, ((int)left.b * right.b) / 255);
}

Color& operator+=(Color& left, const Color& right){
	left.r = std::min(((int)left.r + right.r) / 2, 255);
	left.g = std::min(((int)left.g + right.g) / 2, 255);
	left.b = std::min(((int)left.b + right.b) / 2, 255);
	return left;
}

Color& operator-=(Color& left, const Color& right){
	left.r = std::max(((int)left.r - right.r) / 2, 0);
	left.g = std::max(((int)left.g - right.g) / 2, 0);
	left.b = std::max(((int)left.b - right.b) / 2, 0);
	return left;
}
 //restraindre a 255
Color& operator*=(Color& left, const Color& right){
	left.r = ((int)left.r * right.r) / 255;
	left.g = ((int)left.g * right.g) / 255;
	left.b = ((int)left.b * right.b) / 255;
	return left;
}

////////////////////////////////////////////////// CONSTRUCTEURS

ColorPair::ColorPair() : ColorPair(DEFAULT, DEFAULT) {}

ColorPair::ColorPair(chtype c){

	//chtype color = c & A_COLOR;
	short f = 0, b = 0;

	pair_content(PAIR_NUMBER(c), &f, &b);

	front = to_color(f);
	back = to_color(b);
}

ColorPair::ColorPair(ColorUnit front, ColorUnit back) {
	this->front = to_color(front);
	this->back = to_color(back);
}

ColorPair::ColorPair(Color front, Color back) {
	this->front = front;
	this->back = back; 
}

////////////////////////////////////////////////// METHODES

int ColorPair::pair_num() const{
	return to_number(front); //* COLORS + (to_number(back));
}

ColorPair::operator chtype() const{
	return COLOR_PAIR(pair_num()) + 1;
}

////////////////////////////////////////////////// VARIABLE STATIQUES

const ColorPair ColorPair::Default(DEFAULT, DEFAULT);
const ColorPair ColorPair::Black(BLACK, DEFAULT);
const ColorPair ColorPair::Red(RED, DEFAULT);
const ColorPair ColorPair::Green(GREEN, DEFAULT);
const ColorPair ColorPair::Yellow(YELLOW, DEFAULT);
const ColorPair ColorPair::Blue(BLUE, DEFAULT);
const ColorPair ColorPair::Magenta(MAGENTA, DEFAULT);
const ColorPair ColorPair::Cyan(CYAN, DEFAULT);
const ColorPair ColorPair::White(WHITE, DEFAULT);

////////////////////////////////////////////////// FONCTIONS DEFINITION

void init_color_pairs(){

	if (has_colors()) {

		start_color();

		use_default_colors(); // -> COLOR_PAIR(0) = DefaultColor (est un extensino de ncurses)

		//int k = 1;
		/*
		for (int b = 0; b < 8; ++b){

			for (int f = 0; f < 8; ++f){
				
				init_pair(k, f, b);
				k++;
			}
		}
		*/
		for (int f = 0; f < COLORS; ++f){
			//init_pair(numero, front, back) (-1 correspond à la couleur par default du terminal)
			//init_pair(b * COLORS + f + 1, f, b);
			init_pair(f + 1, f, -1);
		}


	}
}

bool is_number_grey_color(int color_num){ 
	return color_num >= 232;
}

bool is_number_system_color(int color_num){
	return color_num < 16;
}

bool is_color_grey(uint8_t r, uint8_t g, uint8_t b){
	return r == g && r == b && r && r >= 8 && r <= 238;
}
/*
bool is_system_color(uint8_t r, uint8_t g, uint8_t b){
	return 0; // a implementer
}
*/
int to_grey_index(uint8_t rgb){
	return round((rgb - 8) / 10.0f); //parametrer les valeurs selon le nb couleur du terminal
}

int to_color_index(uint8_t rgb){
	return (rgb - 95) < 0 ? round(rgb / 95.0f) : round((rgb - 95) / 40.0f) + 1; //parametrer les valeurs selon le nb couleur du terminal
}

Color to_color(int color_num) {

	Color c;

	if(is_number_grey_color(color_num)){

		int deb = (color_num - 232);
		int grey = 8 + 10 * (deb / 10); 

		c.b = grey; 
		c.g = grey; 
		c.r = grey;
	}
	else{

		int deb = (color_num - 16);

		c.b = deb % 6 == 0 ? 0 : 95 + 40 * ((deb % 6) - 1);
		c.g = deb / 6 == 0 ? 0 : 95 + 40 * ((deb / 6) - 1);
		c.r = deb / 6 * 6 == 0 ? 0 : 95 + 40 * ((deb / 6 * 6) - 1);
	}

	return c;
}

int to_number(const Color& c) {
	if(is_color_grey(c.r, c.g, c.b))
		return 232 + to_grey_index(c.r);
	else
		return 16 + to_color_index(c.b) + (6 * to_color_index(c.g)) + (6 * 6 * to_color_index(c.r)); //parametrer les valeurs selon le nb couleur du terminal
}

//#DEFINITION_END