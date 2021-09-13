#pragma once
#include "Sprite.h"
#include "World.h"
#include "TitleScene.h"
#include "RoomInfo.h"
#include "IPEndpoint.h"
#include "TCPConnection.h"
#define CMGR ClientManager::getInstance()

class ClientManager
{
public:
	static ClientManager* getInstance() {
		static ClientManager* sw = new ClientManager();
		return sw;
	}

	ClientManager();
	~ClientManager();

	vector<RoomInfo *> roomInfoGroup;
	RoomInfo * selectedRoomInfo;
private:
	bool isConnected; //���� ���� ���� �˻�
	bool changegame;

	string ServerIp;
	unsigned int ServerPort;
	int mypos;

	string MyIp;
	unsigned int MyPort;

	WSAPOLLFD master_fd;
	WSAPOLLFD use_fd;
	PNet::TCPConnection connection;

	/*=--Server Values--=*/
	bool Connect(PNet::IPEndpoint ip);
	bool IsConnected();

	bool SPEND();
	bool RECV();

	void CloseConnection(string reason);//close server

	void DataManager();//data �˻�
	string getData(PNet::TCPConnection & connection);//data get

	void ShowMessage(string message);//print message

	void OnConnect();//���� ���� Ȯ��
	void OnConnectFail();//���� ���� Ȯ��

	//INGMAE
	void IngameManger();
	void Onskill(float x, float y, bool baseskill, bool skill1, bool skill2, bool skill3, int hp);
	void OnlinePlayerReset(float x, float y);
	bool ProcessPacket(std::shared_ptr<PNet::Packet> packet);//message show
public:
	void setSelectedRoomInfo(RoomInfo * target);
	RoomInfo* getSelectedRoomInfo();
	string getMyIp();
	int Mypos();
	bool Frame();//��� ���� �ؾ��� 
	void makeRoom(int password, string roomname);
	bool connectServer();
	bool connectServer(string Ip, int port);//Connect Server
	void connectRoom(string port, string roomname);
	void exitroom(string Ip);
	void getRoomInfo(string ip, string name, int port, int number);//Get room info at server
	void SendData(std::string sw);//send message
	void startClient();
	void fixRoomInfo(int index, int currnetPlayerCount);		//Fix currnetPlayerCount in roomInfoGroup index

	bool change() {
		return true;
	}//server�� Ŭ���̾�Ʈ�� ��ȯ+
};

