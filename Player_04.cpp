#include "DXUT.h"
#include "Player_04.h"
#include "Projectile.h"

//ÀÌÀçÈÆ

Player_04::Player_04(bool isLocal) : PlayerFrame(100.0f, 1.0f, 3.0f, 7.0f, "Player04", isLocal), def(nullptr) 
{
	//Animation Setting
	anim_idle = new Animation("Sources/Player4/Idle", 7, true, 8.0f);
	anim_walk = new Animation("Sources/Player4/move", 8, true, 8.0f);
	anim_jump = new Animation("Sources/Player4/Jump", 1, true, 8.0f);
	anim_fall = new Animation("Sources/Player4/Jump", 1, true, 8.0f);
	anim_attack = new Animation("Sources/Player4/Attack", 7, false, 14.0f);
	anim_protect = new Animation("Sources/Player4/defend", 1, true, 8.0f);
	anim_sk1 = new Animation("Sources/Player4/sk1", 20, false, 16.0f);
	anim_sk2 = new Animation("Sources/Player4/sk2", 12, false, 16.0f);
	anim_suq = new Animation("image/skillicon/zedu", 1, false, 16.0f);
	anim_damage = new Animation("Sources/Temp/Damage", 4, false, 8.0f);
	//anim_death = new Animation("Sources/Temp/Death", 4);

	//anim_Effect
	effect_Anim_Def = new Animation("Sources/Player4/effect",8, false, 14.0f);
	effect_Skill2 = new Animation("Sources/Player4/effect", 8, false, 8.0f);

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
	addChild(effect_Skill2); effect_Skill2->visible = false;

	effect_Skill2->scale.x *= 2.0f;

	//Default Animation Setting
	currentAnim = anim_idle;
	currentAnim->visible = true;

	//Speed Setting
	PlayerFrame::moveSpeed = 100.0f;
	PlayerFrame::jumpSpeed = 600.0f;

	//ScaleCenter Setting - For Render
	scaleCenter = currentAnim->center();
	rect = currentAnim->rect;
	SetPlayerRect();

	sk1timer = new Timer();
	sk1timer->onTick = [=]() {
		shoot = true;
	};

	SetDamage(3.0f, 15.0f, 8.0f, 10);
}


Player_04::~Player_04()
{
	sk1timer->removing = true;
}

void Player_04::update(float dt)
{
	PlayerFrame::update(dt);

	if (effect_Anim_Def->isEnd && def != nullptr) {
		effect_Anim_Def->visible = false;
		def->removing = true;
		def = nullptr;
	}
	effect_Anim_Def->update(dt);
	
	if (effect_Skill2->isEnd && def != nullptr) {
		effect_Skill2->visible = false;
		def->removing = true;
		def = nullptr;
	}
	effect_Skill2->update(dt);

	if (shoot == true)
	{
		//Skill_1
		Projectile* pro = new Projectile(this, 700, "Sources/Player4/sigong", 2);
		world.currentScene->addChild(pro);
		LOCAL_GM->addSkillObject(pro);

		pro->damage = sk1_Damage;

		shoot = false;
	}
}

void Player_04::Attack() {
	PlayerFrame::Attack();

	asset.sounds[L"Sources/Sound/punch.wav"]->Play();

	Projectile * pro = new Projectile(this, 0.0f, "Sources/Player4/effect", 0);
	
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

void Player_04::Skill_1()
{
	PlayerFrame::Skill_1();
	asset.sounds[L"Sources/Sound/sigong.wav"]->Play();
	sk1timer->reset(1.25f, 1);
	

	this->color = D3DXCOLOR(1, 1, 1, 1);
}

void Player_04::Skill_2()
{
	PlayerFrame::Skill_2();

	Projectile * pro = new Projectile(this, 0.0f, "", 0);
	//Animation Movement

	pro->pos.x = this->pos.x + 50;
	pro->pos.y = this->pos.y - 20;

	pro->rect = effect_Skill2->rect;

	if (scale.x >= 1.0f) {
		pro->rect.right *= 1.35;
		pro->rect.right -= 50;
	}
	else {
		pro->rect.left -= pro->rect.right * 1.35;
		pro->rect.left += 50;
	}
	world.currentScene->addChild(pro);
	LOCAL_GM->addSkillObject(pro);

	pro->damage = sk2_Damage;
	
	effect_Skill2->reset();
	effect_Skill2->visible = true;

	def = pro;

	this->color = D3DXCOLOR(1, 1, 1, 1);
}

void Player_04::Skill_Unique()
{
	PlayerFrame::Skill_Unique();

	PlayerFrame* Enemy = LOCAL_GM->GetEnemy(this,1);


	if (Enemy->current_Hp_Gauge <= 30)
	{
		this->SetDamage(6,20,20,20);
	}
     Enemy = LOCAL_GM->GetEnemy(this, 2);


	if (Enemy->current_Hp_Gauge <= 30)
	{
		this->SetDamage(6, 20, 20, 20);
	}

	Enemy = LOCAL_GM->GetEnemy(this, 3);


	if (Enemy->current_Hp_Gauge <= 30)
	{
		this->SetDamage(6, 20, 20, 20);
	}

	Enemy = LOCAL_GM->GetEnemy(this, 4);


	if (Enemy->current_Hp_Gauge <= 30)
	{
		this->SetDamage(6, 20, 20, 20);
	}

	this->color = D3DXCOLOR(1, 1, 1, 1);
}
