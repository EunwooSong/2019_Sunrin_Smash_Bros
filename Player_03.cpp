#include "DXUT.h"
#include "Player_03.h"
#include "Local_GameManager.h"

Player_03::Player_03(bool isLocal) : PlayerFrame(100.0f, 1.0f, 5.0f, 10.0f, "Player03", isLocal), def(nullptr)
{
	//Animation Setting
	anim_idle = new Animation("Sources/Player3/Idle", 8, true, 8.0f);
	anim_walk = new Animation("Sources/Player3/Walk", 8, true, 8.0f);
	anim_jump = new Animation("Sources/Player3/Jump", 1, true, 8.0f);
	anim_fall = new Animation("Sources/Player3/Jump", 1, true, 8.0f);
	anim_attack = new Animation("Sources/Player3/Attack", 6, false, 8.0f);
	anim_protect = new Animation("Sources/Player3/Protect", 1, true);
	anim_sk1 = new Animation("Sources/Player3/Sk1", 15, false, 8.0f);
	anim_sk2 = new Animation("Sources/Player3/Sk2", 12, false, 8.0f);
	anim_suq = new Animation("Sources/Player3/Suq", 19, false, 8.0f);
	anim_damage = new Animation("Sources/Temp/Damage", 4, false, 8.0f);
	//anim_death = new Animation("Sources/Temp/Death", 4);
	effect_Anim_Def = new Animation("Sources/Player3/effect", 6, false, 8.0f);

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

	Skill2Timer = new Timer();
	Skill2Timer->onTick = [=]() {
		skill2bool = false;
	};

	Skill3Timer = new Timer();
	Skill3Timer->onTick = [=]() {
		skill3bool = true;
	};

	Skill1Timer = new Timer();
	Skill1Timer->onTick = [=]() {
		skill1bool = true;
	};


	SetDamage(2.0f, 7.0f, 8.0f, 10);
	suq_Gauge_Max = 20.0f;
}


Player_03::~Player_03()
{
	Skill1Timer->removing = true;
	Skill2Timer->removing = true;
	Skill3Timer->removing = true;
}

void Player_03::update(float dt)
{
	PlayerFrame::update(dt);
	
	if (effect_Anim_Def->isEnd && def != nullptr) {
		effect_Anim_Def->visible = false;
		def->removing = true;
		def = nullptr;
	}
	effect_Anim_Def->update(dt);

	if (skill2bool == false)
	{
		printf("이속비활성화");
		this->moveSpeed -= 100;
		this->sk1_Damage -= 7;
		this->sk2_Damage -= 7;
		this->def_Damage -= 7;
		//this->suq_Damage -= 7;
		skill2bool = true;
	}

	if (skill3bool == true)
	{
		Projectile* pro = new Projectile(this, 600, "Sources/Player3/Sk1/Black_Dragoon", 3);


		pro->scale.x = -pro->scale.x;

		world.currentScene->addChild(pro);
		skill3bool = false;
		pro->pos.y -= 70;
		pro->damage = this->sk1_Damage;

		pro->rect.right -= 28; pro->rect.left += 28;
		pro->rect.top += 40; pro->rect.bottom -= 40;

		LOCAL_GM->addSkillObject(pro);
	}

	if (skill1bool == true) {
		Projectile* guk = new Projectile(this, 300, "Sources/Player3/guk", 1);

		guk->pos.y -= 40.0f;
		guk->damage = this->sk2_Damage;

		world.currentScene->addChild(guk);
		LOCAL_GM->addSkillObject(guk);
		skill1bool = false;
	}
}

void Player_03::Attack() {
	PlayerFrame::Attack();

	asset.sounds[L"Sources/Sound/punch.wav"]->Play();

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

void Player_03::Skill_1()
{
	PlayerFrame::Skill_1();
	Skill3Timer->reset(1.3f, 1);

	this->color = D3DXCOLOR(1, 1, 1, 1);
}

void Player_03::Skill_2()
{
	PlayerFrame::Skill_2();
	Skill1Timer->reset(1.3f, 1);

	this->color = D3DXCOLOR(1, 1, 1, 1);

}

void Player_03::Skill_Unique()
{
	PlayerFrame::Skill_Unique();
	Skill2Timer->reset(10, 1);

	if (skill2bool == true) {
		printf("이속활성화");
		this->moveSpeed += 100;
		this->sk1_Damage += 7;
		this->sk2_Damage += 7;
		this->def_Damage += 7;
	}

	this->color = D3DXCOLOR(1, 1, 1, 1);
}