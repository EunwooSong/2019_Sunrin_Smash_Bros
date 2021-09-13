#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerFrame.h"
#include "Timer.h"

class Projectile
	: public Entity
{
public :

	
	Animation * anim_Projectile;
	PlayerFrame * parent;

	Timer * autoRemove;

	float moveDir;
	float moveSpeed;
	float damage;

public:
	Projectile(PlayerFrame * parent, float moveSpeed,
		const string& uri, int frameCount, float fps = 20,
		bool loop = true, bool png = true);

	virtual void update(float dt);

	~Projectile();
};

