#pragma once
#include "PlayerFrame.h"
#include "World.h"
#include "Timer.h"
#include "Local_GameManager.h"
class Player_04 :
	public PlayerFrame
{
public:
	Player_04(bool isLocal);
	~Player_04();

	void update(float dt);

	//PlayerFrame * target;

	Timer* sk1timer;

	//Animation* ani;
	Animation * effect_Skill2;
	Animation * effect_Anim_Def;
	Projectile * def;

	bool shoot = false;
	bool shake = false;

	virtual void Attack();
	virtual void Skill_1();
	virtual void Skill_2();
	virtual void Skill_Unique();
};

