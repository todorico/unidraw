#include "Color.h"

//#DEFINITION
////////////////////////////////////////////////// CONSTRUCTEURS

Color::Color() : r(), g(), b() {}

Color::Color(chtype color) : r(), g(), b() {

	short f = 0;
	short red = 0, green = 0, blue = 0; 

	/* Get foreground color */
	pair_content(PAIR_NUMBER(color), &f, NULL);

	/* Get rgb of foreground color */
	color_content(f, &red, &green, &blue);

	//1000 est l'intensité maximale qui peut etre stocker dans red/green/blue.
	r = (int)(red * 255) / 1000; 
	g = (int)(green * 255) / 1000; 
	b = (int)(blue * 255) / 1000; 
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}

////////////////////////////////////////////////// METHODES

int Color::to_number() const{

	switch(COLORS){
		case 8:
		return to_8_color_num(r, g, b);
		break;

		case 16:
		return to_16_color_num(r, g, b);
		break;

		case 88:
		return to_88_color_num(r, g, b);
		break;

		case 256:
		return to_256_color_num(r, g, b);
		break;

		default:
		return -1;
		break;
	}
}

short Color::to_pair() const{
	
	int color_num = to_number();

	return color_num == -1 ? 0 : color_num + 1;
}

std::string Color::to_string() const{
	std::stringstream ss;
	ss << "(" << r << ", " << g << ", " << b << ")";
	return ss.str();
}

Color::operator chtype() const{
	return COLOR_PAIR(to_pair());
}

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

	front = to_color_rgb(f);
	back = to_color_rgb(b);
}

ColorPair::ColorPair(ColorUnit front, ColorUnit back) {
	this->front = to_color_rgb(front);
	this->back = to_color_rgb(back);
}

ColorPair::ColorPair(Color front, Color back) {
	this->front = front;
	this->back = back; 
}

////////////////////////////////////////////////// METHODES

int ColorPair::pair_num() const{
	return front.to_pair(); //* COLORS + (to_number(back));
}

ColorPair::operator chtype() const{
	return COLOR_PAIR(pair_num());
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

		use_default_colors(); // -> COLOR_PAIR(0) = Default Color (est un extension de ncurses)

		for (int f = 0; f < COLORS; ++f){
			init_pair(f + 1, f, -1);
		}
	}
}

bool is_color_0_to_7(uint8_t r, uint8_t g, uint8_t b){
	return (r == 192 && r == g && r == b) || ((r == 0 || r == 128) && (g == 0 || g == 128) && (b == 0 || b == 128));
}

bool is_color_8_to_15(uint8_t r, uint8_t g, uint8_t b){
	return !(r == 0 && g == 0 && b == 0) && (((r == 128 && r == g && r == b) || ((r == 0 || r == 255) && (g == 0 || g == 255) && (b == 0 || b == 255))));
}

bool is_color_greyscale(uint8_t r, uint8_t g, uint8_t b){
	return (r >= 8 && r <= 238) && r == g && r == b;
}

int to_8_color_num(uint8_t r, uint8_t g, uint8_t b){
	uint8_t red = r > 0 ? 1 : 0; 
	uint8_t green = g > 0 ? 1 : 0; 
	uint8_t blue = b > 0 ? 1 : 0; 

	return red + 2 * green + 4 * blue;
}

int to_16_color_num(uint8_t r, uint8_t g, uint8_t b){

	if(is_color_8_to_15(r, g, b)){
		if(r == 128)
			return 8;
		else
			return 8 + to_8_color_num(r, g, b);
	}
	else
		return to_8_color_num(r, g, b);
}

/* verifier les echelles de gris */
int to_88_color_num(uint8_t r, uint8_t g, uint8_t b){

	if(is_color_greyscale(r, g, b)){
		return 80 + round((r * 8) / 238.0f); 
	}
	else{
		short red = std::max(((r * 4) / 255) - 1, 0); 
		short green = std::max(((g * 4) / 255) - 1, 0); 
		short blue = std::max(((b * 4) / 255) - 1, 0); 

		return 16 + blue + 4 * green + 16 * red;
	}
}

int to_256_color_num(uint8_t r, uint8_t g, uint8_t b){

	if(is_color_greyscale(r, g, b)){
		return 232 + ((r * 24) / 238.0f); 
	}
	else{
		short red = std::max(((r * 6) / 255) - 1, 0); 
		short green = std::max(((g * 6) / 255) - 1, 0); 
		short blue = std::max(((b * 6) / 255) - 1, 0); 

		return 16 + blue + 6 * green + 36 * red;
	}
}

Color to_color_rgb(int color_num){
	short r = 0, g = 0, b = 0;

	color_content(color_num, &r, &g, &b);

	return Color((int)(r * 255) / 1000, (int)(g * 255) / 1000, (int)(b * 255) / 1000); 
}

//#DEFINITION_END