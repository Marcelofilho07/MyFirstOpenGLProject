#pragma once

class Texture
{
public:
	
	Texture(char const *filename, int desired_channels, bool bAlfa);

	inline unsigned int GetId() const { return textureId; }

private:
	
	unsigned int textureId;
};
