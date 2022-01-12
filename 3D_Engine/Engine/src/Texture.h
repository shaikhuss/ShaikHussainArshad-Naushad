//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------

#ifndef TEXTURE_H
#define TEXTURE_H

#include "sb7.h"
#include "TextureLink.h"

namespace Azul
{
	class Texture : public TextureLink
	{
	public:
		static const unsigned int ASSET_NAME_SIZE = 64;

		enum class Name
		{
			STONES,
			RED_BRICK,
			DUCKWEED,
			ROCKS,
			INVADERS,
			
			TEDDY,
			POLARBEAR,
			HOTPINK,
			WARBEAR,
			BUGGY,
			ASTRO,
			SPACE,
			ROBO,
			CUSTOM,
			NUM,
			NOT_INITIALIZED
		};

	public:
		Texture();
		Texture(const Texture &) = default;
		Texture &operator = (const Texture &) = default;
		virtual ~Texture() = default;

		void set(const char *const _assetName,
			Texture::Name _name,
			GLuint _TextureID,
			GLenum minFilter,
			GLenum magFilter,
			GLenum horizWrapMode,
			GLenum vertWrapMode,
			int _width,
			int _height);

	private:
		char assetName[Texture::ASSET_NAME_SIZE];

	public:
		Texture::Name name;
		GLuint textureID;
		GLenum minFilter;
		GLenum magFilter;
		GLenum horizWrapMode;
		GLenum vertWrapMode;
		int width;
		int height;
	};
}

#endif

// --- End of File ---
