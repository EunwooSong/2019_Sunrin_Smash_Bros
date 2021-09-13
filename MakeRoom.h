#pragma once
#include "Scene.h"
#include "Text.h"
#include "Sprite.h"

class MakeRoom :
	public Scene
{
private:
	Sprite * Background;
	Sprite * inputRoomName_BG;
	Sprite * inputRoomPort_BG;
	Text * showRoomName;
	Text * showRoomPort;

	string roomIp;
	string roomName;
	string roomPort;

	bool isRoomNameInput;

public:
	MakeRoom();
	~MakeRoom();

	void sendServer();		//send roomName, roomPort to server
	void getUserInput();	//get user input values
	void focus();			//set user input focus 

	void update(float dt);
};

