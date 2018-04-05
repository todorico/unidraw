#include "Particle.h"

//#DEFINITION
////////////////////////////////////////////////// CONSTRUCTEURS
 
Particle::Particle() : position(), velocity(random(-1, 1), random(-1, -1)), acceleration(), lifetime(), mass(1) {}

Particle::Particle(const Vector2f& position, float lifetime) : position(position), velocity(random(-1, 1), random(-1, -1)), acceleration(), lifetime(lifetime), mass(1){}

Particle::Particle(const Vector2f& pos, const Vector2f& v, float lifetime) : position(pos), velocity(v), acceleration(), lifetime(lifetime), mass(1) {} 

////////////////////////////////////////////////// METHODES

void Particle::apply_force(const Vector2f& force){
	acceleration += (force / mass);
}

void Particle::update() { 
	velocity += acceleration;
	position += velocity;
	acceleration = Vector2f::zero;
	lifetime -= 1.0;
}

void Particle::display(Canvas& c) {
		
	c.set(position.rounded());
	//c.toggle(position.rounded());
}

void Particle::run(Canvas& c) {
	update();
	display(c);
}

bool Particle::is_alive() {
	return lifetime > 0;
}

////////////////////////////////////////////////// CONSTRUCTEURS

Attractor::Attractor() : position(), strength(100), mass(1) {}

Attractor::Attractor(const Vector2f& position) : position(position), strength(100), mass(1) {}

////////////////////////////////////////////////// METHODES

Vector2f Attractor::attract(const Particle& p) const {

	Vector2f dir = position - p.position;
	
	float dist_squared = dir.length_squared();

	//constrain dist pour ne pas perdre le controle des particules trop rapides
	dist_squared = constrain(dist_squared, 100, 1000000000000);

	dir.normalize();

	float force = (strength * mass * p.mass) / dist_squared;
	
	return dir * force;
}

////////////////////////////////////////////////// CONSTRUCTEURS

Repeller::Repeller() : position(), strength(1), mass(1) {}

Repeller::Repeller(const Vector2f& position) : position(position), strength(100), mass(1) {}

////////////////////////////////////////////////// METHODES

Vector2f Repeller::repel(const Particle& p) const {

	Vector2f dir = position - p.position;
	
	float dist_squared = dir.length_squared();

	//constrain dist pour ne pas perdre le controle des particules trop rapides
	dist_squared = constrain(dist_squared, 100, 10000000000000);

	dir.normalize();

	float force = (strength * mass * p.mass) / dist_squared; 

	return -dir * force;
}

////////////////////////////////////////////////// CONSTRUCTEURS

ParticleSystem::ParticleSystem() : particles(), duration(1000), velocity_range(), velocity_over_time() {}

ParticleSystem::ParticleSystem(float duration, IntRect velocity_range, float velocity_over_time) : particles(),  duration(duration), velocity_range(velocity_range), velocity_over_time(velocity_over_time) {}
 
////////////////////////////////////////////////// METHODES

void ParticleSystem::apply_force(const Vector2f& force){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		it->apply_force(force);
	}
}

void ParticleSystem::apply_repeller(const Repeller& rep){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		Vector2f force = rep.repel(*it);
		it->apply_force(force);
	}
}

void ParticleSystem::apply_attractor(const Attractor& att){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		Vector2f force = att.attract(*it);
		it->apply_force(force);
	}
}

void ParticleSystem::add_particles(int n, Vector2f origin){
	for(int i = 0 ; i < n ; i++){
		particles.push_back(Particle(origin, 
									 Vector2f(random(velocity_range.x, velocity_range.y), random(velocity_range.width, velocity_range.height)), 
									 duration));
	}
}

void ParticleSystem::add_particles(int n, IntRect zone){
	for(int i = 0 ; i < n ; i++){
		particles.push_back(Particle(Vector2f(random(zone.x, zone.width), random(zone.y, zone.height)), 
									 Vector2f(random(velocity_range.x, velocity_range.y), random(velocity_range.width, velocity_range.height)), 
									 duration));
	}
}

void ParticleSystem::run(Canvas& c){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		
		if(it->is_alive()){
			it->run(c);
			it->velocity *= velocity_over_time;
		}
		else
			it = particles.erase(it); //met a jour l'iterateur pour pointer vers l'iterateur suivant
	}
}

////////////////////////////////////////////////// FONCTIONS DEFINITION

float random(int start, int end, int precision){

	int longueur = abs(abs(end) - start);

	int randlong = (rand() % ((longueur * precision) + 1));

	return (float) start + ((float) randlong / (float) precision);
}

float constrain(float f, float start, float end){
	return f < start ? start : f > end ? end : f;  
}

//#DEFINITION_END