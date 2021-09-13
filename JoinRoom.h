#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"

class JoinRoom :
	public Scene
{
public:
	//UI
	Sprite * background;
	Text * showRoomName;	//방 제목 출력
	vector<Text *> userInfo;	//유저 정보 관리 리스트
	int users[4];				//유저 정보 임시 저장

	//Character Name
	string characterName[4];

	//Room Info
	string roomIp;			//방 아이피
	string roomName;		//방 제목

	int roomPort;			//방 포트
	bool isGameMaster;		//게임 마스터 인지 - 초기화에서 확인
	bool isGameStart;		//게임이 시작했는지

	int myServerIndexNum;	//0~3
	int myCharacterIndex;	//0~3

public:
	JoinRoom(string _roomIp = "", int _roomPort = 0, string _roomName = "");
	~JoinRoom();

	void update(float dt);

	void getMyServerIndexNum();		//서버 안에서의 나의 위치 정보(몇 번 플레이어인지) 확인
	void setMyCharacterIndex();		//캐릭터 선택(좌/우 로선택)
	void sendMyCharacterIndex();	//내가 고른 캐릭터 서버로 전송 
	void getOtherCharacterIndex();	//순차적으로 상대방의 캐릭터 정보를 불러옴, 적용

	void exitRoom();				//현재 접속중인 방을 나가고 메인 로비로 다시 접속

	//Room Master
	void gameStart();				//게임 시작
};

