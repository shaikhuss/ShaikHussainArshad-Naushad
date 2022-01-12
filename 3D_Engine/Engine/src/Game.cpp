//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#include "sb7.h"
#include "GameMan.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "ShaderObject.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "PyramidModel.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "TextureMan.h"
#include "InputMan.h"
#include "InputTest.h"
#include "Camera.h"
#include "GameObjectMan.h"
#include "GameObjectAnim.h"
#include "ModelMan.h"
#include "ShaderMan.h"
#include "BoundingSphereGameObject.h"
#include "CameraMan.h"
#include "CameraModel.h"
#include "CameraDemoInput.h"
#include "AnimTime.h"
#include "AnimTimer.h"
#include "VectApp.h"
#include "QuatApp.h"
#include "Anim.h"
#include "GraphicsDebugMessage.h"
#include "TimerController.h"
#include "AnimController.h"
#include "Clip.h"
#include "ImageMan.h"
#include "TeddyModel.h"
#include "HumanoidModel.h"
#include "GraphicsObject_SkinTexture.h"
#include "SSBO.h"
#include "GameObjectRigid.h"
#include "GraphicsObject_Sprite.h"
#include "SpriteModel.h"
#include "GameObject2D.h"
#include "AnimTransition.h"
#include "AnimManager.h"
#include "TransitionManager.h"
#include <SpuModel.h>
#include <SimpleGameObject.h>
namespace Azul
{
	//-----------------------------------------------------------------------------
	//  Game::Game()
	//		Game Engine Constructor
	//-----------------------------------------------------------------------------
	Game::Game(const char *const pWindowName, const int Width, const int Height)
		:Engine(pWindowName, Width, Height)
	{
		assert(pWindowName);

		this->globalTimer.Tic();
		this->intervalTimer.Tic();
	}

	//-----------------------------------------------------------------------------
	// Game::Initialize()
	//		Allows the engine to perform any initialization it needs to before 
	//      starting to run.  This is where it can query for any required services 
	//      and load any non-graphic related content. 
	//-----------------------------------------------------------------------------
	void Game::Initialize()
	{

	}


	//-----------------------------------------------------------------------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//-----------------------------------------------------------------------------
	void Game::LoadContent()
	{

		// Start the managers
		CameraMan::Create();
		ModelMan::Create();
		ShaderMan::Create();
		TextureMan::Create();
		GameObjectMan::Create();
		CameraMan::Create();
		InputMan::Create();
		ImageMan::Create();
		AnimManager::Create();
		
		
		
		//Camera setup

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 3D perspective Camera
		//---------------------------------------------------------------------------------------------------------

		Camera *pCam0 = new Camera(Camera::Type::PERSPECTIVE_3D);
		pCam0->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
		pCam0->setPerspective(35.0f, float(pCam0->getScreenWidth()) / float(pCam0->getScreenHeight()), 1.0f, 20000.0f);
		pCam0->setOrientAndPosition(Vect(0.0f, 0.0f, 1.0f), Vect(0.0f, 0.0f, 500.0f), Vect(2000.0f, 0.0f, 0.0f));
		pCam0->updateCamera();
		CameraMan::Add(Camera::Name::CAMERA_0, pCam0);
		CameraMan::SetCurrent(Camera::Name::CAMERA_0, Camera::Type::PERSPECTIVE_3D);

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 2D orthographic Camera
		//---------------------------------------------------------------------------------------------------------
		Camera *pCam2D = new Camera(Camera::Type::ORTHOGRAPHIC_2D);

		pCam2D->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
		pCam2D->setOrthographic((float)-pCam2D->getScreenWidth() / 2.0f, (float)pCam2D->getScreenWidth() / 2.0f,
								(float)-pCam2D->getScreenHeight() / 2.0f, (float)pCam2D->getScreenHeight() / 2.0f,
								1.0f, 1000.0f);
		pCam2D->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, -1.0f), Vect(0.0f, 0.0f, 2.0f));

		//Holder for the current 2D  cameras
		CameraMan::Add(Camera::Name::CAMERA_1, pCam2D);
		CameraMan::SetCurrent(Camera::Name::CAMERA_1, Camera::Type::ORTHOGRAPHIC_2D);

		// Load the model
		SpriteModel *pSpriteModel = new SpriteModel("SpriteModel.azul");
		assert(pSpriteModel);
		ModelMan::Add(pSpriteModel);

		TeddyModel* pTeddyModel = new TeddyModel("TeddyModel.azul");
		assert(pTeddyModel);
		pTeddyModel->name = "TeddyModel";
		ModelMan::AddTeddy(pTeddyModel);
		
		HumanoidModel* pHumanoidModel = new HumanoidModel("HumanoidModel.azul");
		assert(pHumanoidModel);
		pHumanoidModel->name = "HumanoidModel";
		ModelMan::AddHumanoid(pHumanoidModel);


		// Create/Load Shader 
		ShaderObject *pShaderObject_sprite = new ShaderObject(ShaderObject::Name::SPRITE, "spriteRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_sprite);
		ShaderMan::Add(pShaderObject_sprite);

		ShaderObject *pShaderObject_skinTexture = new ShaderObject(ShaderObject::Name::SKIN_TEXTURE, "skinTextureRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_skinTexture);
		ShaderMan::Add(pShaderObject_skinTexture);

		ShaderObject *pShaderObject_mixer = new ShaderObject(ShaderObject::Name::COMPUTE_MIXER, "computeMixer", ShaderObject::Type::COMPUTE);
		assert(pShaderObject_mixer);
		ShaderMan::Add(pShaderObject_mixer);
		                                                                
		ShaderObject *pShaderObject_world = new ShaderObject(ShaderObject::Name::COMPUTE_WORLD, "computeWorld", ShaderObject::Type::COMPUTE);
		assert(pShaderObject_world);
		ShaderMan::Add(pShaderObject_world);

		// Textures
		TextureMan::Add("Rocks.tga", Texture::Name::ROCKS);
		TextureMan::Add("Stone.tga", Texture::Name::STONES);
		TextureMan::Add("RedBrick.tga", Texture::Name::RED_BRICK);
		TextureMan::Add("Duckweed.tga", Texture::Name::DUCKWEED);
		TextureMan::Add("Consolas36pt.tga", Texture::Name::INVADERS);
		TextureMan::Add("TeddyTexNORLE.tga", Texture::Name::TEDDY);
		
		//Skin textures
		GraphicsObject_SkinTexture* pHumanSkinGraphicsObject = new GraphicsObject_SkinTexture(
			pHumanoidModel,
			pShaderObject_skinTexture,
			Texture::Name::DUCKWEED);

		GameObjectRigid* pHumanSkinObject = new GameObjectRigid(pHumanSkinGraphicsObject);
		GameObjectMan::Add(pHumanSkinObject, GameObjectMan::GetRoot());
		pHumanSkinObject->SetName("HumanSkin Object");

		GraphicsObject_SkinTexture* pSkinGraphicsObject = new GraphicsObject_SkinTexture(
			pTeddyModel,
			pShaderObject_skinTexture,
			Texture::Name::TEDDY);

		GameObjectRigid* pSkinObject = new GameObjectRigid(pSkinGraphicsObject);
		GameObjectMan::Add(pSkinObject, GameObjectMan::GetRoot());
		pSkinObject->SetName("Skin Object");


		
		
		// Anim Controller
		AnimTime delta;
		
		delta = 0.25f * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
		AnimController* pAnimControllerB = new AnimController(delta, pHumanSkinGraphicsObject, "humanoid.spu");
		AnimManager::Add(pAnimControllerB);
		delta = 0.25f * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
		AnimController* pAnimControllerA = new AnimController(delta, pSkinGraphicsObject, "teddy.spu");
		AnimManager::Add2(pAnimControllerA);
		
		

		//2D Numbers
		
		Image* pImageGreen = new Image(Image::Name::Alien_Green, Texture::Name::INVADERS, Rect(1.0f, 48.0f, 21.0f, 27.0f));
		
		assert(pImageGreen);
		ImageMan::Add(pImageGreen);

		GraphicsObject_Sprite* pGraphics_Sprite = new GraphicsObject_Sprite(pSpriteModel, pShaderObject_sprite, pImageGreen, Rect(455, 155, 250, 250));
		GameObject2D* pA1 = new GameObject2D(pGraphics_Sprite);


		pA1->posX = 1710.0f;
		pA1->posY = 1000.0f;
		pA1->scaleX = 0.25f;
		pA1->scaleY = 0.25f;
		pA1->SetName("0");
		GameObjectMan::Add(pA1, GameObjectMan::GetRoot());



		Image* pImageRed = new Image(Image::Name::Alien_Red, Texture::Name::INVADERS, Rect(22.0f, 48.0f, 21.0f, 27.0f));
		
		assert(pImageRed);
		ImageMan::Add(pImageRed);

		GraphicsObject_Sprite* pGraphics_Sprite2 = new GraphicsObject_Sprite(pSpriteModel, pShaderObject_sprite, pImageRed, Rect(455, 155, 250, 250));
		GameObject2D* pA2 = new GameObject2D(pGraphics_Sprite2);


		pA2->posX = 1800.0f;
		pA2->posY = 1000;
		pA2->scaleX = 0.25f;
		pA2->scaleY = 0.25f;
		pA2->SetName("1");
		GameObjectMan::Add(pA2, GameObjectMan::GetRoot());




		Image* pImageBlue = new Image(Image::Name::Alien_Blue, Texture::Name::INVADERS, Rect(44.0f, 48.0f, 21.0f, 27.0f));
		
		assert(pImageBlue);
		ImageMan::Add(pImageBlue);

		GraphicsObject_Sprite* pGraphics_Sprite3 = new GraphicsObject_Sprite(pSpriteModel, pShaderObject_sprite, pImageBlue, Rect(455, 155, 250, 250));
		GameObject2D* pA3 = new GameObject2D(pGraphics_Sprite3);


		pA3->posX = 1890.0f;
		pA3->posY = 1000;
		pA3->scaleX = 0.25f;
		pA3->scaleY = 0.25f;
		pA3->SetName("2");
		GameObjectMan::Add(pA3, GameObjectMan::GetRoot());

		// ----- Spu Model ------------
		//3D RigidModel
		SpuModel* pBuggyModel = new SpuModel("buggy.spu");
		assert(pBuggyModel);
		ModelMan::Add(pBuggyModel);

		SpuModel* pSpaceModel = new SpuModel("space_frigate.spu");
		assert(pSpaceModel);
		ModelMan::Add(pSpaceModel);

		ShaderObject* pShaderObject_texture = new ShaderObject(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_texture);
		ShaderMan::Add(pShaderObject_texture);

		GraphicsObject* pGraphicsObj = nullptr;
		Vect Spucolor(0.0f, 0.0f, 0.0f, 0.0f);
		Vect Spupos(2.0f, 2.0f, 2.0f);

		//Buggy
		pGraphicsObj = new GraphicsObject_FlatTexture(pBuggyModel, pShaderObject_texture, Texture::Name::BUGGY);
		SimpleGameObject* pGameObjBuggySpu = nullptr;
		pGameObjBuggySpu = new SimpleGameObject(pGraphicsObj);
		pGameObjBuggySpu->SetName("Buggy");
		pGameObjBuggySpu->SetScale(0.5f, 0.5f, 0.5f);
		pGameObjBuggySpu->SetPos(100.3f, -800.5f, 900.5f);
		pGameObjBuggySpu->setMove(SimpleGameObject::Rot_X);
		GameObjectMan::Add(pGameObjBuggySpu, GameObjectMan::GetRoot());


		//SpaceFrigate

		pGraphicsObj = new GraphicsObject_FlatTexture(pSpaceModel, pShaderObject_texture, Texture::Name::SPACE);
		SimpleGameObject* pGameObjSpaceSpu;
		pGameObjSpaceSpu = new SimpleGameObject(pGraphicsObj);
		pGameObjSpaceSpu->SetName("Space");
		pGameObjSpaceSpu->SetScale(4.5f, 4.5f, 4.5f);
		pGameObjSpaceSpu->SetPos(500.2f, 600.0f, 300.5f);
		pGameObjSpaceSpu->setMove(SimpleGameObject::Rot_X);
		GameObjectMan::Add(pGameObjSpaceSpu, GameObjectMan::GetRoot());

		
	}

	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------
	void Game::Update(float)
	{
		Vect obj(0.0f, 0.0f, 0.0f);
		
		AnimController* pAnimControllerB = AnimManager::getAnimController();
		AnimController* pAnimControllerA = AnimManager::getAnimController2();

		//Trace::out("\n-----START ------\n");
		Anim* pAnim = pAnimControllerA->poAnim;
		Anim* pAnim2 = pAnimControllerB->poAnim;
		Clip* pClip = pAnim->getClip();
		Clip* pClip2 = pAnim->getClip2();
		Clip* pClip3 = pAnim2->getClip();
		Clip* pClip4 = pAnim2->getClip2();
		AnimTime max = pClip->GetTotalTime();

		AnimTime max2 = pClip3->GetTotalTime();
		// ------------------------------------------------
		// Camera update
		// ------------------------------------------------

		Camera *pCam3D = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		pCam3D->updateCamera();

		Camera *pCam2D = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		pCam2D->updateCamera();
		AnimTransition* pAnimTransition = TransitionManager::getAnimTransition();
		AnimTransition* pAnimTransition2 = TransitionManager::getAnimTransition2();
		// ------------------------------------------------
		// Animate ME
		// ------------------------------------------------
		Keyboard* key = InputMan::GetKeyboard();
		//Key to move Camera
		if (key->GetKeyState(Keyboard::KEY_ARROW_RIGHT))
		{

			Vect pos;
			Vect tar;
			Vect up;
			Vect upNorm;
			Vect forwardNorm;
			Vect rightNorm;

			pCam3D->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm
			tar = obj;

			Matrix Trans(Matrix::Trans::XYZ, tar);
			Matrix NegTrans(Matrix::Trans::XYZ, -tar);

			Matrix Rot;
			Rot.set(Matrix::Rot::AxisAngle, upNorm, +0.03f);

			Matrix M = NegTrans * Rot * Trans;

			up = up * M;
			pos = pos * M;
			tar = tar * M;

			pCam3D->SetHelper(up, tar, pos);
		}

		if (key->GetKeyState(Keyboard::KEY_ARROW_LEFT))
		{

			Vect pos;
			Vect tar;
			Vect up;
			Vect upNorm;
			Vect forwardNorm;
			Vect rightNorm;

			pCam3D->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm

			tar = obj;

			Matrix Trans(Matrix::Trans::XYZ, tar);
			Matrix NegTrans(Matrix::Trans::XYZ, -tar);

			Matrix Rot;
			Rot.set(Matrix::Rot::AxisAngle, upNorm, -0.03f);

			Matrix M = NegTrans * Rot * Trans;

			up = up * M;
			pos = pos * M;
			tar = tar * M;

			pCam3D->SetHelper(up, tar, pos);
		}

		if (key->GetKeyState(Keyboard::KEY_ARROW_DOWN))
		{
			Vect pos;
			Vect tar;
			Vect up;
			Vect upNorm;
			Vect forwardNorm;
			Vect rightNorm;

			pCam3D->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			tar = obj;

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm

			Matrix Trans(Matrix::Trans::XYZ, tar);
			Matrix NegTrans(Matrix::Trans::XYZ, -tar);
			Matrix Rot;
			Rot.set(Matrix::Rot::AxisAngle, rightNorm, 0.03f);

			Matrix M = NegTrans * Rot * Trans;

			up = up * M;
			pos = pos * M;
			tar = tar * M;

			pCam3D->SetHelper(up, tar, pos);
		}

		if (key->GetKeyState(Keyboard::KEY_ARROW_UP))
		{
			Vect pos;
			Vect tar;
			Vect up;
			Vect upNorm;
			Vect forwardNorm;
			Vect rightNorm;

			pCam3D->GetHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

			// OK, now 3 points... pos, tar, up
			//     now 3 normals... upNorm, forwardNorm, rightNorm
			tar = obj;

			Matrix Trans(Matrix::Trans::XYZ, tar);
			Matrix NegTrans(Matrix::Trans::XYZ, -tar);
			Matrix Rot;
			Rot.set(Matrix::Rot::AxisAngle, rightNorm, -0.03f);

			Matrix M = NegTrans * Rot * Trans;

			up = up * M;
			pos = pos * M;
			tar = tar * M;

			pCam3D->SetHelper(up, tar, pos);
		}



		//Key for transition

		if (key->GetKeyState(Keyboard::KEY_T))
		{
			pAnimTransition->StartTransition();
			pAnim->setClip(pClip2);
		}
		if (key->GetKeyState(Keyboard::KEY_H))
		{
			pAnimTransition2->StartTransition();
			pAnim2->setClip(pClip4);
		}
		
		//Updates
		pAnimControllerA->Update(pClip,max);  // Mixer Run
		pAnimControllerB->Update(pClip3,max2);  // Mixer Idle
		pAnimTransition->Update();   // Transition
		pAnimTransition2->Update();
		const char* k = nullptr;
		// ------------------------------------------------
		// GameObjects update
		// ------------------------------------------------
		GameObjectMan::Update(k,this->globalTimer.Toc());

	}

	//-----------------------------------------------------------------------------
	// Game::Draw()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//-----------------------------------------------------------------------------
	void Game::Draw()
	{
		GameObjectMan::Draw();
	}


	//-----------------------------------------------------------------------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//-----------------------------------------------------------------------------
	void Game::UnLoadContent()
	{
		
		TextureMan::Destroy();
		InputMan::Destroy();
		GameObjectMan::Destroy();
		ModelMan::Destroy();
		ShaderMan::Destroy();
		CameraMan::Destroy();
		ImageMan::Destroy();
		AnimManager::Destroy();
		TransitionManager::Destroy();
		
	}

	//------------------------------------------------------------------
	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	//------------------------------------------------------------------
	void Game::ClearBufferFunc()
	{
		const GLfloat grey[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		const GLfloat one = 1.0f;

		glViewport(0, 0, info.windowWidth, info.windowHeight);
		glClearBufferfv(GL_COLOR, 0, grey);
		glClearBufferfv(GL_DEPTH, 0, &one);
	}

}

// --- End of File ---
