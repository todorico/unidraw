#include "Term.h"

/* Affiche toutes les Pairs de couleurs disponibles dans le terminal */
void print_colors(int mod){





/*
	Term::scr.set_color(ColorPair::Blue);
	printw("%c", '*');

	Term::scr.set_color(ColorPair::Yellow);
	printw("%c", '*');

	Term::scr.set_color(ColorPair::Green);
	printw("%c", '*');

	Term::scr.set_color(ColorPair::Magenta);
	printw("%c", '*');

	Term::scr.set_color(ColorPair::Red);
	printw("%c", '*');

	Term::scr.set_color(ColorPair::Cyan);
	printw("%c", '*');

	Term::scr.set_color(ColorPair::Default);
	printw("%c", '*');
*/

	

	//int mod = 6;

	for (int i = 0; i < COLORS; ++i)
	{
		if(i % mod == 4 && i != 0)
			printw("\n");

		attron(COLOR_PAIR(i));
		printw("@");
		attroff(COLOR_PAIR(i));
	}

	/*
	for (int j = 0; j < COLORS; ++j)
	{
		for (int i = 0; i < COLORS; ++i)
		{
			int num = (j + 1) * COLORS + (i + 1) + 1;

			attron(COLOR_PAIR(num));
			printw("%c", '*');
			attroff(COLOR_PAIR(num));
		}
	}
*/
/*
	for(int b = -1 ; b < 5 ; b++){
		for(int g = -1 ; g < 5 ; g++){
			for(int r = -1 ; r < 5 ; r++){
				int red = r == -1 ? 0 : 95 + 40 * r;
				int green = g == -1 ? 0 : 95 + 40 * g;
				int blue = b == -1 ? 0 : 95 + 40 * b;
			}
		}
	}
*/
}

int map_to_table(int rgb){
	rgb = rgb % 256;
	return (rgb - 95) + (rgb - 95) % 40; //faire un moyenne
}

int map_to_pair(int rgb){
	
	map_to_table(rgb);

	return rgb == 0 ? 0 : ((rgb - 95) / 40) + 1;
}

int pair(int red, int green, int blue){
	if(red == green && red == blue){
		8 + 10;
	}
	map_to_table(red);
	map_to_table(green);
	map_to_table(blue);

	return 16 + map_to_pair(blue) + 6 * map_to_pair(green) + 6 * 6 * map_to_pair(red); 
}

class Color{

	chtype m_color;

	Color();
	Color(chtype);
	Color(int r, int g, int b);

/* Renvoie le numéro correspondant à la paire de couleur composée de front et back */
	int pair_num() const;

/* Convertie en chtype la paire de couleur composée de front et back */
	operator chtype() const;

/* Numero de pair associés a la couleur */
	static chtype pair(Color front, Color back = Color::Default);

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

int main(int argc, char** argv)
{
	int mod = 6;

	if(argc > 1)
		mod = atoi(argv[1]);
	
	Term::init_curs();

	print_colors(mod);

	while(Term::read_input() != 'q'){

		//mvprintw(0, 0, "Mouse : (%d, %d) ", Mouse::get_position().x, Mouse::get_position().y);
		refresh();
	}

	Term::end_curs();
	
	return 0;
}
