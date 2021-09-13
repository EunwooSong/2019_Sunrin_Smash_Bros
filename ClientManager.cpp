#include "DXUT.h"
#include "ClientManager.h"
#include "Network.h"
#include "Socket.h"

using namespace PNet;

ClientManager::ClientManager() :ServerIp("172.30.1.4"), ServerPort(9123), isConnected(false), changegame(true)
{
	if (!Network::Initialize())
	{
		//error
	}
	roomInfoGroup.clear();
	connectServer(ServerIp, ServerPort);//connect 로비server
}

ClientManager::~ClientManager()
{
	//out socket
	Network::Shutdown();

	for (auto obj : roomInfoGroup)
		obj->removing = true;

	//removing Online
	roomInfoGroup.clear();
	/*roomInfoGroup.erase(remove_if(roomInfoGroup.begin(), roomInfoGroup.end(),
		[&](auto iter) {
		bool removing = iter->removing;
		SAFE_DELETE(iter);
		return removing;
	}), roomInfoGroup.end());*/
}

bool ClientManager::Connect(PNet::IPEndpoint ip)
{
	isConnected = false;
	Socket socket = Socket(ip.GetIPVersion());
	if (socket.Create() == PResult::P_Success)
	{
		if (socket.SetBlocking(true) != PResult::P_Success)
			return false;


		std::cout << "소켓이 성공적으로 생성되었습니다." << std::endl;
		if (socket.Connect(ip) == PResult::P_Success)
		{
			if (socket.SetBlocking(false) == PResult::P_Success)
			{
				connection = TCPConnection(socket, ip);
				master_fd.fd = connection.socket.GetHandle();
				master_fd.events = POLLRDNORM;
				master_fd.revents = 0;
				isConnected = true;
				OnConnect();
				return true;
			}
		}
		else
		{
			socket.Close();
		}
	}
	else
	{
		std::cerr << "소켓을 만들지 못했습니다." << std::endl;
	}
	OnConnectFail();
	return false;
}

bool ClientManager::IsConnected()
{
	return isConnected;
}

bool ClientManager::Frame()
{
	if (!IsConnected()) {
		return false;
	}

	if (connection.pm_outgoing.HasPendingPackets())
	{
		master_fd.events = POLLRDNORM | POLLWRNORM;
	}

	use_fd = master_fd;

	if (WSAPoll(&use_fd, 1, 1) >= 0)
	{
		if (use_fd.revents & POLLERR) //If error occurred on this socket
		{
			CloseConnection("POLLERR");
			return false;
		}

		if (use_fd.revents & POLLHUP) //If poll hangup occurred on this socket
		{
			CloseConnection("POLLHUP");
			return false;
		}

		if (use_fd.revents & POLLNVAL) //If invalid socket
		{
			CloseConnection("POLLNVAL");
			return false;
		}

		if (!RECV()) {
			return false;
		}

		if (changegame) {
			IngameManger();
		}
		else {
			DataManager();
		}

		if (!SPEND()) {
			return false;
		}
	}
	while (connection.pm_incoming.HasPendingPackets())
	{
		std::shared_ptr<Packet> frontPacket = connection.pm_incoming.Retrieve();
		if (!ProcessPacket(frontPacket))//data 출력
		{
			CloseConnection("Failed to process incoming packet.");
			return false;
		}
		connection.pm_incoming.Pop();
	}
	return true;
}

bool ClientManager::SPEND()
{
	PacketManager & pm = connection.pm_outgoing;
	while (pm.HasPendingPackets())
	{
		if (pm.currentTask == PacketManagerTask::ProcessPacketSize) //Sending packet size
		{
			pm.currentPacketSize = pm.Retrieve()->buffer.size();
			uint16_t bigEndianPacketSize = htons(pm.currentPacketSize);
			int bytesSent = send(use_fd.fd, (char*)(&bigEndianPacketSize) + pm.currentPacketExtractionOffset, sizeof(uint16_t) - pm.currentPacketExtractionOffset, 0);
			if (bytesSent > 0)
			{
				pm.currentPacketExtractionOffset += bytesSent;
			}

			if (pm.currentPacketExtractionOffset == sizeof(uint16_t)) //If full packet size was sent
			{
				pm.currentPacketExtractionOffset = 0;
				pm.currentTask = PacketManagerTask::ProcessPacketContents;
			}
			else //If full packet size was not sent, break out of the loop for sending outgoing packets for this connection - we'll have to try again next time we are able to write normal data without blocking
			{
				return false;
				//break;
			}
		}
		else //Sending packet contents
		{
			char * bufferPtr = &pm.Retrieve()->buffer[0];
			int bytesSent = send(use_fd.fd, (char*)(bufferPtr)+pm.currentPacketExtractionOffset, pm.currentPacketSize - pm.currentPacketExtractionOffset, 0);
			if (bytesSent > 0)
			{
				pm.currentPacketExtractionOffset += bytesSent;
			}

			if (pm.currentPacketExtractionOffset == pm.currentPacketSize) //If full packet contents have been sent
			{
				pm.currentPacketExtractionOffset = 0;
				pm.currentTask = PacketManagerTask::ProcessPacketSize;
				pm.Pop(); //Remove packet from queue after finished processing
			}
			else
			{
				return false;
				//break; //Added after tutorial was made 2019-06-24
			}
		}
	}
	if (!connection.pm_outgoing.HasPendingPackets())
	{
		master_fd.events = POLLRDNORM;
	}

	return true;
}

bool ClientManager::RECV()
{
	int bytesReceived = 0;

	if (connection.pm_incoming.currentTask == PacketManagerTask::ProcessPacketSize)
	{
		bytesReceived = recv(use_fd.fd, (char*)&connection.pm_incoming.currentPacketSize + connection.pm_incoming.currentPacketExtractionOffset, sizeof(uint16_t) - connection.pm_incoming.currentPacketExtractionOffset, 0);
	}
	else //Process Packet Contents
	{
		bytesReceived = recv(use_fd.fd, (char*)&connection.buffer + connection.pm_incoming.currentPacketExtractionOffset, connection.pm_incoming.currentPacketSize - connection.pm_incoming.currentPacketExtractionOffset, 0);
	}


	if (bytesReceived == 0) //If connection was lost
	{
		CloseConnection("Recv==0");
		return false;
	}

	if (bytesReceived == SOCKET_ERROR) //If error occurred on socket
	{
		int error = WSAGetLastError();
		if (error != WSAEWOULDBLOCK)
		{
			CloseConnection("Recv<0");
			return false;
		}
	}

	if (bytesReceived > 0)
	{
		connection.pm_incoming.currentPacketExtractionOffset += bytesReceived;
		if (connection.pm_incoming.currentTask == PacketManagerTask::ProcessPacketSize)
		{
			if (connection.pm_incoming.currentPacketExtractionOffset == sizeof(uint16_t))
			{
				connection.pm_incoming.currentPacketSize = ntohs(connection.pm_incoming.currentPacketSize);
				if (connection.pm_incoming.currentPacketSize > PNet::g_MaxPacketSize)
				{
					CloseConnection("Packet size too large.");
					return false;
				}
				connection.pm_incoming.currentPacketExtractionOffset = 0;
				connection.pm_incoming.currentTask = PacketManagerTask::ProcessPacketContents;
			}
		}
		else //Processing packet contents
		{
			if (connection.pm_incoming.currentPacketExtractionOffset == connection.pm_incoming.currentPacketSize)
			{
				std::shared_ptr<Packet> packet = std::make_shared<Packet>();
				packet->buffer.resize(connection.pm_incoming.currentPacketSize);
				memcpy(&packet->buffer[0], connection.buffer, connection.pm_incoming.currentPacketSize);

				connection.pm_incoming.Append(packet);

				connection.pm_incoming.currentPacketSize = 0;
				connection.pm_incoming.currentPacketExtractionOffset = 0;
				connection.pm_incoming.currentTask = PacketManagerTask::ProcessPacketSize;
			}
		}
	}
	return true;
}

void ClientManager::CloseConnection(string reason)
{
	cout << "연결이 끊어졌습니다.  원인 :" << reason << "." << endl;
	master_fd.fd = 0;
	isConnected = false;
	connection.Close();
}

void ClientManager::DataManager()
{
	std::string message = getData(connection);

	if (message.empty())//NULL 이면 return
		return;

	if (message[0] == 'p') {
		mypos = stoi(message.substr(message.find("<") + 1, message.find(">")));
	}

	if (message[0] == 'r') {
		//list 초기화
		int port = atoi(message.substr(message.find("r") + 1, message.find("!") - message.find("r") - 1).c_str());
		string ip = message.substr(message.find("!") + 1, message.find("@") - message.find("!") - 1);
		int size = atoi(message.substr(message.find("@") + 1, message.find("#") - message.find("@")).c_str());
		string roomName = message.substr(message.find("#") + 1, message.size() - message.find("#"));
		RoomInfo * sw = new RoomInfo(ip, port, size, roomName);

		for (auto check : roomInfoGroup) {
			if (sw->getIp() == check->getIp()) {
				return;
			}
		}
		cout << "RoomName / PORT : " << sw->getRoomName() << sw->getPort() << endl;
		roomInfoGroup.push_back(sw);
		//ShowMessage(ip + " " + to_string(port));
	}
	else if (message[0] == '<') {
		MyIp = message.substr(message.find("<") + 1, message.find(">") - 1);
		//MyPort = atoi(message.substr(message.find("/") + 1,message.size()- message.find("/")).c_str());
	}
	//data 복원
	else {
		//ShowMessage(message);
	}
}

string ClientManager::getData(PNet::TCPConnection & connection)
{
	if (!connection.pm_incoming.HasPendingPackets()) {
		return "";
	}
	std::shared_ptr<Packet> frontPacket = connection.pm_incoming.Retrieve();
	std::string message;
	switch (frontPacket->GetPacketType()) {
	case PacketType::PT_ChatMessage: {
		*frontPacket >> message;
		break;
	}
	}
	connection.pm_incoming.Pop();
	return message;
}

void ClientManager::ShowMessage(string message)
{
	std::shared_ptr<Packet> sendpacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*sendpacket << message;
	connection.pm_incoming.Append(sendpacket);
}

void ClientManager::OnConnect()
{
	cout << "연결완료" << endl;
}

void ClientManager::OnConnectFail()
{
	cout << "연결 실패" << endl;
}

void ClientManager::IngameManger()
{
	string message = getData(connection);
}

void ClientManager::Onskill(float x, float y, bool baseskill, bool skill1, bool skill2, bool skill3, int hp)
{

	//@who#x!y| +<"t"+ "t"+"f"+"t">+hp(int)  v   

	//skillchange
	string skills[4];
	if (baseskill)
		skills[0] = "t";
	else
		skills[0] = "f";
	if (skill1)
		skills[1] = "t";
	else
		skills[1] = "f";
	if (skill2)
		skills[2] = "t";
	else
		skills[2] = "f";
	if (skill3)
		skills[3] = "t";
	else
		skills[3] = "f";

	SendData("@" + to_string(mypos) + "#" + to_string(x) + "!" + to_string(y) + "|" + "<" + skills[0] + skills[1] + skills[2] + skills[3] + ">" + to_string(hp));
	SPEND();
}

void ClientManager::OnlinePlayerReset(float x, float y)
{
	SendData("<" + to_string(mypos) + ">@" + to_string(x) + "!/" + to_string(y) + "|");
	SPEND();
}

bool ClientManager::ProcessPacket(std::shared_ptr<PNet::Packet> packet)
{
	switch (packet->GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::string chatmessage;
		*packet >> chatmessage;
		std::cout << "Chat Message: " << chatmessage << std::endl;
		break;
	}
	case PacketType::PT_IntegerArray:
	{
		uint32_t arraySize = 0;
		*packet >> arraySize;
		std::cout << "Array Size: " << arraySize << std::endl;
		for (uint32_t i = 0; i < arraySize; i++)
		{
			uint32_t element = 0;
			*packet >> element;
			std::cout << "Element[" << i << "] - " << element << std::endl;
		}
		break;
	}
	default:
		std::cout << "Unrecognized packet type: " << packet->GetPacketType() << std::endl;
		return false;
	}

	return true;
}

void ClientManager::setSelectedRoomInfo(RoomInfo * target)
{
	selectedRoomInfo = target;
}

RoomInfo * ClientManager::getSelectedRoomInfo()
{
	return selectedRoomInfo;
}

string ClientManager::getMyIp()
{
	return MyIp;
}

int ClientManager::Mypos()
{
	return mypos;
}

void ClientManager::startClient()
{
	CloseConnection("gamestart");
	connectServer(ServerIp, ServerPort);
}

void ClientManager::makeRoom(int password, string roomname)
{
	RoomInfo* swroom = new RoomInfo(MyIp, password, 1, roomname);
	roomInfoGroup.push_back(swroom);
	//시간 되면 중복 검사 이름 비번 둘다 같을 경우
	SendData("1<" + MyIp + ">" + "/" + to_string(password) + '!' + "4" + "*" + roomname);
	//SPEND();
}

bool ClientManager::connectServer()
{
	if (!Connect(IPEndpoint(ServerIp.c_str(), ServerPort))) {
		//error
		return false;
	}
	if (changegame)
		changegame = false;
	else
		changegame = true;

	isConnected = true;//재접속
	return true;
}

bool ClientManager::connectServer(string Ip, int port)
{
	if (!Connect(IPEndpoint(Ip.c_str(), port))) {
		//error
		return false;
	}
	if (changegame)
		changegame = false;
	else
		changegame = true;

	isConnected = true;//재접속
	return true;
}

void ClientManager::connectRoom(string port, string roomname)
{
	string Ip = MyIp;//getip

	for (int i = 0; i < roomInfoGroup.size(); i++) {
		if (roomInfoGroup[i]->connentRoom(port, roomname))
		{
			SendData("2" + '<' + Ip + ">" + "/" + port);
			return;
		}
	}
	//방이 시작됬거나 폭파됨 message 출력
}

void ClientManager::exitroom(string Ip)//아이피를 받아오는 이유는 내가 만든 서버인지 아니면 참가한 서버인지 구분불가
{
	for (int i = 0; i < roomInfoGroup.size(); i++) {
		if (roomInfoGroup[i]->outroom(Ip))
		{
			SendData("e" + '<' + Ip + ">");
			return;
		}
	}
}

void ClientManager::getRoomInfo(string ip, string name, int port, int number)
{
	//서버에서 방정보들을 받아와서 vector 초기화
	RoomInfo* sw = new RoomInfo(ip, port, number, name);
	roomInfoGroup.push_back(sw);
}

void ClientManager::SendData(std::string sw)
{
	std::shared_ptr<Packet> sendPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*sendPacket << sw;
	connection.pm_outgoing.Append(sendPacket);

	SPEND();
}

//Fix currnetPlayerCount in roomInfoGroup index
void ClientManager::fixRoomInfo(int index, int currnetPlayerCount)
{
	auto target = roomInfoGroup.begin();
	advance(target, index);

	RoomInfo * tmp = *target;
	tmp->setCurrnetPlayerCount(currnetPlayerCount);
}
