#pragma once
#include "PlayerFrame.h"
#include "World.h"
#include "Entity.h"
#include "Sprite.h"
#include "Projectile.h"

#define FINALGROUND "FinalGround"

#define LOCAL_GM Local_GameManager::GetInstance()

class Local_GameManager
{
public:
	vector<PlayerFrame *> players;
	vector<Entity *> Map_Object;
	vector<Projectile *> Skill_Object;

public:
	bool isEnd;

	Timer* redtime;
	Timer* redtime2;
	bool redbool = false;
	bool redbool2 = false;
	Local_GameManager();
	~Local_GameManager();

	static Local_GameManager * GetInstance();

	virtual void addSkillObject(Projectile * obj);
	virtual void addMapObject(Entity * obj);

 void addPlayer(PlayerFrame * me);

	virtual void gameReset();

	virtual void Update_GameManager(float dt);
	PlayerFrame * GetEnemy(PlayerFrame * me, float index = 0);

	string CheckGround(PlayerFrame * me);
	void CheckSkillHit(PlayerFrame * me);
};