//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef IMAGE_H
#define IMAGE_H

#include "Rect.h"
#include "Texture.h"
#include "ImageLink.h"

namespace Azul
{
	class Image : public ImageLink
	{
	public:
		enum class Name
		{
			Alien_Blue,
			Alien_Green,
			Alien_Red,
			Stitch,
			Not_Initialized,
		};

	public:
		// public methods: -------------------------------------------------------------
		Image();
		Image(const Image &) = default;
		Image &operator = (const Image &) = default;
		virtual	~Image() = default;

		Image(Image::Name imageName, Texture::Name textName, Rect rect);
		Image(Image::Name imageName, Texture *pTexture, Rect rect);

		void Set(Image::Name imageName, Texture::Name textName, Rect rect);
		void Set(Image::Name imageName, Texture *pTexture, Rect rect);

	public:
		// data: -----------------------------------------------------------------------
		Image::Name	    imageName;
		Texture         *pText;
		Rect			imageRect;
	};

}


#endif

//--- End of File ---
