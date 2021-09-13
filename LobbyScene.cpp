#include "DXUT.h"
#include "LobbyScene.h"
#include "GameScene.h"

LobbyScene::LobbyScene()
{
	background = new Sprite("image/Lobby/background.png");
	addChild(background);

	blue = new Sprite("image/Lobby/blue.png");
	blue->scale.x = 0.7f;
	blue->scale.y = 0.7f;
	blue->pos.x = 170;
	blue->pos.y = 280;
	addChild(blue);

	red = new Sprite("image/Lobby/red.png");
	red->scale.x = 0.7f;
	red->scale.y = 0.7f;
	red->pos.x = 977;
	red->pos.y = 280;
	addChild(red);


	gray = new Sprite("image/Lobby/gg.png");
	gray->scale.x = 0.7f;
	gray->scale.y = 0.7f;
	gray->pos.x = 235;
	gray->pos.y = 345;
	addChild(gray);

	gray2 = new Sprite("image/Lobby/gg.png");
	gray2->scale.x = 0.7f;
	gray2->scale.y = 0.7f;
	gray2->pos.x = 835;
	gray2->pos.y = 345;
	addChild(gray2);

	p1 = new Sprite("image/Lobby/p1.png");
	p1->scale.x = 0.7f;
	p1->scale.y = 0.7f;
	p1->pos.x = 180;
	p1->pos.y = 290;
	addChild(p1);

	p2 = new Sprite("image/Lobby/p2.png");
	p2->scale.x = 0.7f;
	p2->scale.y = 0.7f;
	p2->pos.x = 1030;
	p2->pos.y = 290;
	addChild(p2);


	Player1NM = new Sprite("image/Lobby/koreanj.png");
	Player1NM->scale.x = 0.7f;
	Player1NM->scale.y = 0.7f;
	Player1NM->pos.x = 285;
	Player1NM->pos.y = 420;
	addChild(Player1NM);

	Player2NM = new Sprite("image/Lobby/koreane.png");
	Player2NM->scale.x = 0.7f;
	Player2NM->scale.y = 0.7f;
	Player2NM->pos.x = 895;
	Player2NM->pos.y = 420;
	addChild(Player2NM);

	Player1CH = new Sprite("image/Lobby/lee.png");
	Player1CH->scale.x = 0.5f;
	Player1CH->scale.y = 0.5f;
	Player1CH->pos.x = -170;
	Player1CH->pos.y = 130;
	addChild(Player1CH);

	Player2CH = new Sprite("image/Lobby/en.png");
	Player2CH->scale.x = -0.5f;
	Player2CH->scale.y = 0.5f;
	Player2CH->pos.x = 1445;
	Player2CH->pos.y = 130;
	addChild(Player2CH);

	push = new Sprite("image/winnerback/push.png");
	push->pos.x = 560.0f;
	push->pos.y = 425.0f;
	push->scale.x = 0.73f;
	push->scale.y = 0.73f;
	addChild(push);
}


LobbyScene::~LobbyScene()
{
}

void LobbyScene::update(float dt)
{
	Scene::update(dt);



	//캐릭터 변환
	if (world.getKeyState('A') == 1)
	{
		if (Player1Choose != 0)
			Player1Choose--;
	}
	if (world.getKeyState('D') == 1)
	{
		if (Player1Choose != 3)
			Player1Choose++;
	}
	//캐릭터 변환
	if (world.getKeyState(VK_LEFT) == 1)
	{
		if (Player2Choose != 0)
			Player2Choose--;
	}
	if (world.getKeyState(VK_RIGHT) == 1)
	{
		if (Player2Choose != 3)
			Player2Choose++;
	}

	if (Player1Choose == 0)
		Player1uri = "woo";
	if (Player1Choose == 1)
		Player1uri = "song";
	if (Player1Choose == 2)
		Player1uri = "jae";
	if (Player1Choose == 3)
		Player1uri = "black";

	if (Player2Choose == 0)
		Player2uri = "woo";
	if (Player2Choose == 1)
		Player2uri = "song";
	if (Player2Choose == 2)
		Player2uri = "jae";
	if (Player2Choose == 3)
		Player2uri = "black";

	if (Player2uri == "song")
	{
		Player2CH->setPath("image/Lobby/en.png");
		Player2NM->setPath("image/Lobby/koreane.png");
	}
	else if (Player2uri == "jae")
	{
		Player2CH->setPath("image/Lobby/lee.png");
		Player2NM->setPath("image/Lobby/koreanj.png");
	}
	else if (Player2uri == "woo")
	{
		Player2CH->setPath("image/Lobby/woo.png");
		Player2NM->setPath("image/Lobby/koreanw.png");
	}
	else if (Player2uri == "black")
	{
		Player2CH->setPath("image/Lobby/black.png");
		Player2NM->setPath("image/Lobby/koreanm.png");
	}



	if (Player1uri == "jae")
	{
		Player1CH->setPath("image/Lobby/lee.png");
		Player1NM->setPath("image/Lobby/koreanj.png");
	}
	else if (Player1uri == "song")
	{
		Player1CH->setPath("image/Lobby/en.png");
		Player1NM->setPath("image/Lobby/koreane.png");
	}
	else if (Player1uri == "woo")
	{
		Player1CH->setPath("image/Lobby/woo.png");
		Player1NM->setPath("image/Lobby/koreanw.png");
	}
	else if (Player1uri == "black")
	{
		Player1CH->setPath("image/Lobby/black.png");
		Player1NM->setPath("image/Lobby/koreanm.png");
	}

	if (world.getKeyState(VK_BACK) == 1)
	{
		world.changeScene(new TitleScene());
	}

	if ((world.getMousePos().x >= 565 && world.getMousePos().x <= 725) && (world.getMousePos().y >= 435 && world.getMousePos().y <= 475))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			world.changeScene(new GameScene(this->Player1uri, this->Player2uri));
		}
	}
}