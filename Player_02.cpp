#include "DXUT.h"
#include "Player_02.h"
 
//유명환
Player_02::Player_02(bool isLocal) : PlayerFrame(100.0f, 1.0f, 5.0f, 10.0f, "Player02", isLocal), def(nullptr)
{
	//Animation Setting
	anim_idle = new Animation("image/U_idle", 8, true, 8.0f);
	anim_walk = new Animation("image/U_move", 8, true, 8.0f);
	anim_jump = new Animation("image/U_jump", 1, true, 8.0f);
	anim_fall = new Animation("image/U_jump", 1, true, 8.0f);
	anim_attack = new Animation("image/U_Attack", 7, false, 8.0f);
	anim_protect = new Animation("image/U_defende", 1, false, 8.0f);
	anim_sk1 = new Animation("image/U_Zer0penOut", 10, false, 4.0f);
	anim_sk2 = new Animation("image/U_Anim", 22, false, 8.0f);
	anim_suq = new Animation("image/U_Blacklist", 11, false, 4.0f);
	anim_damage = new Animation("Sources/Temp/Damage", 4, false, 8.0f);
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

	//Default Animation Setting
	currentAnim = anim_idle;
	currentAnim->visible = true;
	PlayerFrame::moveSpeed = 100.0f;
	PlayerFrame::jumpSpeed = 600.0f;

	Skill1Timer = new Timer();
	Skill1Timer->onTick = [=]() {
		Skill1boo1 = true;
	};

	this->pos.x = 300;
	this->pos.y = 200;
	scaleCenter = currentAnim->center();
	rect = currentAnim->rect;
	SetPlayerRect();

	SetDamage(3.0f, 10.0f, 6.0f, 10);
}

void Player_02::update(float dt)
{
	PlayerFrame::update(dt);

	if (Skill1boo1){
	
		WigGuidedMissile* wd = new WigGuidedMissile(Enemy, this, 300, "image/Masage", 1);
		world.currentScene->addChild(wd);
		LOCAL_GM->addSkillObject(wd);
		Skill1boo1 = false;

		PlayerFrame* Enemy = LOCAL_GM->GetEnemy(this, -1);
		Enemy->color = D3DXCOLOR(1, 1, 1, 1);
	}
}

void Player_02::Attack()
{
	PlayerFrame::Attack();

	asset.sounds[L"Sources/Sound/chack.wav"]->Play();

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

void Player_02::Skill_1()
{
	PlayerFrame::Skill_1();
	printf("Player02 Skill_1 \n");
	Enemy = LOCAL_GM->GetEnemy(this);
	Skill1Timer->reset(1.5f, 1);


	this->color = D3DXCOLOR(1, 1, 1, 1);
	//구ㅡ현
}

void Player_02::Skill_2()
{
	PlayerFrame::Skill_2();
	printf("Player02 Skill_2 \n");

	this->current_Hp_Gauge += 10;


	this->color = D3DXCOLOR(1, 1, 1, 1);
	//구ㅡ현
}

void Player_02::Skill_Unique()
{
	PlayerFrame::Skill_Unique();
	printf("Player02 Skill_Unique \n");

	PlayerFrame* Enemy = LOCAL_GM->GetEnemy(this);

	Enemy->current_Hp_Gauge -= this->sk1_Damage;


	this->color = D3DXCOLOR(1, 1, 1, 1);
	//구ㅡ현
}

Player_02::~Player_02()
{
}
