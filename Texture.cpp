#include "DXUT.h"
#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
	SAFE_RELEASE(d3dTexture);
}
