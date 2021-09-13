#include "DXUT.h"
#include "Projectile.h"

Projectile::Projectile(PlayerFrame * parent, float moveSpeed, const string& uri,
						int frameCount, float fps, bool loop, bool png) :
	moveSpeed(moveSpeed), parent(parent)
{
	if (frameCount != 0) {
		anim_Projectile = new Animation(uri, frameCount, loop, fps, png);
		addChild(anim_Projectile);
		this->rect = anim_Projectile->rect;
	}
	else
		anim_Projectile = nullptr;

	moveDir = parent->scale.x;
	scale.x = moveDir;

	pos.x = parent->pos.x;
	pos.y = parent->pos.y + 40;

	autoRemove = new Timer();
	autoRemove->reset(10.0f, 1);
	autoRemove->onTick = [=] {
		autoRemove->removing = true;
		this->parent->removeChild(this);
		cout<<"Auto Remove Complet!"<<endl;
	};
}

void Projectile::update(float dt)
{
	this->pos.x += moveDir * moveSpeed * dt;
	
	if(anim_Projectile != nullptr)
		anim_Projectile->update(dt);
}

Projectile::~Projectile()
{
	autoRemove->removing = true;
	removing = true;
}
