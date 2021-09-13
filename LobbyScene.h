#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "World.h"
#include "GameScene.h"
#include "TitleScene.h"
class LobbyScene :
	public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	Sprite* blue;
	Sprite* red;
	Sprite* Player1CH;
	Sprite* Player2CH;
	Sprite* gray;
	Sprite* gray2;
	Sprite* p1;
	Sprite* p2;
	Sprite* Player1NM;
	Sprite* Player2NM;
	Sprite* background;
	Sprite* push;
	GameScene* gm;

	string Player1uri = "song";
	string Player2uri = "jae";
	int Player1Choose = 0;
	int Player2Choose = 1;
	void update(float dt);
};

