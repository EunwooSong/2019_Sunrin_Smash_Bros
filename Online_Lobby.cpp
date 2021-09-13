#include "DXUT.h"
#include "Online_Lobby.h"
#include "Network.h"
#include "Socket.h"
#include "MakeRoom.h"
#include "ClientManager.h"
#include "JoinRoom.h"

Online_Lobby::Online_Lobby() : lastYPos(300.0f), playerInfo(0)
{
	//socket conneting
	background = new Sprite("image/Temp_Img/Online_Lobby/Online_Lobby_Tmp.png");
	addChild(background);

	CMGR->SendData("listreset");

	portInputField = new Text("", 50, D3DXCOLOR(0, 0, 0, 1));
	addChild(portInputField);
	roomGroup.clear();
}


Online_Lobby::~Online_Lobby()
{

}

void Online_Lobby::update(float dt)
{
	Scene::update(dt);
	CMGR->Frame();

	//Move TitleScene
	if (world.getKeyState('T') == 1) {
		world.changeScene(new TitleScene());
		return;
	}

	//Move MakeScene -> JoinRoom
	if (world.getKeyState('C') == 1) {
		world.changeScene(new MakeRoom());
		return;
	}

	//Move JoinRoom
	if (world.getKeyState('J') == 1) {
		CMGR->connectRoom(to_string(CMGR->selectedRoomInfo->getPort()), CMGR->selectedRoomInfo->getRoomName());
		world.changeScene(new JoinRoom(CMGR->selectedRoomInfo->getIp(), CMGR->selectedRoomInfo->getPort(), CMGR->selectedRoomInfo->getRoomName()));
		return;
	}

	portInput();
	updateRoom();
}

void Online_Lobby::updateRoom()
{
	int len = CMGR->roomInfoGroup.size();

	if (len == roomGroup.size() + playerInfo)
		return;

	//reset
	for (auto room : roomGroup) {
		removeChild(room);
	}

	roomGroup.clear();
	playerInfo = 0;
	lastYPos = 300.0f;

	for (int i = 0; i < len; i++) {
		RoomInfo * tmp = new RoomInfo(CMGR->roomInfoGroup[i]->getIp(), CMGR->roomInfoGroup[i]->getPort(), CMGR->roomInfoGroup[i]->getCurrentPlayerCount(), CMGR->roomInfoGroup[i]->getRoomName(), false);

		if (tmp->getRoomName() == "") {
			playerInfo++;
			SAFE_DELETE(tmp);
			continue;
		}

		roomGroup.push_back(tmp);
		tmp->pos = Vec2(200.0f, lastYPos);
		lastYPos += 100 + 25;
		addChild(tmp);

		cout << tmp->getRoomName() << " ADD SUCCEEDED" << endl;
	}
}

void Online_Lobby::portInput()
{
	int roomPortLen = portInputField->text.length();
	//Delete
	if (world.getKeyState(VK_DELETE) == 1 || world.getKeyState(VK_BACK) == 1) {
		if (!portInputField->text.empty())
			portInputField->text.pop_back();
	}

	//NUM
	for (int i = '0'; i <= '9'; i++) {
		if (world.getKeyState(i) == 1) {
			if (roomPortLen < 4) {
				portInputField->text += i;
			}
		}
	}

	//NUMPAD
	for (int i = VK_NUMPAD0; i <= VK_NUMPAD9; i++) {
		if (world.getKeyState(i) == 1) {
			if (roomPortLen < 4) {
				portInputField->text += to_string(i - VK_NUMPAD0);
			}
		}
	}
}
