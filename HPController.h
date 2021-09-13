#pragma once
#include "Sprite.h"
#include "PlayerFrame.h"
#include "Scene.h"
class HPController
{
private:


	Sprite* outFlame;
	Sprite* outFlame2;

	Sprite* Player1HP1;
	Sprite* Player1HP2;
	Sprite* Player1HP3;
	Sprite* Player1HP4;
	Sprite* Player1HP5;

	Sprite* Player2HP1;
	Sprite* Player2HP2;
	Sprite* Player2HP3;
	Sprite* Player2HP4;
	Sprite* Player2HP5;

	Sprite* Player1si1;
	Sprite* Player1si2;
	Sprite* Player1si3;
	Sprite* Player1si4;
	Sprite* Player1si5;

	Sprite* Player2si1;
	Sprite* Player2si2;
	Sprite* Player2si3;
	Sprite* Player2si4;
	Sprite* Player2si5;

	Sprite* Head1;
	Sprite* Head2;

	Sprite* skill1;
	Sprite* skill2;
	Sprite* skill3;

	Sprite* skill4;
	Sprite* skill5;
	Sprite* skill6;

	vector<Sprite*> fillSkillbar;

	Sprite* skillbar1;
	Sprite* skillbar2;
	Sprite* skillbar3;

	Sprite* skillbar4;
	Sprite* skillbar5;
	Sprite* skillbar6;
public:
	HPController(Scene * cs, string url1, string url2);
	~HPController();
	PlayerFrame * winner;
	bool duce;
	void updateHPGUI(PlayerFrame * p1, PlayerFrame * p2);
	void updateShieldGUI(PlayerFrame * p1, PlayerFrame * p2);
	void updateSkillCoolFill(PlayerFrame * p1, PlayerFrame * p2);
};

