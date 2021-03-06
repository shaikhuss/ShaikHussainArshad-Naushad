//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "sb7.h"
#include "ShaderLink.h"

namespace Azul
{
	class ShaderObject : public ShaderLink
	{
	public:
		enum class Name
		{
			NULL_SHADER,
			COLOR_LIGHT,
			COLOR_SINGLE,
			SPRITE,
			TEXTURE_SIMPLE,
			TEXTURE_POINT_LIGHT,
			SKIN_TEXTURE,
			CONST_COLOR,
			COMPUTE_TEST,
			COMPUTE_MIXER,
			COMPUTE_WORLD,

			UNINITIALIZED
		};

		enum class Type
		{
			GRAPHICS,
			COMPUTE,
		};


	public:
		ShaderObject(ShaderObject::Name shaderName, const char* const pShaderBaseFileName, ShaderObject::Type type);

		ShaderObject() = delete;
		ShaderObject(const ShaderObject&) = delete;
		ShaderObject& operator = (ShaderObject&) = delete;
		virtual ~ShaderObject() = default;

		void SetActive() const;
		GLint GetLocation(const char* const pUniformName) const;

		void Dispatch(unsigned int groupsize_x, unsigned int groupsize_y, unsigned int groupsize_z);

	private:
		bool privCreateShader(GLuint& programObject, const char* const pShaderBaseFileName, ShaderObject::Type shaderType);
		bool privLoadNCompile(GLuint& shaderObject, const char* const pShaderFileName, GLenum shader_type);

	public:
		Name   name;
		Type   type;
		GLuint programObject;

	};
}

#endif

// ---  End of File ---
