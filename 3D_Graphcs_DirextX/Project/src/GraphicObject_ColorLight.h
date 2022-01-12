// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorLight.h"

class GraphicObject_ColorLight : public GraphicObject_Base
{
	friend class ShaderColorLight;

public:
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;				 // Copy constructor
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;                    // Move constructor
	~GraphicObject_ColorLight();		  											 // Destructor

	GraphicObject_ColorLight() = delete;

	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec);
	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod);

private:
	ShaderColorLight* pShader;

	//Vect							Color;
	Vect* MeshMaterials;

	Matrix							World;

};

#endif _GraphicObject_ColorLight
