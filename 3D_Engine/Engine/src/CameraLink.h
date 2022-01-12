//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef CAMERA_LINK_H
#define CAMERA_LINK_H

namespace Azul
{
	class CameraLink
	{
	public:
		CameraLink();
		CameraLink(const CameraLink &) = default;
		CameraLink &operator = (const CameraLink &) = default;
		virtual ~CameraLink() = default;

	// Data:7
		CameraLink *next;
		CameraLink *prev;
	};
}

#endif

// --- End of File ---