#pragma once
namespace engine
{

	struct texture
	{
		unsigned int ID;
		float width;
		float height;
	};

	static class textureImporter
	{
	public:
		static texture loadTexture(const char* filepath);
	};
}
