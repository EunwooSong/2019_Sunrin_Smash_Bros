#pragma once
#include "PlayerFrame.h"
#include "World.h"
#include "Projectile.h"
#include "Timer.h"
class Player_03 :
	public PlayerFrame
{
public:
	Player_03(bool isLocal = false);
	~Player_03();

	Animation * effect_Anim_Def;
	Projectile * def;

	Timer * Skill2Timer;
	Timer * Skill1Timer;
	Timer * Skill3Timer;

	void update(float dt);

	

	bool skill2bool = true;
	bool skill3bool = false;
	bool skill1bool = false;
	virtual void Attack();
	virtual void Skill_1();
	virtual void Skill_2();
	virtual void Skill_Unique();
};

