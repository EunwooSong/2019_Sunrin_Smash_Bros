#include "DXUT.h"
#include "AnimationTest.h"


AnimationTest::AnimationTest(bool isLocal) : PlayerFrame(100.0f, 0.2f, 1.0f, 1.0f, "PlayerTemp",isLocal)
{
	//Animation Setting
	anim_idle = new Animation("Sources/Temp/Idle", 7, true, 8.0f);
	anim_walk = new Animation("Sources/Temp/Walk", 4, true, 8.0f);
	anim_jump = new Animation("Sources/Temp/Jump", 4, true, 8.0f);
	anim_fall = new Animation("Sources/Temp/Fall", 4, true, 8.0f);
	anim_attack = new Animation("Sources/Temp/Attack", 4, false, 8.0f);
	anim_protect = new Animation("Sources/Temp/Protect", 4, true, 8.0f);
	anim_sk1 = new Animation("Sources/Temp/Sk1", 4, false, 8.0f);
	anim_sk2 = new Animation("Sources/Temp/Sk2", 4, false, 8.0f);
	anim_suq = new Animation("Sources/Temp/Suq", 4, false, 8.0f);
	anim_damage = new Animation("Sources/Temp/Damage", 4, false, 8.0f);
	//anim_death = new Animation("Sources/Temp/Death", 4);

	addChild(anim_idle); anim_idle->visible = false;
	addChild(anim_walk); anim_walk->visible = false;
	addChild(anim_jump); anim_jump->visible = false;
	addChild(anim_fall); anim_fall->visible = false;
	addChild(anim_attack); anim_attack->visible = false;
	addChild(anim_protect); anim_protect->visible = false;
	addChild(anim_sk1); anim_sk1->visible = false;
	addChild(anim_sk2); anim_sk2->visible = false;
	addChild(anim_suq); anim_suq->visible = false;
	addChild(anim_damage); anim_damage->visible = false;
	//Default Animation Setting
	currentAnim = anim_idle;
	currentAnim->visible = true;

	//Speed Setting
	PlayerFrame::moveSpeed = 100.0f;
	PlayerFrame::jumpSpeed = 800.0f;

	//Start Position Setting
	this->pos.x = 50;
	this->pos.y = 100;
	
	//ScaleCenter Setting - For Render
	scaleCenter = currentAnim->center();
	rect = currentAnim->rect;
}

AnimationTest::~AnimationTest()
{
}

void AnimationTest::update(float dt)
{
	PlayerFrame::update(dt);
}

void AnimationTest::Skill_1()
{
	PlayerFrame::Skill_1();
}

void AnimationTest::Skill_2()
{
	PlayerFrame::Skill_2();
}

void AnimationTest::Skill_Unique()
{
	PlayerFrame::Skill_Unique();
}
