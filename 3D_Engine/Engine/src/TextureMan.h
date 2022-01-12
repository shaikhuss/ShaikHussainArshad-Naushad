//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef TEXTURE_MAN_H
#define TEXTURE_MAN_H

#include "TextureLink.h"
#include "Texture.h"

namespace Azul
{
	class TextureMan
	{
	public:
		TextureMan(const TextureMan &) = delete;
		TextureMan &operator = (const TextureMan &) = delete;
		~TextureMan() = default;

		static void Add(const char *const _assetName, const Texture::Name _name);
		static void DeleteAllTextures();
		static GLuint FindID(const Texture::Name _name);
		static Texture *Find(const Texture::Name _name);
		static void Destroy();
		static void Create();
		static void AddSpu(const char* const _assetName, const Texture::Name _name);
		bool privLoadSpuTGATexture(unsigned char* szFileName, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode);
		GLbyte* gltReadSpuTGABits(unsigned char* szFileName, GLint* iWidth, GLint* iHeight, GLint* iComponents, GLenum* eFormat);

		void privLoadSpuTexture(unsigned char* _assetName, GLuint*& textureID);

	private:
		// methods
		TextureMan();
		static TextureMan *privGetInstance();

		// helper private methods
		void privLoadTexture(const char *const _assetName, GLuint *&textureID, int &width, int &height);
		bool privLoadTGATexture(const char *szFileName, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode, int &width, int &height);
		void privAddToFront(TextureLink *node, TextureLink *&head);
		void privRemove(TextureLink *pNode, TextureLink *&poHead);
		GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

	private:

		TextureLink *pActive;
	};
}

#endif

// --- End of File ---
