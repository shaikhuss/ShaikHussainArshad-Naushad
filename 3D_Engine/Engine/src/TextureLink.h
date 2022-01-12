//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef TEXTURE_LINK_H
#define TEXTURE_LINK_H

namespace Azul
{
	class TextureLink
	{
	public:
		TextureLink();
		TextureLink(const TextureLink &) = default;
		TextureLink &operator = (const TextureLink &) = default;

		virtual ~TextureLink();

	// Data:
		TextureLink *next;
		TextureLink *prev;
	};
}
#endif

// --- End of File ---
