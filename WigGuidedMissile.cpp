#include "DXUT.h"
#include "WigGuidedMissile.h"

WigGuidedMissile::WigGuidedMissile(PlayerFrame * target, PlayerFrame * parent, float moveSpeed,
	const string & uri, int frameCount, float fps, bool loop, bool png)
	: Projectile(parent, moveSpeed, uri, frameCount, fps, loop, png), target(target)
{
	this->rect = anim_Projectile->rect;
	damage = parent->sk1_Damage;
}

WigGuidedMissile::~WigGuidedMissile()
{
}

void WigGuidedMissile::update(float dt) {
	Projectile::update(dt);

	if (sqrt((target->pos.x - pos.x) * (target->pos.x - pos.x)) <= 400) {
		if (target->pos.y <= pos.y)
			pos.y -= 100 * dt;

		else if (target->pos.y >= pos.y)
			pos.y += 100 * dt;
	}

	if (this->rectWithPos().intersects(target->rectWithPos())) {
		printf("¾Ó Ãæµ¹¶ì \n");
	}
}
