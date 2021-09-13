#pragma once
#include "PlayerFrame.h"
class AnimationTest :
	public PlayerFrame
{
public:
	AnimationTest(bool isLocal = false);
	~AnimationTest();

	void update(float dt);

	virtual void Skill_1();
	virtual void Skill_2();
	virtual void Skill_Unique();
};

