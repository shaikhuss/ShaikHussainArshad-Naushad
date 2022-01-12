//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"


class ParticleEmitter
{
public:

	// big four
	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter&) = default;
	~ParticleEmitter();
	ParticleEmitter& operator=(const ParticleEmitter&) = default;

	void update();
	void draw();
	void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);

;


private:
	Particle* pParticle;
	Particle* pBuffer; 

	Vect4D	vel_variance;
	Vect4D	pos_variance;
	Vect4D	start_position;
	Vect4D	start_velocity;
	int		max_particles;
	int		last_active_particle;
	float	max_life;
	
	float	spawn_frequency;
	float	last_spawn;
	float	last_loop;
	float	scale_variance;
};

#endif

// End of File
