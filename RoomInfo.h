#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Text.h"

class RoomInfo :
	public Entity
{
private:
	//=--Server Info--=
	string		_roomIp;
	int			_roomPort;
	//Show Info
	int			_currentPlayerCount;
	int			Maxnum;
	string		_roomName;

	//=--User Interface--=
	Sprite	*background;
	Text	*roomName;
	Text	*currentPlayerCount;

public:
	RoomInfo(string _roomIp, int _roomPort = 0, int _currentPlayerCount = 0, string _roomName = "", bool justInfo = true);
	~RoomInfo();

	void update(float dt);
	string getIp();
	int getPort();
	int getCurrentPlayerCount();
	string getRoomName();
	void setCurrnetPlayerCount(int _currentPlayerCount);
	bool connentRoom(string port, string roomname);
	bool outroom(string Ip);
};

