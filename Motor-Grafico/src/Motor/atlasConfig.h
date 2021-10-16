#pragma once
namespace engine
{
	class atlasCutConfig
	{
	public:
		void CutByCount(int columns, int rows, int offsetX, int offsetY, int framesAmount)
		{
			this->columns = columns;
			this->rows = rows;
			this->offsetX = offsetX;
			this->offsetY = offsetY;
			this->framesAmount = framesAmount;
			usePixelSize = false;
		}
		void CutByPixels(int spriteWidth, int spriteHeight, int offsetX, int offsetY, int framesAmount)
		{
			this->spriteWidth = spriteWidth;
			this->spriteHeight = spriteHeight;
			this->offsetX = offsetX;
			this->offsetY = offsetY;
			this->framesAmount = framesAmount;
			usePixelSize = true;
		}
	private:
		int columns;
		int rows;
		int offsetX;
		int offsetY;
		int framesAmount;
		bool usePixelSize = false;
		int spriteWidth;
		int spriteHeight;
		friend class animation;
	};
}