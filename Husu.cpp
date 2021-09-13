#include "DXUT.h"
#include "Husu.h"


Husu::Husu() : PlayerFrame(20000.0f, 1.0f, 5.0f, 10.0f, "husu")
{

	//Animation Setting
	anim_idle = new Animation("image/husufather", 1, false, 8.0f);
	anim_walk = new Animation("image/husufather", 1, false, 8.0f);
	anim_jump = new Animation("image/husufather", 1, false, 8.0f);
	anim_fall = new Animation("image/husufather", 1, false, 8.0f);
	anim_attack = new Animation("image/husufather", 1, false, 8.0f);
	anim_protect = new Animation("image/husufather", 1, false, 8.0f);
	anim_sk1 = new Animation("image/husufather", 1, false, 8.0f);
	anim_sk2 = new Animation("image/husufather", 1, false, 8.0f);
	anim_suq = new Animation("image/husufather", 1, false, 8.0f);
	anim_damage = new Animation("image/husufather", 1, false, 8.0f);
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

	left = NULL;
	right = NULL;

	//Default Animation Setting
	currentAnim = anim_idle;
	currentAnim->visible = true;

	scaleCenter = currentAnim->center();
	rect = currentAnim->rect;
	SetPlayerRect();

	//Speed Setting
	PlayerFrame::moveSpeed = 0.0f;
	PlayerFrame::jumpSpeed = 0.0f;

}


Husu::~Husu()
{
}

void Husu::update(float dt)
{
	PlayerFrame::update(dt);
}
