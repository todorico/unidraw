#include "Particle.h"

using namespace std;

#define DISPLAY_STATS \
		mvwprintw(canvas, 0, 0, "Particles : %d, Calculation : %f, Runtime : %f", PS.particles.size(), calc_time, run_time); \
		mvwprintw(canvas, 1, 0, "Frame time : %f, Clear : %f, Display : %f, Update : %f", frame_time, clear_time, display_time, update_time); \
		mvwprintw(canvas, 2, 0, "Input time : %f, Mouse pos : %d %d   ", input_time, Mouse::get_position().x, Mouse::get_position().y);\
		canvas.display(); \

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	//program variables:

	int nbframe = 0;
	float update_time = 0.0;
	float frame_time = 0.0;

	//argv variables:

	//int border = 0;
	int n = 30000;
	float lifetime = 10000000;
	Vector2f gravity(0.0, 0.0);
	Vector2f wind(0.0, 0.0);

	if(argc > 1)
		n = atoi(argv[1]);

	if(argc > 2)
		lifetime = atof(argv[2]);

	if(argc > 3)
		gravity.x = atof(argv[3]);

	if(argc > 4)
		wind.x = atof(argv[4]);

	if(argc > 5)
		wind.y = atof(argv[5]);

	Term::init_curs();
	Term::set_timeout(0);
	
	Canvas canvas;

	canvas.set_attr(Attr::Bright);
	canvas.set_color(ColorPair::Default);

	IntRect zone(Vector2i::zero, Vector2i(50, 50));

	ParticleSystem PS(lifetime, IntRect(0, 0, 0, 0), 0.95);
	//PS.add_particles(n, Vector2f(canvas.get_size()) / float(2.0));
	PS.add_particles(n, zone);

	while(!Keyboard::is_pressed(Keyboard::Escape)){

		nbframe++;

		float total_time = clock();

		////////// READ AND USE INPUT

		Term::read_input();
		
		float input_time = (clock() - total_time) / (float)CLOCKS_PER_SEC;

		////////// FORCES CALCULATIONS

		float calc_time = clock();

		PS.apply_force(gravity + wind);

		Vector2f origin(cell_to_pixel_pos(Mouse::get_position()));

		if(Mouse::is_pressed(Mouse::Left))
			PS.apply_repeller(Repeller(origin));
		else if(Mouse::is_pressed(Mouse::Right))
			PS.apply_attractor(Attractor(origin));
		else if(Mouse::is_released(Mouse::Middle))
			PS.add_particles(n, zone);

		calc_time = (clock() - calc_time) / (float)CLOCKS_PER_SEC;

		////////// CLEAR SCREEN

		float clear_time = clock();

		canvas.clear();

		clear_time = (clock() - clear_time) / (float)CLOCKS_PER_SEC;

		////////// RUN
		

		float run_time = clock();

		//canvas.set_border((Window::BorderType)border);
		PS.run(canvas);
	
		run_time = (clock() - run_time) / (float)CLOCKS_PER_SEC;
		
		////////// DISPLAY CANVAS (PRINT TO VIRTUAL SCREEN)

		float display_time = clock();

		canvas.display();

		display_time = (clock() - display_time) / (float)CLOCKS_PER_SEC;
		
		////////// DISPLAY STATS

		DISPLAY_STATS

		////////// UPDATE TERMINAL (PRINT TO REAL SCREEN)

		update_time = clock();

		Term::update();
		
		update_time = (clock() - update_time) / (float)CLOCKS_PER_SEC;

		frame_time = (clock() - total_time) / (float)CLOCKS_PER_SEC;

		//Term::wait(16);
	}

	Term::end_curs();

	return 0;
}