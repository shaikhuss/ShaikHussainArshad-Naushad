//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef MODEL_H
#define MODEL_H

#include "sb7.h"
#include "ModelLink.h"
#include "BoundingSphere.h"

namespace Azul
{
	class Model : public ModelLink
	{
	public:
		Model();
		Model(Model& copyModel) = delete;
		Model& operator = (Model& copyModel) = delete;
		virtual ~Model();

		// Data
		int numVerts;
		int numTris;    // Keenan(20)

		GLuint vao;
		GLuint vbo_verts;   // xyzuvn
		GLuint vbo_trilist;   // trilist

		// Reference sphere... before any transformations are applied
		Sphere *poRefSphere;
		char* name;

	protected:
		// load VAO
		virtual void privCreateVAO(const char* const pModelFileName) = 0;

	private:


	};

}

#endif

// --- End of File ---
