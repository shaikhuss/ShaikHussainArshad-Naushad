//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include "Model.h"

namespace Azul
{
	class CameraModel : public Model
	{
	public:
		CameraModel(const char *const modelFileName);
		virtual ~CameraModel();

		void update();

		// tells the compiler do not create or allow it to be used, c++11
		CameraModel() = delete;
		CameraModel(const CameraModel &) = delete;
		CameraModel &operator=(const CameraModel &other) = delete;

	private:
		void privCreateVAO(const char *const modelFileName) override;

	};

}

#endif

// --- End of File ---
