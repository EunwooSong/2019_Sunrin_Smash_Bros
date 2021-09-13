#include "DXUT.h"
#include "WinnerScene.h"
#include "TitleScene.h"
WinnerScene::WinnerScene(PlayerFrame* winner, bool duce, string url1, string url2, PlayerFrame* Player1)
{
	background = new Sprite("image/background/map.png");
	background->pos = Vec2(-200.0f, -100.0f);
	addChild(background);

	if (duce)
	{
		_duce = new Sprite("image/winnerback/win.png");
		_duce->scale.x = 0.67f;
		_duce->scale.y = 0.67f;
		addChild(_duce);
	}
	else
	{
		win = new Sprite("image/winnerback/win.png");
		win->scale.x = 0.67f;
		win->scale.y = 0.67f;
		addChild(win);
	}



	if (winner == Player1)
	{
		if (url1 == "jae")
			player = new Sprite("image/Lobby/lee.png");
		else if (url1 == "song")
			player = new Sprite("image/Lobby/en.png");
		else if (url1 == "woo")
			player = new Sprite("image/Lobby/woo.png");
		else if (url1 == "black")
			player = new Sprite("image/2/0.png");
		player->scale.x = 0.5f;
		player->pos.x = -100;

	}

	else
	{
		if (url2 == "jae")
			player = new Sprite("image/Lobby/lee.png");
		else if (url2 == "song")
			player = new Sprite("image/Lobby/en.png");
		else if (url2 == "woo")
			player = new Sprite("image/Lobby/en.png");
		else if (url2 == "black")
			player = new Sprite("image/2/0.png");
		player->scale.x = -0.5f;
		player->pos.x = 1400;
	}

	player->pos.y = 130;
	player->scale.y = 0.5f;
	addChild(player);
	push = new Sprite("image/winnerback/push.png");
	push->pos.x = 560.0f;
	push->pos.y = 425.0f;
	push->scale.x = 0.73f;
	push->scale.y = 0.73f;
	addChild(push);
}

WinnerScene::~WinnerScene()
{
}

void WinnerScene::update(float dt)
{
	Scene::update(dt);

	if ((world.getMousePos().x >= 565 && world.getMousePos().x <= 725) && (world.getMousePos().y >= 435 && world.getMousePos().y <= 475))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			world.changeScene(new TitleScene);
		}
	}
}
