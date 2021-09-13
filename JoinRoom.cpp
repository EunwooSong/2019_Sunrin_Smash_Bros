#include "DXUT.h"
#include "JoinRoom.h"
#include "World.h"
#include "ClientManager.h"

JoinRoom::JoinRoom(string _roomIp, int _roomPort, string _roomName)
	: roomIp(_roomIp), roomPort(_roomPort), roomName(_roomName),
	isGameMaster(false), isGameStart(false), myServerIndexNum(0), myCharacterIndex(0)
{
	CMGR->connectRoom(to_string(roomPort), roomName);

	//Set Character Name
	characterName[0] = "최우혁"; characterName[1] = "유명환";
	characterName[2] = "송은우"; characterName[3] = "이재훈";

	background = new Sprite("image/Temp_Img/Online_JoinRoom/Online_JoinRoom_Tmp.png");
	addChild(background);

	D3DXCOLOR textColor = D3DXCOLOR(0, 0, 0, 1);		//set TEXT Color black
	showRoomName = new Text(roomName, 50, textColor);
	showRoomName->pos = Vec2(420.0f, 70.0f);
	addChild(showRoomName);

	Text * tmp;
	//Show User Info RESET
	tmp = new Text("Empty", 50, textColor);
	tmp->pos = Vec2(200.0f, 290.0f);
	userInfo.push_back(tmp);
	addChild(tmp);

	tmp = new Text("Empty", 50, textColor);
	tmp->pos = Vec2(770.0f, 290.0f);
	userInfo.push_back(tmp);
	addChild(tmp);

	tmp = new Text("Empty", 50, textColor);
	tmp->pos = Vec2(200.0f, 560.0f);
	userInfo.push_back(tmp);
	addChild(tmp);

	tmp = new Text("Empty", 50, textColor);
	tmp->pos = Vec2(770.0f, 560.0f);
	userInfo.push_back(tmp);
	addChild(tmp);

	if (myServerIndexNum == 0)
		isGameMaster = true;

	int i = 0;
	for (auto myInfo : userInfo) {
		if (myServerIndexNum == i) {
			myInfo->text = characterName[myCharacterIndex];
			break;
		}

		i++;
	}

	sendMyCharacterIndex();
	getOtherCharacterIndex();

	cout << "Server Ip/Port : " << roomIp << " / " << to_string(roomPort) << endl;
}

JoinRoom::~JoinRoom()
{
}

void JoinRoom::update(float dt)
{
	Scene::update(dt);
	CMGR->Frame();

	if (isGameStart) {
		printf("GameStart! \n");
	}

	if (world.getKeyState(VK_BACK) == 1) {
		exitRoom();
	}

	getMyServerIndexNum();
	setMyCharacterIndex();
	getOtherCharacterIndex();
}

void JoinRoom::getMyServerIndexNum()
{
	if (CMGR->Mypos() < 0) {
		return;
	}

	myServerIndexNum = CMGR->Mypos();

	printf("Server My Index : %d", myServerIndexNum);
}

void JoinRoom::setMyCharacterIndex()
{
	int i;

	//캐릭터 선택(좌/우 로선택)
	if (world.getKeyState(VK_LEFT) == 1) {
		myCharacterIndex = clamp(--myCharacterIndex, 0, 3);

		i = 0;
		for (auto myInfo : userInfo) {
			if (myServerIndexNum == i) {
				myInfo->text = characterName[myCharacterIndex];
				break;
			}

			i++;
		}
		sendMyCharacterIndex();
	}
	else if (world.getKeyState(VK_RIGHT) == 1) {
		myCharacterIndex = clamp(++myCharacterIndex, 0, 3);

		i = 0;
		for (auto myInfo : userInfo) {
			if (myServerIndexNum == i) {
				myInfo->text = characterName[myCharacterIndex];
				break;
			}

			i++;
		}
		sendMyCharacterIndex();
	}
}

void JoinRoom::sendMyCharacterIndex()
{
	//내가 고른 캐릭터 서버로 전송
	string myChar = "#" + to_string(myServerIndexNum) + "/" + to_string(myCharacterIndex);
	CMGR->SendData(myChar);
	cout << "My Pick : " << myChar << endl;
}

void JoinRoom::getOtherCharacterIndex()
{
	//순차적으로 상대방의 캐릭터 정보를 불러옴, 적용
}

void JoinRoom::exitRoom()
{
	//현재 접속중인 방을 나가고 메인 로비로 다시 접속
	CMGR->SendData("e" + CMGR->getMyIp());
}

void JoinRoom::gameStart()
{
	//게임 시작
	CMGR->SendData("s" + CMGR->getMyIp());
	isGameStart = true;
}
