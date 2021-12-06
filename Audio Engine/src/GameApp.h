//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_APP_H
#define GAME_APP_H

class GameApp
{
public:
	GameApp() noexcept;
	GameApp(const GameApp&) = delete;
	GameApp(GameApp&&) = delete;
	GameApp& operator = (const GameApp&) = delete;
	GameApp& operator = (GameApp&&) = delete;
	~GameApp();

	static void LoadDemo(int width, int height);
	static void UpdateDemo();
	static void DrawDemo();
	
private:
	static GameApp *privGameApp() noexcept;

	Camera* pCam3D;
	GraphicsObject_TextureLight* pSpaceFrigateLight;
	Texture* pSpaceFrigateTexture;
	Model* pModelSpaceFrigate;
	ShaderObject* pShaderObject_textureLight;
};

#endif

// End of File 

