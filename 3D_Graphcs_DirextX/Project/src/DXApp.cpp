#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"

DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	CHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

void DXApp::InitDemo()
{
	// Initialize the world matrices
	mWorld2 = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 0, 150, 0);
	mWorldSphere = Matrix(SCALE, 2.5, 2.5, 2.5) * Matrix(TRANS, 110, 30, 0);
	mWorldCube = Matrix(SCALE, 5, 5, 5) * Matrix(TRANS, -110, 38, 0);
	mWorldPyramid = Matrix(SCALE, 25, 25, 25) * Matrix(TRANS, -110, 85, 0);
	mWorldPyramid2 = Matrix(SCALE, 25, 25, 25) * Matrix(TRANS, 110, 80, 0);
	mWorldPyramid3 = Matrix(SCALE, 25, 25, 25) * Matrix(TRANS, 0, 80, 110);
	mWorldPyramid4 = Matrix(SCALE, 25, 25, 25) * Matrix(TRANS, 0, 80, -110);
	mPlaneMat = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 0, 15, 0);
	mBackPlane = Matrix(TRANS, 0, 25, 0);
	mWorldChopper = Matrix(SCALE, 5, 5, 5) * Matrix(ROT_X, -1.5f) * Matrix(ROT_Y, 2.35f) * Matrix(TRANS, 105, 135, 110);
	mWorldWolf = Matrix(SCALE, .2, .2, .2) * Matrix(ROT_X, -0.50f) * Matrix(TRANS, 0, 99, 0);
	mWorldMissile = Matrix(SCALE, 2, 2, 2) * Matrix(ROT_Y, -1.5f) * Matrix(ROT_Y, -0.85f) * Matrix(TRANS, 45, 125, 50);
	mWorldTower = Matrix(SCALE, 5, 5, 5) * Matrix(ROT_X, -1.6f) * Matrix(TRANS, -110, 35, 0);
	mWorldTower2 = Matrix(SCALE, 5, 5, 5) * Matrix(ROT_X, -1.6f) * Matrix(TRANS, 110, 30, 0);
	mWorldTower3 = Matrix(SCALE, 5, 5, 5) * Matrix(ROT_X, -1.6f) * Matrix(TRANS, 0, 30, 110);
	mWorldTower4 = Matrix(SCALE, 5, 5, 5) * Matrix(ROT_X, -1.6f) * Matrix(TRANS, 0, 30, -110);
	mWorldCar = Matrix(SCALE, .5, .5, .5) * Matrix(ROT_Y, 2.0f) * Matrix(TRANS, 55, 27, -100);
	mWorldCastle = Matrix(SCALE, 15, 5, 15) * Matrix(TRANS, 0, 30, 0);
	
	pointLight1 = Vect(145, 0, -45);
	pointLight2 = Vect(-105, 0, -25);
	pointLight3 = Vect(145, 45, -45);
	pointLight4 = Vect(-105, 45, -25);

	pShaderTexLight = new ShaderTextureLight(md3dDevice);

	//Water
	pShaderColLight = new ShaderColorLight(md3dDevice);
	//
	pShaderTexLight->SetDirectionalLightParameters(Vect(1, -1, 1).getNorm(),
		.3 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));
	
	pModelChopper = new Model(md3dDevice, "../Assets/Models/Apache.azul");
	pModelWolf = new Model(md3dDevice, "../Assets/Models/WereWolf.azul");
	pModelTower = new Model(md3dDevice, "../Assets/Models/watchtower.azul");
	pModelMissile = new Model(md3dDevice, "../Assets/Models/Rocket.azul");
	pModelCar = new Model(md3dDevice, "../Assets/Models/car.azul");
	pModelCastle = new Model(md3dDevice, "../Assets/Models/Castle.azul");

	//
	pCube = new Model(md3dDevice, Model::UnitBoxRepeatedTexture);
	pPyramidModel = new Model(md3dDevice, Model::UnitPyramidRepeatedTexture);
	pSphereModel = new Model(md3dDevice, Model::UnitSphere);

	mTexChopper = new Texture(md3dDevice, L"../Assets/Textures/Apache.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexWolf = new Texture(md3dDevice, L"../Assets/Textures/WerewolfBrown.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexTower = new Texture(md3dDevice, L"../Assets/Textures/boat.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexMissile = new Texture(md3dDevice, L"../Assets/Textures/Missile.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexCar = new Texture(md3dDevice, L"../Assets/Textures/BlackPaint.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexWheel = new Texture(md3dDevice, L"../Assets/Textures/wheel.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexCottage1 = new Texture(md3dDevice, L"../Assets/Textures/Concrete.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexPlane = new Texture(md3dDevice, L"../Assets/Textures/grass.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexSky = new Texture(md3dDevice, L"../Assets/Textures/grim.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	mTexCube = new Texture(md3dDevice, L"../Assets/Textures/CrateFace.tga");
	pTerrain = new Terrain(md3dDevice, pShaderTexLight, mTexPlane, L"../Assets/Textures/HM.tga", 1150, 30, 512, 125);
	pTerrain->SendWorldAndMaterial(mPlaneMat, Colors::White, Colors::White, Vect(1, 1, 1, 100));

	pWater = new FlatPlane(md3dDevice, 1000, 1, 1);

	pShaderColor = new ShaderColor(md3dDevice);

	colorLightChopper = new GraphicObject_TextureLight(pShaderTexLight, pModelChopper);
	colorLightChopper->SetTexture(mTexChopper);
	colorLightChopper->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	colorLightChopper->SetWorld(mWorldChopper);

	GCube = new GraphicObject_TextureLight(pShaderTexLight, pCube);
	GCube->SetTexture(mTexCube);
	GCube->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	GCube->SetWorld(mWorldCube);

	pPyramid = new GraphicObject_TextureLight(pShaderTexLight, pPyramidModel);
	pPyramid->SetTexture(mTexTower);
	pPyramid->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	pPyramid->SetWorld(mWorldPyramid);

	pPyramid2 = new GraphicObject_TextureLight(pShaderTexLight, pPyramidModel);
	pPyramid2->SetTexture(mTexTower);
	pPyramid2->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	pPyramid2->SetWorld(mWorldPyramid2);

	pPyramid3 = new GraphicObject_TextureLight(pShaderTexLight, pPyramidModel);
	pPyramid3->SetTexture(mTexTower);
	pPyramid3->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	pPyramid3->SetWorld(mWorldPyramid3);

	pPyramid4= new GraphicObject_TextureLight(pShaderTexLight, pPyramidModel);
	pPyramid4->SetTexture(mTexTower);
	pPyramid4->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	pPyramid4->SetWorld(mWorldPyramid4);

	GSphere = new GraphicObject_ColorLight(pShaderColLight, pSphereModel);
	

	colorLightWolf = new GraphicObject_TextureLight(pShaderTexLight, pModelWolf);
	colorLightWolf->SetTexture(mTexWolf);
	colorLightWolf->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	colorLightWolf->SetWorld(mWorldWolf);

	pTextureShader = new ShaderTexture(md3dDevice);

	pSkybox = new Skybox(md3dDevice, pTextureShader, mTexSky, 1000);

	texLightTower = new GraphicObject_TextureLight(pShaderTexLight, pModelTower);
	texLightTower->SetTexture(mTexTower);
	texLightTower->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	texLightTower->SetWorld(mWorldTower);

	texLightTower2 = new GraphicObject_TextureLight(pShaderTexLight, pModelTower);
	texLightTower2->SetTexture(mTexTower);
	texLightTower2->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	texLightTower2->SetWorld(mWorldTower2);

	texLightTower3 = new GraphicObject_TextureLight(pShaderTexLight, pModelTower);
	texLightTower3->SetTexture(mTexTower);
	texLightTower3->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	texLightTower3->SetWorld(mWorldTower3);

	texLightTower4 = new GraphicObject_TextureLight(pShaderTexLight, pModelTower);
	texLightTower4->SetTexture(mTexTower);
	texLightTower4->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	texLightTower4->SetWorld(mWorldTower4);

	texLightMissile = new GraphicObject_TextureLight(pShaderTexLight, pModelMissile);
	texLightMissile->SetTexture(mTexMissile);
	texLightMissile->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	texLightMissile->SetWorld(mWorldMissile);

	
	texLightCastle = new GraphicObject_TextureLight(pShaderTexLight, pModelCastle);
	texLightCastle->SetTexture(mTexCottage1);
	texLightCastle->SetMaterial(Colors::DarkGray, Colors::DarkGray, Vect(1, 1, 1, 1));
	texLightCastle->SetWorld(mWorldCastle);

	//CarLight
	Point3LightCar = new GraphicObject_TextureLight(pShaderTexLight, pModelCar);
	Point3LightCar->SetTexture(mTexCar, 0);
	Point3LightCar->SetTexture(mTexWheel, 1);
	Point3LightCar->SetTexture(mTexWheel, 2);
	Point3LightCar->SetTexture(mTexWheel, 3);
	Point3LightCar->SetTexture(mTexWheel, 4);
	Point3LightCar->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 1));
	Point3LightCar->SetWorld(mWorldCar);

	// Initialize the projection matrix
	mCam.setPerspective(45, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	// Setting buffer values
	// We cant do that yet: camera and worlmat may get updated!!!

	// Initialize gimmicky mouse control values
	mTheta = .5;
	mPhi = 3.1415f / 8;
	mRadius = 285;

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	//mWorld *= Matrix(ROT_Y, .0001f);  // Simple slow rotation about y axis
	// Build the view matrix using gimmicky trick
	Vect target = Vect(0, 0, 0, 0);
	Vect up = Vect(0, 1, 0, 0);
	//Vect pos = Vect(0, 0, -mRadius) * Matrix(ROT_Y, mTheta) * Matrix(ROT_X, mPhi);
	Vect pos = Vect(0, 0, -mRadius) * Matrix(ROT_X, mPhi) * Matrix(ROT_Y, mTheta);

	mCam.setOrientAndPosition(up, target, pos);

	mCam.updateCamera();

}

void DXApp::DrawScene()
{
	// Clear the back buffer
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	// Clear the depth stencil;
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	Vect eyepos;
	mCam.getPos(eyepos);

	pointLight1 = Vect(-150, 0, 250 * cosf(mTimer.TotalTime()));
	pointLight2 = Vect(150, 0, -250 * cosf(mTimer.TotalTime()));

	pointLight3 = Vect(-75 * cosf(mTimer.TotalTime()), 0, 250);
	pointLight4 = Vect(75 * cosf(mTimer.TotalTime()), 0, -250);

	
	pShaderColLight->SetToContext(md3dImmediateContext);
	pShaderColLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderColLight->SendLightParameters(eyepos);
	pShaderColLight->SendFogParameters(35, 500, Colors::Black);
	//
	pShaderColLight->SendWorldAndMaterial(mWorldSphere, Colors::Black, Colors::Black, Vect(1, 1, 1, 100));
	pSphereModel->Render(md3dImmediateContext);
	pShaderColLight->SendWorldAndMaterial(mBackPlane, Colors::Black, Colors::Black, Vect(1, 1, 1, 100));
	pWater->Render(md3dImmediateContext);



	pShaderTexLight->SetPointLightParameters(pointLight1, 50, .2 * Vect(20, 0, 0), .2 * Colors::Yellow, .2 * Colors::Yellow, .2 * Colors::Yellow);
	//
	pShaderTexLight->SetPointLight2Parameters(pointLight2, 50, .6 * Vect(20, 0, 0), .2 * Colors::Yellow, .2 * Colors::Yellow, .2 * Colors::Yellow);
	pShaderTexLight->SetPointLight3Parameters(pointLight3, 50, .6 * Vect(20, 0, 0), .2 * Colors::Yellow, .2 * Colors::Yellow, .2 * Colors::Yellow);
	pShaderTexLight->SetPointLight4Parameters(pointLight4, 50, .6 * Vect(20, 0, 0), .2 * Colors::Yellow, .2 * Colors::Yellow, .2 * Colors::Yellow);


	pShaderTexLight->SetSpotLightParameters(Vect(50, 50, -50), 100, .2 * Vect(1, 0, 0), .2 * Vect(0, -1, 0), 5, Colors::Beige, Colors::Beige, Colors::Beige);
	pShaderTexLight->SetToContext(md3dImmediateContext);
	pShaderTexLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTexLight->SendLightParameters(eyepos);
	pShaderTexLight->SendFogParameters(550, 1500, Colors::White);

	texLightTower->Render();
	texLightTower2->Render();
	texLightTower3->Render();
	texLightTower4->Render();
	texLightMissile->Render();
	Point3LightCar->Render();

	pPyramid->Render();
	pPyramid2->Render();
	pPyramid3->Render();
	pPyramid4->Render();

	texLightCastle->Render();

	colorLightChopper->Render();
	GCube->Render();
	colorLightWolf->Render();
	GSphere->Render();
	pTerrain->Render();

	pTextureShader->SetToContext(md3dImmediateContext);
	pTextureShader->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pSkybox->SendWorld(mWorld2);
	pSkybox->Render();

	mSwapChain->Present(0, 0);
}


DXApp::~DXApp()
{
	delete mTexChopper;
	delete mTexWolf;
	delete mTexPlane;
	delete pTerrain;
	delete pShaderColLight;

	delete pShaderColor;
	delete pTextureShader;
	delete pWater;
	delete GSphere;
	
	delete colorLightChopper;
	delete colorLightWolf;
	delete texLightTower;
	delete texLightTower2;
	delete texLightMissile;
	delete texLightCastle;

	delete Point3LightCar;
	delete GCube;
	delete pShaderTexLight;
	delete pSkybox;
	delete mTexMissile;
	delete mTexTower;
	delete mTexCar;
	delete mTexCottage1;

	delete pPyramidModel;
	delete texLightTower3;
	delete texLightTower4;
	delete pModelChopper;
	delete pModelWolf;
	delete pModelTower;
	delete pModelMissile;
	delete pModelCar;
	delete pModelCastle;
	delete pCube;
	delete pSphereModel;
	delete pPyramid;
	delete pPyramid2;
	delete pPyramid3;
	delete pPyramid4;

	delete mTexSky;
	delete mTexCube;
	delete mTexWheel;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}


void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << mspf << " (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		MousePos[x] = static_cast<float>(xval);
		MousePos[y] = static_cast<float>(yval);
	}
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		float dx = 0.01f * (MousePos[x] - xval);
		float dy = 0.01f * (MousePos[y] - yval);

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi -= dy;

		static float verticalMax = MATH_PI2 - 0.2f;

		if (mPhi > verticalMax)
			mPhi = verticalMax;
		else if (mPhi < -verticalMax)
			mPhi = -verticalMax;

	}
	MousePos[x] = static_cast<float>(xval);
	MousePos[y] = static_cast<float>(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	if (delta > 0)
	{
		mRadius -= 3;
	}
	else
	{
		mRadius += 3;
	}
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}