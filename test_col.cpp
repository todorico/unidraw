#include "Term.h"

/* Affiche toutes les Pairs de couleurs disponibles dans le terminal */
void print_colors(int mod){

	for (int i = 0; i < COLORS; ++i)
	{
		if(i % mod == 4 && i != 0)
			printw("\n");

		attron(COLOR_PAIR(i));
		printw("@");
		attroff(COLOR_PAIR(i));
	}

/*
	0 --> 15 classic color 		
	16 --> 231 rgb color
	232 --> 255 grey color
	
	int COLORS_VARIATION = 0;
	int GREYS_VARIATION = 0;

	if(COLORS == 88){
		COLORS_VARIATION = 4;
		GREYS_VARIATION = 8;
	}
	else if(COLORS == 256){
		COLORS_VARIATION = 6;
		GREYS_VARIATION = 24;
	}

	grey = 8 + 10 * i
	
	(grey - 8) / 10 = i

 */
}
/*
bool is_number_grey_color(int color_num){
	return color_num >= 232;
}

bool is_number_system_color(int color_num){
	return color_num < 16;
}

bool is_color_grey(uint8_t r, uint8_t g, uint8_t b){
	return r == g && r == b && r && r >= 8 && r <= 238;
}

int to_grey_index(uint8_t rgb){
	return round((rgb - 8) / 10.0f); //parametrer les valeurs selon le nb couleur du terminal
}

int to_color_index(uint8_t rgb){
	return (rgb - 95) < 0 ? round(rgb / 95.0f) : round((rgb - 95) / 40.0f) + 1; //parametrer les valeurs selon le nb couleur du terminal
}

int to_color_num(uint8_t r, uint8_t g, uint8_t b){

	if(is_color_grey(r, g, b))
		return 232 + to_grey_index(r);
	else
		return 16 + to_color_index(b) + (6 * to_color_index(g)) + (6 * 6 * to_color_index(r)); //parametrer les valeurs selon le nb couleur du terminal
}

class Color {

public:
	
	uint8_t r;
	uint8_t g;
	uint8_t b;

	Color();
	Color(uint8_t red, uint8_t green, uint8_t blue);

	static const Color Default;
	static const Color White;
	static const Color Black;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Magenta;
	static const Color Yellow;
	static const Color Cyan;
};

bool operator==(const Color& left, const Color& right);
bool operator!=(const Color& left, const Color& right);

Color operator+(const Color& left, const Color& right);//min(c + c /2, 255)
Color operator-(const Color& left, const Color& right); 
Color operator*(const Color& left, const Color& right); //restraindre a 255

Color& operator+=(Color& left, const Color& right);
Color& operator-=(Color& left, const Color& right); //restraindre a 255
Color& operator*=(Color& left, const Color& right);

Color::Color() : r(), g(), b() {}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}

bool operator==(const Color& left, const Color& right){
	return left.r == right.r && left.g == right.g && left.b == right.b; 
}

bool operator!=(const Color& left, const Color& right){
	return !(left == right);
}

//faire attention au cas ou l'addition depasse 255
Color operator+(const Color& left, const Color& right){
	return Color(std::min(((int)left.r + right.r) / 2, 255),std::min(((int)left.g + right.g) / 2, 255), std::min(((int)left.b + right.b) / 2, 255));
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
	return to_color_num(c.r, c.g, c.b);
}
*/

int main(int argc, char** argv)
{
	int mod = 6;

	int n = 20000;
	int min = 50;
	int max = 255;

	srand(time(NULL));

	if(argc > 1)
		n = atoi(argv[1]);
	if(argc > 2)
		min = atoi(argv[2]);
	if(argc > 3)
		max = atoi(argv[3]);

	Term::init_curs();

	//print_colors(mod);
	
	for(int i = n ; i < min ; i++){

		if(i % 256 == 0 && i != 0)
			printw("\n");
		//for(int j = 0 ; j < num ; j++){
				//Color color(n, min, max);
				attron(COLOR_PAIR(i));
				printw("*");
				attroff(COLOR_PAIR(i));	
		//}	
	}

	getch();

	Term::end_curs();
	
	return 0;
}
