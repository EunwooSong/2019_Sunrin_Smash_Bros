#pragma once
#include "Define.h"
#include "Entity.h"

class Text :
	public Entity
{
public:
	Text(string text, int size, D3DXCOLOR color);
	~Text();

	void render();
	void setText(string text);

	LPD3DXFONT font;
	string text;
	int size;
	D3DXCOLOR color;
};

