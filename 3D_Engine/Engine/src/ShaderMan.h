//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef SHADER_MAN_H
#define SHADER_MAN_H

#include "ShaderObject.h"

namespace Azul
{
	class ShaderMan
	{
	public:
		static void Add(ShaderObject* pShader);
		static void Create();
		static void Destroy();
		static ShaderObject *Find(ShaderObject::Name name);

		ShaderMan(const ShaderMan &) = delete;
		ShaderMan &operator = (const ShaderMan &) = delete;
		~ShaderMan() = default;

	private:  // methods

		static ShaderMan* privGetInstance();
		ShaderMan();

		void privAddToFront(ShaderObject* node, ShaderObject*& head);
		void privRemove(ShaderObject* node, ShaderObject*& head);

	private:  // add

		ShaderObject *pActive;
	};

}

#endif

// ---  End of File ---
