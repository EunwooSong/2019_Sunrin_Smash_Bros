#include "DXUT.h"
#include "Tutorial.h"
#include "TutorialGame.h"

Tutorial::Tutorial()
{
	background = new Sprite("image/tutoria/bg.png");
	background->scale.x = 0.67f;
	background->scale.y = 0.67f;
	addChild(background);

	p1 = new Sprite("image/tutoria/p1.png");
	p1->pos.x = 250.0f;
	p1->pos.y = 400.0f;
	addChild(p1);

	p2 = new Sprite("image/tutoria/p2.png");
	p2->pos.x = 900.0f;
	p2->pos.y = 400.0f;	
	addChild(p2);


	key1 = new Sprite("image/tutoria/keyIMG1.png");
	key1->scale.x = 0.5f;
	key1->scale.y = 0.5f;
	key1->pos.x = 500.0f;
	key1->pos.y = 600.0f;
	addChild(key1);

	key2 = new Sprite("image/tutoria/keyIMG2.png");
	key2->scale.x = 0.5f;
	key2->scale.y = 0.5f;
	key2->pos.x = 710.0f;
	key2->pos.y = 600.0f;
	addChild(key2);

	Player = new Sprite("image/tutoria/lee.png");
	Player->scale.x = 0.45f;
	Player->scale.y = 0.45f;
	Player->pos.x = 420.0f;
	Player->pos.y = 100.0f;
	addChild(Player);

	push = new Sprite("image/winnerback/push.png");
	push->pos.x = 560.0f;
	push->pos.y = 425.0f;
	push->scale.x = 0.73f;
	push->scale.y = 0.73f;
	addChild(push);


}


Tutorial::~Tutorial()
{
}

void Tutorial::update(float dt)
{
	Scene::update(dt);

	if (world.getKeyState(VK_BACK) == 1)
	{
		world.changeScene(new TitleScene());
	}

	if ((world.getMousePos().x >= 505 && world.getMousePos().x <= 580) && (world.getMousePos().y >= 615 && world.getMousePos().y <= 640))
	{

		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			if (tutoriaPlayer != 0)
				tutoriaPlayer--;
		}
	}

	if ((world.getMousePos().x >= 710 && world.getMousePos().x <= 800) && (world.getMousePos().y >= 615 && world.getMousePos().y <= 640))
	{

		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			if (tutoriaPlayer != 3)
				tutoriaPlayer++;
		}
	}



	if (world.getKeyState(VK_LEFT) == 1)
	{
		if (tutoriaPlayer != 0)
			tutoriaPlayer--;
	}
	if (world.getKeyState(VK_RIGHT) == 1)
	{
		if (tutoriaPlayer != 3)
			tutoriaPlayer++;
	}

	if (tutoriaPlayer == 0)
		tutoriaPlayeruri = "woo";
	if (tutoriaPlayer == 1)
		tutoriaPlayeruri = "song";
	if (tutoriaPlayer == 2)
		tutoriaPlayeruri = "jae";
	if (tutoriaPlayer == 3)
		tutoriaPlayeruri = "black";


	if (tutoriaPlayeruri == "song")
		Player->setPath("image/Lobby/en.png");
	else if (tutoriaPlayeruri == "jae")
		Player->setPath("image/Lobby/lee.png");
	else if (tutoriaPlayeruri == "woo")
		Player->setPath("image/Lobby/woo.png");
	else if (tutoriaPlayeruri == "black")
		Player->setPath("image/Lobby/black.png");


	if ((world.getMousePos().x >= 255 && world.getMousePos().x <= 355) && (world.getMousePos().y >= 405 && world.getMousePos().y <= 510))
	{

		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			p1->setPath("image/tutoria/p11.png");
			p2->setPath("image/tutoria/p2.png");
			setpath = 0;
		}
	}


	if ((world.getMousePos().x >= 905 && world.getMousePos().x <= 1030) && (world.getMousePos().y >= 405 && world.getMousePos().y <= 510))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			p2->setPath("image/tutoria/p22.png");
			p1->setPath("image/tutoria/p1.png");
			setpath = 1;
		}
	}

	if ((world.getMousePos().x >= 565 && world.getMousePos().x <= 725) && (world.getMousePos().y >= 435 && world.getMousePos().y <= 475))
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			if (!setpath)
				world.changeScene(new TutorialGame(tutoriaPlayeruri, false));
			else
				world.changeScene(new TutorialGame(tutoriaPlayeruri, true));
		}
	}

	printf("X:%f Y:%f\n", world.getMousePos().x, world.getMousePos().y);
}
