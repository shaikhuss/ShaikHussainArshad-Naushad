//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include "Image.h"

namespace Azul
{
	// Singleton
	class ImageMan
	{
	public:
		static void Add(Image *pModel);
		static Image* Get()
		{
			ImageMan* pImageMan = ImageMan::privGetInstance();
			assert(pImageMan);

			return pImageMan->pActive;
		}
		static void Create();
		static void Destroy();

		ImageMan(const ImageMan &) = delete;
		ImageMan &operator = (const ImageMan &) = delete;
		~ImageMan() = default;

	private:  // methods

		static ImageMan *privGetInstance();
		ImageMan();

		void privAddToFront(Image *node, Image *&head);
		void privRemove(Image *node, Image *&head);

	private:  // add

		Image *pActive;

	};
}

#endif

//--- End of File ---
