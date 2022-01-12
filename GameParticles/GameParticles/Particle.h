//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"
#include "Matrix.h"
#include <xmmintrin.h>
#include <smmintrin.h>  

class Particle : Align16
{
public:
	friend class ParticleEmitter;

	// big four
	Particle();
	Particle(const Particle& tmp);
	void updatePos(Vect4D& pos, const Vect4D& vel, const float time_elapsed) const;
	~Particle() = default;
	Particle& operator = (const Particle&) = default;

	void Update(const float& time_elapsed);
	


private:


	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;
	float	life;
	float	rotation;
	float	rotation_velocity;
};


#endif 

// End of File
