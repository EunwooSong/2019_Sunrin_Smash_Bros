#include "DXUT.h"
#include "TitleScene.h"
#include "LobbyScene.h"
#include "Online_Lobby.h"
#include "Asset.h"
#include "Tutorial.h"

TitleScene::TitleScene()
{
	//Sound
	asset.getSound(L"Sources/Sound/Game.wav");
	asset.getSound(L"Sources/Sound/Main.wav");
	asset.getSound(L"Sources/Sound/chack.wav");
	asset.getSound(L"Sources/Sound/punch.wav");
	asset.getSound(L"Sources/Sound/sigong.wav");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	background1 = new Sprite("image/title/8.png");
	background1->scale.x *= 1.2f;
	background1->scale.y *= 1.2f;
	background1->pos.x -= 100.0f;
	background1->pos.y -= 100.0f;

	addChild(background1);

	background2 = new Sprite("image/title/1.png");
	background2->scale.x = 0.7f;
	background2->scale.y = 0.7f;
	background2->pos.x = 100;
	background2->pos.y = 260;
	addChild(background2);

	background3 = new Sprite("image/title/3.png");
	background3->scale.x = 0.6f;
	background3->scale.y = 0.7f;
	background3->pos.x = 650;
	addChild(background3);

	background4 = new Sprite("image/title/4.png");
	background4->scale.x = 0.6f;
	background4->scale.y = 0.7f;
	background4->pos.x = 650;
	background4->pos.y = 370;
	addChild(background4);

	background5 = new Sprite("image/title/2.png");
	background5->scale.x = 0.7f;
	background5->scale.y = 0.7f;
	background5->pos.x = 840;
	background5->pos.y = 110;
	addChild(background5);

	background6 = new Sprite("image/title/5.png");
	background6->scale.x = 0.7f;
	background6->scale.y = 0.7f;
	background6->pos.x = 800;
	background6->pos.y = 500;
	addChild(background6);

	background8 = new Sprite("image/title/10.png");
	background8->scale.x = 0.76f;
	background8->scale.y = 0.76f;
	background8->pos.x = 0;
	background8->pos.y = 555;
	addChild(background8);

	background7 = new Sprite("image/title/9.png");
	background7->scale.x = 0.7f;
	background7->scale.y = 0.7f;
	background7->pos.x = 200;
	background7->pos.y = 600;
	addChild(background7);

	//shakeTimer = new Timer();
	//shake(0.001f, 10000, 5);
	asset.sounds[L"Sources/Sound/Main.wav"]->Play();
	asset.sounds[L"Sources/Sound/Game.wav"]->Stop();
}


TitleScene::~TitleScene()
{
	//shakeTimer->removing = true;
}

void TitleScene::update(float dt)
{

	Scene::update(dt);

	printf("X:%f Y:%f\n", world.getMousePos().x, world.getMousePos().y);

	if ((world.getMousePos().x >= 910 && world.getMousePos().x <= 1110) && (world.getMousePos().y >= 110 && world.getMousePos().y <= 200))
	{
		background5->scale.x = 1.0f;
		background5->scale.y = 1.0f;
		background5->pos.x = 800;
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			world.changeScene(new LobbyScene);
			AniALL = false;
		}
	}

	else if ((world.getMousePos().x >= 855 && world.getMousePos().x <= 1115) && (world.getMousePos().y >= 510 && world.getMousePos().y <= 595))
	{
		background6->scale.x = 1.0f;
		background6->scale.y = 1.0f;
		background6->pos.x = 700;

		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			world.changeScene(new Online_Lobby());
			AniALL = false;
		}
	}

	else if ((world.getMousePos().x >= 200 && world.getMousePos().x <= 500) && (world.getMousePos().y >= 600 && world.getMousePos().y <= 670))
	{
		background7->scale.x = 1.0f;
		background7->scale.y = 1.0f;
		background7->pos.x = 100;

		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			world.changeScene(new Tutorial);
			AniALL = false;
		}
	}


	else
	{
		background5->scale.x = 0.7f;
		background5->pos.x = 840;
		background5->scale.y = 0.7f;

		background6->scale.x = 0.7f;
		background6->pos.x = 800;
		background6->scale.y = 0.7f;

		background7->scale.x = 0.7f;
		background7->scale.y = 0.7f;
		background7->pos.x = 200;
	}

	if (AniALL) {
		if (Ani)
		{
			background2->scale.x += 0.05f* dt;
			background2->scale.y += 0.05f* dt;
		}
		else if (!Ani)
		{
			background2->scale.x -= 0.05f* dt;
			background2->scale.y -= 0.05f* dt;
		}

		if (background2->scale.x >= 0.8f)
		{
			Ani = false;
		}

		if (background2->scale.x <= 0.7f)
		{
			Ani = true;
		}

		background1->pos = background1->pos + Vec2(random(-3, 3), random(-3, 3));
	}


}

void TitleScene::shake(float duration, int count, float range)
{
	shakeTimer->reset(duration, count);
	shakeTimer->onTick = [=]()
	{
		background1->pos = background1->pos + Vec2(random(-range, range), random(-range, range));
	};
}