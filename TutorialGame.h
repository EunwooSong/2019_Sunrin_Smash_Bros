#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "World.h"
#include "PlayerFrame.h"
#include "Player_01.h"
#include "Player_02.h"
#include "Player_03.h"
#include "Player_04.h"
#include "Husu.h"
#include "TitleScene.h"
class TutorialGame :
	public Scene
{
public:
	TutorialGame();
	TutorialGame(string playerurl, bool p1);
	~TutorialGame();


	Sprite* skillex1;

	Sprite* background;
	PlayerFrame * Player;
	Husu* husu;
	void update(float dt);
};

