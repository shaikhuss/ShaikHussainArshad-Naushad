//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Particle.h"



Particle::Particle()
{
	// construtor
	this->life = 0.0f;
	this->position.set(0.0f, 0.0f, 0.0f);
	this->velocity.set(0.0f, 0.0f, 0.0f);
	this->scale.set(1.0f, 1.0f, 1.0f);
	this->rotation = 0.0f;
	this->rotation_velocity = 0.25f;
}

Particle::Particle(const Particle& tmp)
{
	// copy the data only
	// this way of copying data is more efficient that element by element
	this->position = tmp.position;  // p.position
	this->velocity = tmp.velocity;
	this->scale = tmp.scale;
	this->rotation = tmp.rotation;
	this->rotation_velocity = tmp.rotation_velocity;
	this->life = tmp.life;
}

void Particle::updatePos(Vect4D& pos, const Vect4D& vel, const float time_elapsed) const
{
	pos._m = _mm_add_ps(pos._m, _mm_mul_ps(vel._m, _mm_set1_ps(time_elapsed)));
}

void Particle::Update(const float& time_elapsed)
{
	
	life += time_elapsed;

	updatePos(position, velocity, time_elapsed);

	
	Vect4D axis(1.0f, 0.0f, 0.0f);
	Vect4D v(0.0f, 50.0f, 0.0f);
	position.Cross(axis, v);	  

	v.norm(v);	

	position = position + v * (0.07f * life);  

	rotation = rotation + rotation_velocity * time_elapsed * 4.0f;
	

}


// End of file
