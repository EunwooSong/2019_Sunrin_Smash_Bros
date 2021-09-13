#include "DXUT.h"
#include "MakeRoom.h"
#include "JoinRoom.h"
#include "World.h"
#include "ClientManager.h"

MakeRoom::MakeRoom() : isRoomNameInput(true), roomName(""), roomPort(""), roomIp("0.0.0.0")
{
	Background = new Sprite("image/Temp_Img/Online_MakeRoom/Online_MakeRoom_Tmp.png");
	Background->pos = Vec2(0.0f, 0.0f);

	//Set Input && Background
	showRoomName = new Text(roomName, 50, D3DXCOLOR(0, 0, 0, 1));
	showRoomPort = new Text(roomPort, 50, D3DXCOLOR(0, 0, 0, 1));

	showRoomName->pos = Vec2(470.0f, 212.0f);
	showRoomPort->pos = Vec2(470.0f, 360.0f);

	addChild(Background);
	addChild(showRoomName);
	addChild(showRoomPort);

	//Set Room Ip
	roomIp = CMGR->getMyIp();
}


MakeRoom::~MakeRoom()
{
}

void MakeRoom::sendServer()
{
	//Send Room Info -> MoveRoom
	CMGR->makeRoom(stoi(roomPort), roomName);
	world.changeScene(new JoinRoom(roomIp, stoi(roomPort), roomName));
}

void MakeRoom::getUserInput()
{
	//Get Key Input

	//Room Name - A ~ Z, a ~ z, 0 ~ 9, -, _, ' '
	int roomNameLen = roomName.length();
	int roomPortLen = roomPort.length();

	//A~Z, a~z
	for (int i = 'A'; i <= 'Z'; i++) {
		if (isRoomNameInput && roomNameLen <= 23)
			if (world.getKeyState(i) == 1) {
				if (world.getKeyState(VK_LSHIFT) >= 1 || world.getKeyState(VK_RSHIFT) >= 1) {
					roomName += i;
				}
				else {
					roomName += ('a' - 'A') + i;
				}

				showRoomName->text = roomName;
			}
	}

	//SPACEBAR
	if (world.getKeyState(' ') == 1) {
		if (isRoomNameInput && roomNameLen <= 23) {
			roomName += ' ';
			showRoomName->text = roomName;
		}
	}

	//NUM
	for (int i = '0'; i <= '9'; i++) {
		if (world.getKeyState(i) == 1) {
			if (isRoomNameInput && roomNameLen <= 23) {
				roomName += i;
				showRoomName->text = roomName;
			}
			else if (!isRoomNameInput && roomPortLen < 4) {
				roomPort += i;
				showRoomPort->text = roomPort;
			}
		}
	}

	//NUMPAD
	for (int i = VK_NUMPAD0; i <= VK_NUMPAD9; i++) {
		if (world.getKeyState(i) == 1) {
			if (isRoomNameInput && roomNameLen <= 23) {
				roomName += to_string(i - VK_NUMPAD0);
				showRoomName->text = roomName;
			}
			else if (!isRoomNameInput && roomPortLen < 4) {
				roomPort += to_string(i - VK_NUMPAD0);
				showRoomPort->text = roomPort;
			}
		}
	}

	//Delete
	if (world.getKeyState(VK_DELETE) == 1 || world.getKeyState(VK_BACK) == 1) {
		if (isRoomNameInput) {
			if (!roomName.empty())
				roomName.pop_back();
			showRoomName->text = roomName;
		}
		else {
			if (!roomPort.empty())
				roomPort.pop_back();
			showRoomPort->text = roomPort;
		}
	}
}

void MakeRoom::focus()
{
	//Ser Input Focus
	//1. MouseCursor

	//2. Input Keyboard
	if (world.getKeyState(VK_TAB) == 1) {
		isRoomNameInput = !isRoomNameInput;
		printf("Change Focus Succeeded! \n");
	}
}

void MakeRoom::update(float dt)
{
	Scene::update(dt);
	CMGR->Frame();

	focus();
	getUserInput();

	//If User Input VK_LEFT -> SendServer
	if (world.getKeyState(VK_LEFT) == 1) {
		printf("Send Room Info to Server, Move To JoinRoom . . .\n");
		sendServer();
		return;
	}
}
