//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "Camera.h"
#include "CameraNode.h"

namespace Azul
{
	// Singleton
	class CameraMan
	{
	public:
		CameraMan(const CameraMan &) = delete;
		CameraMan &operator = (const CameraMan &) = delete;
		~CameraMan() = default;

		static void Add(Camera::Name name, Camera *pCamera);
		static Camera *Find(Camera::Name name);

		static void SetCurrent(Camera::Name name, Camera::Type type);
		static Camera *GetCurrent(Camera::Type type);

		static void Create();
		static void Destroy();

	private:  // methods

		static CameraMan *privGetInstance();
		CameraMan();
		void privAddToFront(CameraLink *node, CameraLink *&head);
		void privRemove(CameraLink *pNode, CameraLink *&poHead);

	private:  // add

		CameraLink *poActive;
		Camera *pCamOrthographic;
		Camera *pCamPerspective;

	};

}

#endif

// --- End of File ---
