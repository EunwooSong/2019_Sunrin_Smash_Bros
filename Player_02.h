#pragma once
#include "PlayerFrame.h"
#include "Local_GameManager.h"
#include "Projectile.h"
#include "WigGuidedMissile.h"

class Player_02
	:public PlayerFrame
{
public:
	Player_02(bool isLocal = false);
	~Player_02();

	void update(float dt);

	Animation * effect_Anim_Def;
	Projectile * def;

	Timer * Skill1Timer;
	PlayerFrame* Enemy;
	bool Skill1boo1 = false;

	virtual void Attack();
	virtual void Skill_1();
	virtual void Skill_2();
	virtual void Skill_Unique();
};

