#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;


class TerrainModel
{

private:
	Model* pModTerrain;

public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, int RepeatU, int RepeatV);

	int TexelIndex(int side, int i, int j) const;

	void Render(ID3D11DeviceContext* context);
	~TerrainModel();
};




#endif _TerrainModel