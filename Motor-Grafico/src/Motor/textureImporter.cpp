#include "textureImporter.h"
#include "stb_image.h"
#include "glew.h"
#include "glfw3.h"
#include <iostream>

namespace engine
{
	textureData textureImporter::loadTexture(const char* filepath)
	{
		unsigned int newTextureID;
		int textureWidth;
		int textureHeight;
		int nrChannels;
		glGenTextures(1, &newTextureID);
		glBindTexture(GL_TEXTURE_2D, newTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filepath, &textureWidth, &textureHeight, &nrChannels, 0);
		if (data)
		{
			int channelType = GL_RGB;
			switch (nrChannels)
			{
			case 1:
				channelType = GL_R;
				break;
			case 2:
				channelType = GL_RG;
				break;
			case 3:
				channelType = GL_RGB;
				break;
			case 4:
				channelType = GL_RGBA;
				break;
			default:
				break;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, channelType, textureWidth, textureHeight, 0, channelType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		textureData tex = { newTextureID, textureWidth, textureHeight };
		return tex;
	}
}