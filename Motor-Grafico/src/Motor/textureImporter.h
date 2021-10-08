#pragma once
namespace engine
{
	static class textureImporter
	{
	public:
		static unsigned char* loadTexture(const char* filepath, int& textureWidth, int& textureHeight, int& nrChannels);
		static void unloadTexture(unsigned char* data);
	};
}
