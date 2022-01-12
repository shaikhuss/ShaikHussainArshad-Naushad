//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "DO_NOT_MODIFY\OpenGLInterface.h"
#include "ParticleEmitter.h"
#include "Settings.h"


extern PerformanceTimer GlobalTimer;
extern Matrix inverseCameraMatrix;

static const unsigned char squareColors[] =
{
	// ----------------------------
	//  point is actually a quad   
	//  set color on each vertex   
	// ----------------------------
	//    Vert A = Yellow 
	//    Vert B = Yellow
	//    Vert C = Yellow
	//    Vert D = Yellow
	// ----------------------------

	200.0f,  200.0f,  0.0f,  255.0f,
	200.0f,  200.0f,  0.0f,  255.0f,
	200.0f,  200.0f,  0.0f,  255.0f,
	200.0f,  200.0f,  0.0f,  255.0f,
};

static const float squareVertices[] =
{
	// --------------------
	//   Vert A = (x,y,z)
	//   Vert B = (x,y,z)
	//   Vert C = (x,y,z)
	//   Vert D = (x,y,z)
	// --------------------

	-0.015f,  -0.015f, 0.0f, // Size of Triangle
	 0.015f,  -0.015f, 0.0f, // Size of Triangle
	-0.015f,   0.015f, 0.0f, // Size of Triangle
	 0.015f,   0.015f, 0.0f, // Size of Triangle
};

ParticleEmitter::ParticleEmitter()
	: start_position(0.0f, 0.0f, 0.0f),
	start_velocity(0.0f, 1.0f, 0.0f),
	max_life(MAX_LIFE),
	max_particles(NUM_PARTICLES),
	spawn_frequency(0.0000001f),
	last_active_particle(-1),
	vel_variance(1.0f, 4.0f, 0.4f),
	pos_variance(1.0f, 1.0f, 1.0f),
	scale_variance(2.5f)
{
	// OpenGL goo... don't worrry about this
	glVertexPointer(3, GL_FLOAT, 0, squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
	glEnableClientState(GL_COLOR_ARRAY);

	pParticle= new Particle[NUM_PARTICLES];
	Particle* t = pParticle;
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		t->life = 0.0f;
		t->position = start_position;
		t->velocity = start_velocity;
		t->scale.set(1.0f, 1.0f, 1.0f, 1.0f);
		this->Execute(t->position, t->velocity, t->scale);
		t++;
	}

	pBuffer = new Particle[NUM_PARTICLES];
	memcpy(pBuffer, pParticle, NUM_PARTICLES * sizeof(Particle));

	GlobalTimer.Toc();

	last_spawn = GlobalTimer.TimeInSeconds();
	last_loop = GlobalTimer.TimeInSeconds();
}
ParticleEmitter::~ParticleEmitter()
{
	delete[] pParticle;
	delete[] pBuffer;
}


void ParticleEmitter::update()
{
	// get current time
	GlobalTimer.Toc();
	float current_time = GlobalTimer.TimeInSeconds();

	// spawn particles
	float time_elapsed = current_time - last_spawn;


	//this->SpawnParticle();
	last_spawn = current_time;

	// total elapsed
	time_elapsed = current_time - last_loop;


	// -- new update method
	if (pParticle->life > max_life)
	{
		memcpy(pParticle, pBuffer, NUM_PARTICLES * sizeof(Particle));
	}
	Particle* t = pParticle;
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		t->Update(time_elapsed);
		t = t + 1;
	}

	last_loop = current_time;
}





void ParticleEmitter::draw()
{

	Particle* p = pParticle;


	Vect4D camPosVect;
	float cos;
	float sin;    // 1.78


	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		
		camPosVect = p->position * 0.35f;
		cos = cosf(p->rotation);   
		sin = sinf(p->rotation);   

		
		Matrix tmp(cos * p->scale.x * p->scale.x, (-sin) * p->scale.x * p->scale.y, 0.0f, 0.0f,
			sin * p->scale.y * p->scale.y, cos * p->scale.y * p->scale.x, 0.0f, 0.0f,
			0.0f, 0.0f, p->scale.z * p->scale.z, 0.0f,
			((inverseCameraMatrix.m12 + camPosVect.x) * cos + (inverseCameraMatrix.m13 + camPosVect.y) * sin) * p->scale.x, ((inverseCameraMatrix.m12 + camPosVect.x) * (-sin) + (inverseCameraMatrix.m13 + camPosVect.y) * cos) * p->scale.y, (inverseCameraMatrix.m14 + camPosVect.z) * p->scale.z, 1.0f);

		glLoadMatrixf(reinterpret_cast<float*>(&(tmp)));

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		p += 1;
	}
}

void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// --------------------------------------------------------------
	//   Ses it's ugly - I didn't write this so don't bitch at me   |
	//   Sometimes code like this is inside real commerical code    |
	//   ( so now you know how it feels )  |
	//---------------------------------------------------------------

	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.005f; // Var
	float sign = static_cast<float>(rand() % 2);  // Sign 
	float* t_pos = reinterpret_cast<float*>(&pos);
	float* t_var = &pos_variance[x];
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	// x  - add velocity
	t_pos = &vel[x];
	t_var = &vel_variance[x];
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if (sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// correct the sign
	var = 1.5f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	if (sign == 0)
	{
		var *= -1.0;
	}
	sc = sc * var;
}



// End of file
