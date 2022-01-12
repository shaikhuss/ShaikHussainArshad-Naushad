//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "Model.h"

namespace Azul
{
	Model::Model()
		: numVerts(0),
		numTris(0),    // Keenan(20)
		vao(0),
		vbo_verts(0),
		vbo_trilist(0),
		poRefSphere(new Sphere())
	{
		assert(this->poRefSphere);
	}

	Model::~Model()
	{
		delete this->poRefSphere;
	}
}

// --- End of File ---
