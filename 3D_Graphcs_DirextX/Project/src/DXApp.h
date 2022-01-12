#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "Skybox.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include "ShaderColorLight.h"
#include "ShaderTextureLight.h"
#include "ShaderTextureLight3Point.h"
#include "ShaderTextureLightMultipleSpot.h"
#include "GraphicObject_Color.h"
#include "GraphicObject_ColorLight.h"
#include "GraphicObject_Texture.h"
#include "GraphicObject_TextureLight.h"
#include "Terrain.h"
class Model;
class Texture;
class FlatPlane;
class TerrainModel;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;
	Matrix mWorld2;
	Matrix mWorldChopper;
	Matrix mWorldWolf;
	Matrix mWorldTower;
	Matrix mWorldTower2;
	Matrix mWorldTower3;
	Matrix mWorldTower4;
	Matrix mWorldMissile;
	Matrix mWorldCar;
	Matrix mWorldCastle;
	Matrix mWorldCube;
	Matrix mWorldPyramid;
	Matrix mWorldPyramid2;
	Matrix mWorldPyramid3;
	Matrix mWorldPyramid4;
	Matrix mWorldSphere;

	Matrix mWorldLight;
	Vect pointLight1;
	Vect pointLight2;
	Vect pointLight4;
	Vect pointLight3;
	Skybox* pSkybox;

	Model* pModelTower;
	Model* pModelMissile;
	Model* pModelChopper;
	Model* pModelWolf;
	Model* pModelCar;
	Model* pModelCastle;
	Model* pCube;
	Model* pPyramidModel;
	Model* pSphereModel;
	
	Texture* mTexCube;
	Texture* mTexChopper;
	Texture* mTexMissile;
	Texture* mTexWolf;
	Texture* mTexTower;
	Texture* mTexPlane;
	Texture* mTexSky;
	Texture* mTexCar;
	Texture* mTexWheel;
	Texture* mTexCottage1;

	GraphicObject_TextureLight* colorLightChopper;
	GraphicObject_TextureLight* colorLightWolf;
	GraphicObject_TextureLight* texLightTower;
	GraphicObject_TextureLight* texLightTower2;
	GraphicObject_TextureLight* texLightTower3;
	GraphicObject_TextureLight* texLightTower4;
	GraphicObject_TextureLight* texLightMissile;
	GraphicObject_TextureLight* texLightCastle;
	GraphicObject_TextureLight* Point3LightCar;
	GraphicObject_TextureLight* GCube;
	GraphicObject_TextureLight* pPyramid;
	GraphicObject_TextureLight* pPyramid2;
	GraphicObject_TextureLight* pPyramid3;
	GraphicObject_TextureLight* pPyramid4;
	GraphicObject_ColorLight* GSphere;

	FlatPlane* pWater;
	Terrain* pTerrain;
	Matrix mPlaneMat;
	Matrix mBackPlane;

	ShaderTexture* pTextureShader;
	ShaderColor* pShaderColor;
	ShaderColorLight* pShaderColLight;
	ShaderTextureLight* pShaderTexLight;
	
	// gimmicky mouse control
	Vect MousePos;
	float mTheta;
	float mPhi;
	float mRadius;

public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp