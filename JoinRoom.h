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
	Text * showRoomName;	//�� ���� ���
	vector<Text *> userInfo;	//���� ���� ���� ����Ʈ
	int users[4];				//���� ���� �ӽ� ����

	//Character Name
	string characterName[4];

	//Room Info
	string roomIp;			//�� ������
	string roomName;		//�� ����

	int roomPort;			//�� ��Ʈ
	bool isGameMaster;		//���� ������ ���� - �ʱ�ȭ���� Ȯ��
	bool isGameStart;		//������ �����ߴ���

	int myServerIndexNum;	//0~3
	int myCharacterIndex;	//0~3

public:
	JoinRoom(string _roomIp = "", int _roomPort = 0, string _roomName = "");
	~JoinRoom();

	void update(float dt);

	void getMyServerIndexNum();		//���� �ȿ����� ���� ��ġ ����(�� �� �÷��̾�����) Ȯ��
	void setMyCharacterIndex();		//ĳ���� ����(��/�� �μ���)
	void sendMyCharacterIndex();	//���� �� ĳ���� ������ ���� 
	void getOtherCharacterIndex();	//���������� ������ ĳ���� ������ �ҷ���, ����

	void exitRoom();				//���� �������� ���� ������ ���� �κ�� �ٽ� ����

	//Room Master
	void gameStart();				//���� ����
};

