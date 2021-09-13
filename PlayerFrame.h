#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"
#include "Asset.h"
/*
�� ĳ���� ���� ������ ��
 - moveSpeed
 - jumpSpeed
 - current_Hp_Gauge
 - suq_Gauge_Max
 - def_Damage
 - shield_Dec
 - sk1, sk2, suq Damage
   (�нú� ��ų �� �ñ����̸� ��ŵ, �˾Ƽ� ���)
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
	float moveSpeed;      //�̵� �ӵ�
	float currentJumpSpeed; //���� ���� �ӵ�
	float jumpSpeed;      //���� �ӵ�
	float gravSpeed;      //�߷� �ӵ�

	//=-----------Gauge-----------=
	float current_Hp_Gauge;     //ü�� ������
	float max_Hp_Gauge;         //�ִ� ü��
	float current_suq_Gauge;   //����ũ ������
	float suq_Gauge_Max;      //����ũ ������ �ִ�
	float shield_Gauge;         //���� ������
	float can_Use_Shield_Offset;//���� �ּ� ��� ����
	float max_Shield_Gauge;      //���� �ִ뷮

	//=-----------Damage-----------=0
	float def_Damage;   //�⺻ ���� ������
	float shield_Dec;   //���� ���Ұ�
	float sk1_Damage;   //��ų 1 ������
	float sk2_Damage;   //��ų 2 ������
	float suq_Damage;   //����ũ ��ų ������

	//=-----------Bool-----------=
	bool isMeleeAttack;		//���� �����̶� �浹�ϸ� ������ �޴���
	bool isMine;			//�� �÷��̾ ������
	bool isHit;				//���� �޾Ҵ���

	bool canDef;      //�⺻ ���� ����
	bool canSk1;      //��ų1 ��밡��
	bool canSk2;      //��ų2 ��밡��
	bool canProtc;     //��� ����

	bool local_Player;   //���� �÷��̾�?

	//For Animation(Online Values)
	bool use_def;      //�⺻ ����
	bool use_protc;      //���
	bool use_sk1;      //��ų 1
	bool use_sk2;      //��ų 2
	bool use_suq;      //��ų ����ũ

	//=-----------Pos(For Aniamtion)-----------=
	Vec2 pastPos;

	//=-----------Box Collider-----------=
	Rect footBoxCollider;   //�� ����
	Rect RAttackBoxCollider;   //������ ���� ����
	Rect LAttackBoxCollider;   //���� ���� ����

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
	bool isGround;         //���� ��Ҵ���

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
	void getDamage(float damageValue); //���� ����

protected:
	virtual void Move(float dt);
	virtual void Attack();
	virtual void Protect(float dt);
	virtual void Skill_1();
	virtual void Skill_2();
	virtual void Skill_Unique();
};