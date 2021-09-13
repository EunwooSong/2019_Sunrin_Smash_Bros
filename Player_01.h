#pragma once
#include "PlayerFrame.h"
#include "WigGuidedMissile.h"
class Player_01 :
	public PlayerFrame
{
private:
	Animation * protc;
public:
	WigGuidedMissile * wgm;

	Player_01(bool isLocal = false);
	~Player_01();

	void update(float dt);
	Projectile* boomerang;
	Vec2 nowPosition;
	Timer * Skill1Timer;
	Timer * uniTimer;

	PlayerFrame* EnemyPos;
	PlayerFrame* EnemyPos2;
	PlayerFrame* EnemyPos3;
	bool skill1bool = false;
	bool unibool = false;
	virtual void AnimationController(float dt);
	virtual void Attack();
	virtual void Skill_1();
	virtual void Skill_2();
	virtual void Skill_Unique();

	Animation * effect_Anim_Def;
	Projectile * def;

	bool returnboomerang = false;
};

