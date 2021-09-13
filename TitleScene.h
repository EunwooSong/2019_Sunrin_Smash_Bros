#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "World.h"

class TitleScene :
	public Scene
{
public:

	Timer* shakeTimer;

	Sprite* background1;
	Sprite* background2;
	Sprite* background3;
	Sprite* background4;
	Sprite* background5;
	Sprite* background6;
	Sprite* background7;
	Sprite* background8;
	Sprite* background9;

	bool Ani = true;
	bool AniALL = true;
	TitleScene();
	~TitleScene();

	void update(float dt);
	void shake(float duration, int count, float range);
};
