#include "DXUT.h"
#include "PlayerFrame.h"
#include "World.h"
#include "Local_GameManager.h"

PlayerFrame::PlayerFrame(float HP, float defCT, float sk1CT, float sk2CT, string tag, bool isLocal, float max_shield_Gauge)
	: defCoolTime(defCT), sk1CoolTime(sk1CT), sk2CoolTime(sk2CT),
	use_protc(false), use_def(false), use_sk1(false), use_sk2(false), use_suq(false),
	canDef(false), canSk1(false), canSk2(false), isMine(true),
	current_suq_Gauge(0.0f), suq_Gauge_Max(10.0f), isGround(true), gravSpeed(981.0f), local_Player(isLocal), max_Hp_Gauge(HP),
	pastPos(0.0f, 0.0f), current_Hp_Gauge(HP), can_Use_Shield_Offset(3.0f),
	max_Shield_Gauge(max_shield_Gauge), shield_Dec(1.0f), shield_Gauge(max_shield_Gauge), waitGetDown(0.0f), canProtc(false),
	color(D3DXCOLOR(1,1,1,1))
	, lastGroundTag(FINALGROUND)
{
	anim_whileProtect = nullptr;
	this->tag = tag;
	def_Timer = new Timer();
	sk1_Timer = new Timer();
	sk2_Timer = new Timer();

	sk1_Timer->reset(sk1CoolTime, 1);
	sk1_Timer->onTick = [=]() {
		canSk1 = true;
	};

	sk2_Timer->reset(sk2CoolTime, 1);
	sk2_Timer->onTick = [=]() {
		canSk2 = true;
	};

	def_Timer->reset(defCoolTime, 1);
	def_Timer->onTick = [=] {
		canDef = true;
	};

	if (local_Player) {
		up = VK_UP;   down = VK_DOWN;   left = VK_LEFT;   right = VK_RIGHT;
		attack = 'H'; sk1 = 'J';   sk2 = 'K'; suq = 'L';
	}
	else {
		up = 'W';   down = 'S';   left = 'A';   right = 'D';
		sk1 = 'X';   sk2 = 'C'; attack = 'Z'; suq = 'V';
	}


}

PlayerFrame::~PlayerFrame()
{
	def_Timer->removing = true;
	sk1_Timer->removing = true;
	sk2_Timer->removing = true;

	/*SAFE_DELETE(anim_idle);      SAFE_DELETE(anim_walk);
	SAFE_DELETE(anim_jump);      SAFE_DELETE(anim_attack);
	SAFE_DELETE(anim_protect);   SAFE_DELETE(anim_fall);
	SAFE_DELETE(anim_sk1);      SAFE_DELETE(anim_sk2);
	SAFE_DELETE(anim_suq);      SAFE_DELETE(anim_damage);
	SAFE_DELETE(anim_death);*/

	pastPos = pos;
}

void PlayerFrame::update(float dt)
{
	//printf("Player Frame Test : %f \n", dt);

	if (!use_protc && !use_def && !use_sk1 && !use_sk2 && !use_suq) {
		//printf("Player Can Something! \n\n");

		if (canDef && world.getKeyState(attack) == 1 && isGround)                       //공격키를 누름
			Attack();

		else if (canSk1 && world.getKeyState(sk1) == 1 && isGround)                           //스킬키를 누름
			Skill_1();

		else if (canSk2 && world.getKeyState(sk2) == 1 && isGround)                           //스킬키를 누름
			Skill_2();

		else if (current_suq_Gauge >= suq_Gauge_Max && world.getKeyState(suq) == 1 && isGround)      //스킬키를 누름
			Skill_Unique();

		Move(dt);
	}

	//Shield Or Move Down
	if (world.getKeyState(down) >= 1) {
		waitGetDown += dt;
	}
	else {
		waitGetDown = 0.0f;
	}

	if (waitGetDown >= 0.2f && isGround)      //방어
		Protect(dt);
	else
		use_protc = false;

	if (!use_protc) {
		shield_Gauge += dt;

		if (shield_Gauge > max_Shield_Gauge)
			shield_Gauge = max_Shield_Gauge;
	}

	AnimationController(dt);
	current_suq_Gauge += dt;
	pastPos.x = pos.x;
	pastPos.y = pos.y;

	currentAnim->color = this->color;
}

//---------------------------------------------------
Vec2 PlayerFrame::GetMoveDir()
{
	Vec2 _moveDir;
	if (pastPos.x > pos.x)
		_moveDir.x = -1.0f;
	else if (pastPos.x < pos.x)
		_moveDir.x = 1.0f;
	else
		_moveDir.x = 0.0f;

	if (pastPos.y > pos.y)
		_moveDir.y = 1.0f;
	else if (pastPos.y < pos.y)
		_moveDir.y = -1.0f;
	else
		_moveDir.y = 0.0f;

	return _moveDir;
}

void PlayerFrame::AnimationController(float dt)
{
	//For Online
	Vec2 _moveDir = GetMoveDir();
	currentAnim->update(dt);

	if (isMine) {

		//Default Attack Animation
		if (use_def) {
			if (currentAnim != anim_attack) {
				SwapAnimation(anim_attack);
			}

			if (currentAnim->isEnd) {
				SwapAnimation(anim_idle);
				use_def = false;
			}

			return;
		}
		//Skill1 Animation
		else if (use_sk1) {
			if (currentAnim != anim_sk1) {
				SwapAnimation(anim_sk1);
			}
			if (currentAnim->isEnd) {
				SwapAnimation(anim_idle);
				use_sk1 = false;
			}
			return;
		}

		else if (use_sk2) {
			if (currentAnim != anim_sk2) {
				SwapAnimation(anim_sk2);
			}
			if (currentAnim->isEnd) {
				SwapAnimation(anim_idle);
				use_sk2 = false;
			}
			return;
		}

		else if (use_suq) {
			if (currentAnim != anim_suq) {
				SwapAnimation(anim_suq);
			}
			if (currentAnim->isEnd) {
				SwapAnimation(anim_idle);
				use_suq = false;
			}
			return;
		}

		else if (use_protc) {
			if (anim_whileProtect != nullptr) {
				if (currentAnim == anim_protect && currentAnim->isEnd) {
					SwapAnimation(anim_whileProtect);
					return;
				}
				else if (currentAnim == anim_whileProtect) {
					return;
				}
			}
			if (currentAnim != anim_protect) {
				SwapAnimation(anim_protect);
			}

			return;
		}

		//Animation Movement
		if (_moveDir.x >= 1.0f) {
			scale.x = 1;

			if (currentAnim != anim_walk && isGround) {
				SwapAnimation(anim_walk);
			}
		}

		else if (_moveDir.x <= -1.0f) {
			scale.x = -1;

			if (currentAnim != anim_walk && isGround) {
				SwapAnimation(anim_walk);
			}
		}

		//Jump / Fall Animation
		if (_moveDir.y >= 1.0f) {
			if (currentAnim != anim_jump) {
				SwapAnimation(anim_jump);
			}
		}
		else if (_moveDir.y <= -1.0f) {
			if (currentAnim != anim_fall) {
				SwapAnimation(anim_fall);
			}
		}
		else if (_moveDir.x == 0.0f) {
			if (currentAnim != anim_idle)
				SwapAnimation(anim_idle);
		}
	}
	else {
		//Online Player Animation
	}
}

void PlayerFrame::SwapAnimation(Animation * value)
{
	currentAnim->visible = false;
	currentAnim = value;
	currentAnim->visible = true;
	currentAnim->reset();
}

void PlayerFrame::SetPlayerRect()
{
	cout << tag;
	rect.left += 20; rect.right -= 20;
	rect.top += 28; rect.bottom -= 20;
	printf(" Rect Set Test / %d %d %d %d \n", rect.left, rect.right, rect.top, rect.bottom);

	footBoxCollider = rect;
	footBoxCollider.top = footBoxCollider.bottom * 3 / 4;
	footBoxCollider.bottom -= 28;
}

void PlayerFrame::SetDamage(float dfD, float s1D, float s2D, float s3D)
{
	def_Damage = dfD;
	sk1_Damage = s1D;
	sk2_Damage = s2D;
	suq_Damage = s3D;
}

void PlayerFrame::getDamage(float damageValue)
{

	if (this->use_protc) {
		printf("Shield Hit! \n");
		current_Hp_Gauge -= damageValue * 0.3f;
	}

	else {
		printf("Skill Hit! \n");
		current_Hp_Gauge -= damageValue;
		isHit = true;
	}

	printf("Current Hp : %f \n", current_Hp_Gauge);
}

void PlayerFrame::Move(float dt)
{
	//printf("Player Pos / X : %f, Y : %f \n", pos.x, pos.y);

	//중력
	if (!isGround) {
		currentJumpSpeed -= gravSpeed * dt;
		pos.y -= currentJumpSpeed * dt;
	}
	else {
		currentJumpSpeed = 0;
	}

	currentGroundTag = LOCAL_GM->CheckGround(this);

	if (currentGroundTag != "" && currentJumpSpeed < 0.0f) {
		if (currentGroundTag == FINALGROUND || currentGroundTag != lastGroundTag) {
			isGround = true;
			pos.y = (int)pos.y;
		}
	}

	else if (currentGroundTag == "" || (0.0f < waitGetDown && waitGetDown < 0.2f)) {
		if (world.getKeyState(down) >= 2) {}
		else if (currentJumpSpeed == 0.0f) {
			isGround = false;
			lastGroundTag = currentGroundTag;
		}
	}

	if (world.getKeyState(up) == 1 && isGround) {
		currentJumpSpeed = jumpSpeed;
		lastGroundTag = "";
		isGround = false;
	}

	else if (world.getKeyState(left) >= 1) {
		scale.x = -1.0f;
		pos.x -= moveSpeed * dt;
	}

	else if (world.getKeyState(right) >= 1) {
		scale.x = 1.0f;
		pos.x += moveSpeed * dt;
	}

	if (this->pos.x < 30.0f) {
		this->pos.x = 30.0f;
	}
	else if (this->pos.x > 1170.0f) {
		this->pos.x = 1170.0f;
	}
}

void PlayerFrame::Protect(float dt)
{
	printf("Shield_Gauge : %.2f\n", shield_Gauge);

	if (!canProtc)
		if (shield_Gauge > 3.0f)
			canProtc = true;
		else
			return;

	if (shield_Gauge - shield_Dec < 0.0f) {
		canProtc = false;
		use_protc = false; return;
	}

	use_protc = true;
	shield_Gauge -= shield_Dec * dt * 2;
}

void PlayerFrame::Attack()
{
	printf("Attack \n");
	def_Timer->reset(defCoolTime, 1);
	canDef = false;
	use_def = true;
}

void PlayerFrame::Skill_1() {
	printf("Skill_1 \n");
	sk1_Timer->reset(sk1CoolTime, 1);
	canSk1 = false;
	use_sk1 = true;
}

void PlayerFrame::Skill_2() {
	printf("Skill_2 \n");
	sk2_Timer->reset(sk2CoolTime, 1);
	canSk2 = false;
	use_sk2 = true;
}

void PlayerFrame::Skill_Unique() {
	printf("Skill_Unique \n");
	current_suq_Gauge = 0.0f;
	use_suq = true;
}