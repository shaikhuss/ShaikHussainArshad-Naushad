//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef IMAGE_LINK_H
#define IMAGE_LINK_H

namespace Azul
{
	class ImageLink
	{
	public:
		ImageLink();
		ImageLink(const ImageLink &) = default;
		ImageLink &operator = (const ImageLink &) = default;
		virtual ~ImageLink();

	// data:
		ImageLink *next;
		ImageLink *prev;
	};
}

#endif

//--- End of File ---
