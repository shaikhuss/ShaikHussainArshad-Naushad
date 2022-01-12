//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include "CameraLink.h"

namespace Azul
{
	class Camera;

	class CameraNode : public CameraLink
	{
	public:
		CameraNode();
		~CameraNode();
		void set(Camera *pCamera);

	public:
		Camera *poCamera;

	};

}

#endif

// --- End of File ---
