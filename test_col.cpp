#include "Canvas.h"

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
	8 premier si (r == 0 || r == 128) && (b == 0 || b == 128) && (b == 0 || b == 128)
	&& (r == b == g == 192)

	16 premier si (r == b == g == 128) && (r == 0 || r == 255) && (b == 0 || b == 255) && (b == 0 || b == 255)

	r % 128 + 2 * (g % 128) + 4 * (b % 128) 
	0 --> 15 classic color 		
	16 --> 231 rgb color
	232 --> 255 grey color
	
	int RGB_MAX_INTENSITY = 0;
	int GREY_MAX_INTENSITY = 0;

	if(COLORS == 88){
		RGB_MAX_INTENSITY = 4;
		GREY_MAX_INTENSITY = 8;
	}
	else if(COLORS == 256){
		RGB_MAX_INTENSITY = 6;
		GREY_MAX_INTENSITY = 24;
	}

	grey = 8 + 10 * i
	
	(grey - 8) / 10 = i
*/
}

int main(int argc, char** argv)
{
	int mod = 6;

	int n = 10;
	int min = 0;
	int max = 0;

	srand(time(NULL));

	if(argc > 1)
		n = atoi(argv[1]);
	if(argc > 2)
		min = atoi(argv[2]);
	if(argc > 3)
		max = atoi(argv[3]);

	Term::init_curs();

	Term::scr.set_background_color(Color::White);

	for(int r = 1 ; r < 7 ; r++){
		for(int g = 1 ; g < 7 ; g++){
			for(int b = 1 ; b < 7 ; b++){
				Term::scr.set_color(Color((r * 255) / 6, (g * 255) / 6, (b * 255) / 6));
				printw("%c", '@');
			}
		}
	}

	getch();

	Term::end_curs();
	
	return 0;
}
