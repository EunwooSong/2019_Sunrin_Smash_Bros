#include "DXUT.h"
#include "RoomInfo.h"
#include "World.h"
#include "ClientManager.h"

RoomInfo::RoomInfo(string _roomIp, int _roomPort, int _currentPlayerCount, string _roomName, bool justInfo) :
	_roomIp(_roomIp), _roomPort(_roomPort), _currentPlayerCount(_currentPlayerCount), _roomName(_roomName), Maxnum(4)
{
	if (justInfo)
		return;

	//Set BackGround
	background = new Sprite("image/Temp_Img/Online_Room/Online_Room_Info.png");

	//Set Text
	roomName = new Text(_roomName, 50, D3DXCOLOR(0, 0, 0, 1));
	currentPlayerCount = new Text(to_string(_currentPlayerCount) + "/4", 50, D3DXCOLOR(0, 0, 0, 1));

	addChild(background);
	addChild(roomName);
	addChild(currentPlayerCount);

	roomName->pos.x = 50.0f;
	roomName->pos.y = 25.0f;

	currentPlayerCount->pos.x = 600.0f;
	currentPlayerCount->pos.y = 25.0f;
}


RoomInfo::~RoomInfo()
{
}

void RoomInfo::update(float dt)
{
	Entity::update(dt);

	Vec2 mousePos = world.getMousePos();

	//키 감지->connetRoom
	if (this->pos.x <= mousePos.x && this->pos.x + background->rect.right >= mousePos.x) {
		if (this->pos.y <= mousePos.y && this->pos.y + background->rect.bottom >= mousePos.y) {
			if (world.getKeyState(VK_LBUTTON) == 1) {
				CMGR->setSelectedRoomInfo(this);
				cout << _roomName << " is Clicked!" << endl;
			}
		}
	}
	else {
		if (world.getKeyState(VK_LBUTTON) == 1) {
			CMGR->setSelectedRoomInfo(nullptr);
			cout << _roomName << " is Unclicked!" << endl;
		}
	}
}

string RoomInfo::getIp()
{
	return _roomIp;
}

int RoomInfo::getPort()
{
	return _roomPort;
}

int RoomInfo::getCurrentPlayerCount()
{
	return _currentPlayerCount;
}

string RoomInfo::getRoomName()
{
	return _roomName;
}

void RoomInfo::setCurrnetPlayerCount(int _currentPlayerCount)
{
	this->_currentPlayerCount = _currentPlayerCount;
	currentPlayerCount->text = to_string(this->_currentPlayerCount) + "/4";
}

bool RoomInfo::connentRoom(string port, string roomname)
{
	//방접속
	if (this->_currentPlayerCount == NULL || this->_roomPort == NULL || this->_roomName == "")
		return false;

	if (this->_currentPlayerCount > 0 && this->_roomPort == atoi(port.c_str()) && this->_currentPlayerCount < this->Maxnum && this->_roomName == roomname) {
		this->_currentPlayerCount++;
		return true;
	}
	return false;
}

bool RoomInfo::outroom(string Ip)
{
	if (this->_roomIp == Ip) {
		this->_currentPlayerCount--;
		return true;
	}
	return false;
}
