#pragma once
#include "Projectile.h"
class WigGuidedMissile :
	public Projectile
{
public:
	PlayerFrame * target;

	WigGuidedMissile(PlayerFrame * target, PlayerFrame * parent, float moveSpeed, const string& uri,
		int frameCount, float fps = 20, bool loop = true, bool png = true);
	~WigGuidedMissile();

	void update(float dt);
};

