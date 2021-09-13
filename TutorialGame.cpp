#include "DXUT.h"
#include "TutorialGame.h"


TutorialGame::TutorialGame()
{
}

TutorialGame::TutorialGame(string playerurl, bool p1)
{
	background = new Sprite("image/background/tutoria.png");
	background->scale.x = 0.67;
	background->scale.y = 0.67;
	addChild(background);

	husu = new Husu();
	husu->pos.x = 400.0f;
	husu->pos.y = 300.0f;
	husu->local_Player = !p1;
	addChild(husu);

	skillex1 = new Sprite("image/skill_Ex/back.png");
	skillex1->pos.x = 0.0f;
	skillex1->pos.y = 0.0f;
	skillex1->scale.x = 0.67;
	skillex1->scale.y = 0.67;
	addChild(skillex1);
	skillex1->visible = false;
	if (playerurl == "song") {
		Player = new Player_03(p1);
	}
	else if (playerurl == "jae") {
		Player = new Player_04(p1);
	}
	else if (playerurl == "woo") {
		Player = new Player_01(p1);
	}
	else if (playerurl == "black") {
		Player = new Player_02(p1);
	}
	if (p1) {
		Player->pos.x = 1100.0f;
		Player->scale.x = 1.0f;
	}
	else {
		Player->pos.x = 100;
		Player->pos.y = 300;
	}
	addChild(Player);

	LOCAL_GM->addPlayer(Player);
	LOCAL_GM->addPlayer(husu);

	

}


TutorialGame::~TutorialGame()
{
}

void TutorialGame::update(float dt)
{
	//35 8 100 70

	Scene::update(dt);
	LOCAL_GM->Update_GameManager(dt);

	printf("X:%f Y:%f\n", world.getMousePos().x, world.getMousePos().y);



	if (world.getKeyState('F') >= 1)
	{
		skillex1->visible = true;
	}
	else {
		skillex1->visible = false;
	}


	if (world.getKeyState(VK_BACK) == 1)
	{
		world.changeScene(new TitleScene());
	}
}
