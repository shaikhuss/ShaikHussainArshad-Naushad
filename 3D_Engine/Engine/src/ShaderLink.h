//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef SHADER_LINK_H
#define SHADER_LINK_H

namespace Azul
{
	class ShaderLink
	{
	public:
		ShaderLink();
		ShaderLink(const ShaderLink &) = default;
		ShaderLink &operator = (const ShaderLink &) = default;
		virtual ~ShaderLink();

	// data:
		ShaderLink* next;
		ShaderLink* prev;
	};
}

#endif

// ---  End of File ---
