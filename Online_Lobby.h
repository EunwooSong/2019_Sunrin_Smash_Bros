#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"
#include "World.h"
#include "RoomInfo.h"
#include "TitleScene.h"

class Online_Lobby :
	public Scene
{
private:
	Sprite * background;
	Text * portInputField;
	vector<RoomInfo *> roomGroup;
	int playerInfo;

	int lastYPos;

public:
	Online_Lobby();
	~Online_Lobby();

	void update(float dt);

	void updateRoom();
	void portInput();
};

