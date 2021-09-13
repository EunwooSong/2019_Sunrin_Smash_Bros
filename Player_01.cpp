#include "DXUT.h"
#include "Player_01.h"
#include "Local_GameManager.h"
#include "WigGuidedMissile.h"

//최우혁

Player_01::Player_01(bool isLocal) : PlayerFrame(100.0f, 1.0f, 5.0f, 10.0f, "Player01", isLocal), def(nullptr)
{
	//Animation Setting
	anim_idle = new Animation("image/choi_idle", 8, true, 8.0f);
	anim_walk = new Animation("image/choi_move", 8, true, 8.0f);
	anim_jump = new Animation("image/choi_jump", 1, true, 8.0f);
	anim_fall = new Animation("image/choi_jump", 1, true, 8.0f);
	anim_attack = new Animation("image/choi_Attack", 6, false, 16.0f);
	anim_protect = new Animation("image/choi_defense/1", 8, false, 16.0f);
	anim_sk1 = new Animation("image/choi_gabal", 11, false, 4.0f);
	anim_sk2 = new Animation("image/choi_ThinkAdd", 9, false, 16.0f);
	anim_suq = new Animation("image/choi_Sun", 10, false, 8.0f);
	anim_damage = new Animation("Sources/Temp/Damage", 4, false, 8.0f);
	anim_whileProtect = new Animation("image/choi_defense/2", 2, true, 8.0f);
	//anim_death = new Animation("Sources/Temp/Death", 4);
	effect_Anim_Def = new Animation("Sources/Player4/effect", 8, false, 14.0f);
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
	addChild(effect_Anim_Def); effect_Anim_Def->visible = false;
	addChild(anim_whileProtect); anim_whileProtect->visible = false;

	//Default Animation Setting
	currentAnim = anim_idle;
	currentAnim->visible = true;
	PlayerFrame::moveSpeed = 100.0f;
	PlayerFrame::jumpSpeed = 600.0f;

	Skill1Timer = new Timer();
	Skill1Timer->onTick = [=]() {
		skill1bool = true;
	};

	uniTimer = new Timer();
	uniTimer->onTick = [=]() {
		unibool = true;
	};

	this->pos.x = 300;
	this->pos.y = 200;
	boomerang = NULL;
	scaleCenter = currentAnim->center();
	rect = currentAnim->rect;
	SetPlayerRect();
	returnboomerang = false;

	SetDamage(3.0f, 15.0f, 8.0f, 10);
}


Player_01::~Player_01()
{
}

void Player_01::update(float dt)
{
	PlayerFrame::update(dt);

	if (skill1bool == true)
	{
		nowPosition = this->pos;

		boomerang = new Projectile(this, 300, "image/gabal", 13);
		boomerang->damage = sk1_Damage;
		returnboomerang = false;
		world.currentScene->addChild(boomerang);
		LOCAL_GM->addSkillObject(boomerang);
		skill1bool = false;

	}

	if (boomerang != NULL && returnboomerang == false) {
		if (boomerang->pos.x > nowPosition.x + 300)
		{
			returnboomerang = true;
		}
		if (boomerang->pos.x < nowPosition.x - 200)
		{
			returnboomerang = true;
		}
	}
	if (returnboomerang)
	{
		if (this->rectWithPos().intersects(boomerang->rectWithPos())) {
			removeChild(boomerang);
		}
		if (this->pos.x > boomerang->pos.x)
			boomerang->pos.x += 600 * dt;
		if (this->pos.x < boomerang->pos.x)
			boomerang->pos.x -= 600 * dt;

		if (this->pos.y < boomerang->pos.y)
			boomerang->pos.y -= 300 * dt;
		if (this->pos.y > boomerang->pos.y)
			boomerang->pos.y += 300 * dt;
	}

	if (unibool == true)
	{
		EnemyPos->moveSpeed = 200;
		EnemyPos->jumpSpeed = 600;

		EnemyPos2->moveSpeed = 200;
		EnemyPos2->jumpSpeed = 600;

		EnemyPos3->moveSpeed = 200;
		EnemyPos3->jumpSpeed = 600;

		unibool = false;
	}
}

void Player_01::AnimationController(float dt)
{
	PlayerFrame::AnimationController(dt);

}

void Player_01::Attack()
{
	PlayerFrame::Attack();


	Projectile * pro = new Projectile(this, 0.0f, "", 0);

	world.currentScene->addChild(pro);
	LOCAL_GM->addSkillObject(pro);

	effect_Anim_Def->visible = true;
	effect_Anim_Def->reset();

	pro->damage = this->def_Damage;
	pro->rect = effect_Anim_Def->rect;

	def = pro;
	pro->rect.right -= 40.0f;
	pro->rect.left += 40.0f;

	this->color = D3DXCOLOR(1, 1, 1, 1);
}

void Player_01::Skill_1()
{
	PlayerFrame::Skill_1();
	printf("Player01 Skill_1 \n");


	Skill1Timer->reset(0.92f, 1);

	this->color = D3DXCOLOR(1, 1, 1, 1);
	//구ㅡ현
}

void Player_01::Skill_2()
{
	PlayerFrame::Skill_2();
	printf("Player01 Skill_2 \n");

	Projectile * pro = new Projectile(this, 0.0f, "", 0);

	world.currentScene->addChild(pro);
	LOCAL_GM->addSkillObject(pro);

	effect_Anim_Def->visible = true;
	effect_Anim_Def->reset();

	pro->damage = sk2_Damage;
	pro->rect = effect_Anim_Def->rect;

	def = pro;
	pro->rect.right -= 40.0f;
	pro->rect.left += 40.0f;

	this->color = D3DXCOLOR(1, 1, 1, 1);
	//구ㅡ현
}

void Player_01::Skill_Unique()
{
	PlayerFrame::Skill_Unique();
	printf("Player01 Skill_Unique \n");

	EnemyPos = LOCAL_GM->GetEnemy(this, 0);

	EnemyPos->moveSpeed = 0;
	EnemyPos->jumpSpeed = 0;

	EnemyPos2 = LOCAL_GM->GetEnemy(this,1);

	EnemyPos2->moveSpeed = 0;
	EnemyPos2->jumpSpeed = 0;

	EnemyPos3 = LOCAL_GM->GetEnemy(this, 2);

	EnemyPos3->moveSpeed = 0;
	EnemyPos3->jumpSpeed = 0;

	uniTimer->reset(5.0f, 1);

	this->color = D3DXCOLOR(1, 1, 1, 1);
	//구ㅡ현
}
