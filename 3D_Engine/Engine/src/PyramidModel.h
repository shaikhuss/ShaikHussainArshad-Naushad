//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PYRAMID_MODEL_H
#define PYRAMID_MODEL_H

#include "Model.h"

namespace Azul
{
	class PyramidModel : public Model
	{
	public:
		PyramidModel()
		{
			pModel = nullptr;
			flag = false;
		}
		PyramidModel(const char* const modelFileName);
		virtual ~PyramidModel();
		// tells the compiler do not create or allow it to be used, c++11
		static PyramidModel* privGetInstance()
		{
			static PyramidModel instance;

			return &instance;
		}
		static void Add(PyramidModel* pController)
		{
			PyramidModel* pPyramid = PyramidModel::privGetInstance();
			assert(pPyramid);
			pPyramid->flag = true;
			pPyramid->pModel = pController;
		}
		static void SetFlag()
		{
			PyramidModel* pPyramid = PyramidModel::privGetInstance();
			assert(pPyramid);
			pPyramid->flag = false;
		}
		static PyramidModel* getPyramid()
		{
			// Get the instance to the manager
			PyramidModel* pPyramid = PyramidModel::privGetInstance();
			assert(pPyramid);

			assert(pPyramid->pModel);
			return pPyramid->pModel;
		}
		static bool getFlag()
		{
			// Get the instance to the manager
			PyramidModel* pPyramid = PyramidModel::privGetInstance();
			assert(pPyramid);

			assert(pPyramid->flag);

			return false;
		}
		PyramidModel(const PyramidModel&) = delete;
		PyramidModel& operator=(const PyramidModel& other) = delete;
		PyramidModel* pModel;
		bool flag;

	private:
		void privCreateVAO(const char* const modelFileName) override;

	};
}

#endif

// --- End of File ---
