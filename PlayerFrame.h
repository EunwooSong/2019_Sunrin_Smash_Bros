#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"
#include "Asset.h"
/*
각 캐릭터 마다 설정할 값
 - moveSpeed
 - jumpSpeed
 - current_Hp_Gauge
 - suq_Gauge_Max
 - def_Damage
 - shield_Dec
 - sk1, sk2, suq Damage
   (패시브 스킬 및 궁국이이면 스킵, 알아서 사용)
 - FootBoxCollider

Loop Animation
 - anim_idle
 - anim_walk
 - anim_fall
*/

class PlayerFrame :
	public Entity
{
public:
	//=-----------Key Input-----------=
	char up;   char down;
	char left;   char right;
	char sk1;   char sk2;
	char suq;   char attack;

	//=-----------Speed-----------=
	float moveSpeed;      //이동 속도
	float currentJumpSpeed; //현재 점프 속도
	float jumpSpeed;      //점프 속도
	float gravSpeed;      //중력 속도

	//=-----------Gauge-----------=
	float current_Hp_Gauge;     //체력 게이지
	float max_Hp_Gauge;         //최대 체력
	float current_suq_Gauge;   //유니크 게이지
	float suq_Gauge_Max;      //유니크 게이지 최댓값
	float shield_Gauge;         //쉴드 게이지
	float can_Use_Shield_Offset;//쉴드 최소 사용 범위
	float max_Shield_Gauge;      //쉴드 최대량

	//=-----------Damage-----------=0
	float def_Damage;   //기본 공격 데미지
	float shield_Dec;   //쉴드 감소값
	float sk1_Damage;   //스킬 1 데미지
	float sk2_Damage;   //스킬 2 데미지
	float suq_Damage;   //유니크 스킬 데미지

	//=-----------Bool-----------=
	bool isMeleeAttack;		//근접 공격이라 충돌하면 공격을 받는지
	bool isMine;			//이 플레이어가 나인지
	bool isHit;				//공격 받았는지

	bool canDef;      //기본 공격 가능
	bool canSk1;      //스킬1 사용가능
	bool canSk2;      //스킬2 사용가능
	bool canProtc;     //방어 가능

	bool local_Player;   //로컬 플레이어?

	//For Animation(Online Values)
	bool use_def;      //기본 공격
	bool use_protc;      //방어
	bool use_sk1;      //스킬 1
	bool use_sk2;      //스킬 2
	bool use_suq;      //스킬 유니크

	//=-----------Pos(For Aniamtion)-----------=
	Vec2 pastPos;

	//=-----------Box Collider-----------=
	Rect footBoxCollider;   //발 범위
	Rect RAttackBoxCollider;   //오른쪽 공격 범위
	Rect LAttackBoxCollider;   //왼쪽 공격 범위

	//=-----------Animation-----------=
	Animation * anim_idle;      //Idle
	Animation * anim_walk;      //Walk
	Animation * anim_jump;      //Jump
	Animation * anim_attack;   //Attack
	Animation * anim_protect;   //Protect(Shield)
	Animation * anim_whileProtect;
	Animation * anim_fall;      //Fall
	Animation * anim_sk1;      //Skill_1
	Animation * anim_sk2;      //Skill_2 
	Animation * anim_suq;      //Skill_Unique
	Animation * anim_damage;   //GetDamage
	Animation * anim_death;      //Death

	Animation * currentAnim;

	//=-----------Timer-----------=
	Timer * def_Timer;
	Timer * sk1_Timer;
	Timer * sk2_Timer;

	Timer * getDamage_Timer;
	D3DXCOLOR color;

	//=-----------CoolTime-----------=
	float waitGetDown;
	float defCoolTime;
	float sk1CoolTime;
	float sk2CoolTime;

	//=-----------CheckGround-----------=
	string lastGroundTag;
	string currentGroundTag;
	bool isGround;         //땅에 닿았는지

public:

	PlayerFrame(float HP, float defCT, float sk1CT,
		float sk2CT, string tag, bool isLocal = false,
		float max_shield_Gauge = 10.0f);

	~PlayerFrame();

	virtual void update(float dt);

	//=-----------For Online-----------=
	Vec2 GetMoveDir();
	virtual void AnimationController(float dt);
	void SwapAnimation(Animation * value);

	void SetPlayerRect();
	void SetDamage(float dfD = 0.0f, float s1D = 0.0f,
		float s2D = 0.0f, float s3D = 0.0f);
	void getDamage(float damageValue); //피해 받음

protected:
	virtual void Move(float dt);
	virtual void Attack();
	virtual void Protect(float dt);
	virtual void Skill_1();
	virtual void Skill_2();
	virtual void Skill_Unique();
};