//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SPU_MODEL_H
#define SPU_MODEL_H

#include "Model.h"

namespace Azul
{
	class SpuModel : public Model
	{
	public:
		SpuModel(const char* const pModelFileName);

		SpuModel() = delete;
		SpuModel(const SpuModel&) = delete;
		SpuModel& operator = (SpuModel&) = delete;
		virtual ~SpuModel();

	private:
		virtual void privCreateVAO(const char* const pModelFileName) override;

		// Data

	};
}

#endif