#include "textureImporter.h"
#include "stb_image.h"

namespace engine
{
	unsigned char* textureImporter::loadTexture(const char* filepath, int& textureWidth, int& textureHeight, int& nrChannels)
	{
		stbi_set_flip_vertically_on_load(true);
		return stbi_load(filepath, &textureWidth, &textureHeight, &nrChannels, 0);
	}
	void textureImporter::unloadTexture(unsigned char* data)
	{
		stbi_image_free(data);
	}
}