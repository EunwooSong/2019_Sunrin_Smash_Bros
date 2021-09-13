#pragma once
#include "Scene.h"
#include "HPController.h"
#include "Timer.h"
#include "World.h"
#include "Player_03.h"
#include "Player_04.h"
class WinnerScene :
	public Scene
{
public:
	WinnerScene(PlayerFrame* winner, bool duce, string url1, string url2, PlayerFrame* Player1);
	~WinnerScene();
	Sprite* background;
	Sprite* win;
	Sprite* _duce;
	Sprite* push;
	Sprite* player;
	Timer* end;

	void update(float dt);
};

