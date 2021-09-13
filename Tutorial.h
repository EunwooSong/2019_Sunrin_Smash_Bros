#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "World.h"
#include "Timer.h"
class Tutorial :
	public Scene
{
public:
	Tutorial();
	~Tutorial();
private:
	Sprite* background;
	Sprite* p1;
	Sprite* p2;
	Sprite* key1;
	Sprite* key2;
	Sprite* Player;
	Sprite* push;
	int tutoriaPlayer = 2;
	string tutoriaPlayeruri = "jae";
	int setpath = 0;
	void update(float dt);
};

