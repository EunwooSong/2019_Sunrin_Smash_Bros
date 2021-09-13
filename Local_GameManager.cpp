#include "DXUT.h"
#include "Local_GameManager.h"

Local_GameManager::Local_GameManager() :
	isEnd(false), redbool(true) {
	redtime = new Timer();
	redtime->onTick = [=]() {
		redbool = true;
	};

	redtime2 = new Timer();
	redtime2->onTick = [=]() {
		redbool2 = true;
	};
}


Local_GameManager::~Local_GameManager()
{
}

Local_GameManager * Local_GameManager::GetInstance()
{
	static Local_GameManager * local_Gm = new Local_GameManager();
	return local_Gm;
}

void Local_GameManager::addSkillObject(Projectile * obj)
{
	Skill_Object.push_back(obj);
}

void Local_GameManager::addMapObject(Entity * obj)
{
	Map_Object.push_back(obj);
}

void Local_GameManager::addPlayer(PlayerFrame * me)
{
	players.push_back(me); 
}

void Local_GameManager::gameReset()
{
	for (auto obj : Skill_Object)
		obj->removing = true;


	Skill_Object.erase(remove_if(Skill_Object.begin(), Skill_Object.end(),
		[&](auto iter) {
		bool removing = iter->removing;
		return removing;
	}), Skill_Object.end());

	for (auto obj : Map_Object) {
		obj->removing = true;
	}

	printf("GAME MGR RESET COMPELTE!\n");
}

void Local_GameManager::Update_GameManager(float dt)
{
	for (auto player : players) {
		CheckSkillHit(player);
	}
}

PlayerFrame * Local_GameManager::GetEnemy(PlayerFrame * me, float index)
{
	if (players.size() == 0)
		return me;

	//size
	if (players.size() == 2) {
		if (players[0] == me)
			return players[1];
		else
			return players[0];
	}

	//가까운 플레이어
	else if (index == -1) {
		float minLen = 10000.0f;
		float tmp = 0.0f;
		PlayerFrame * target;
		PlayerFrame * least;

		for (int i = 0; i < 4; i++) {
			target = players[i];

			tmp = sqrt(pow(me->pos.x - target->pos.x, 2) + pow(me->pos.y - target->pos.y, 2));

			if (minLen > tmp) {
				least = target;
				minLen = tmp;
			}
		}

		return least;
	}

	//index
	else if (index != -1) {
		index = clamp(index, 0, players.size());
		return players[index];
	}
}

string Local_GameManager::CheckGround(PlayerFrame * me)
{
	Rect temp = me->footBoxCollider.offset(me->pos);

	//오류 방지
	if (Map_Object.size() == 0) {
		if (me->pos.y >= 600.0f) {
			return FINALGROUND;
		}
	}

	for (auto map : Map_Object) {
		if (temp.intersects(map->rectWithPos())) {
			if (me->lastGroundTag != map->tag)
				return map->tag;
			if (map->tag == FINALGROUND)
				return FINALGROUND;
		}
	}

	return "";
}

void Local_GameManager::CheckSkillHit(PlayerFrame * me) {
	for (auto obj : Skill_Object) {
		if (me->rectWithPos().intersects(obj->rectWithPos()))
			if (me != obj->parent) {
				if (me->local_Player == true && !me->use_protc) {
					me->color = D3DXCOLOR(1,0,0,1);
					redtime->reset(0.1f, 1);
				}
				if (me->local_Player == false&& !me->use_protc) {
					me->color = D3DXCOLOR(1, 0, 0, 1);
					redtime2->reset(0.1f, 1);
				}
				me->getDamage(obj->damage);
				obj->removing = true;
				world.currentScene->shake(0.01f, 3, 10);
			}
	}
	if (redbool == true && me->local_Player == true) {
		me->color = D3DXCOLOR(1, 1, 1, 1);
		redbool = false;
	}
	if (redbool2 == true && me->local_Player == false) {
		me->color = D3DXCOLOR(1, 1, 1, 1);
		redbool2 = false;
	}
	//제거
	Skill_Object.erase(remove_if(Skill_Object.begin(), Skill_Object.end(),
		[&](auto iter) {
		bool removing = iter->removing;
		return removing;
	}), Skill_Object.end());



}
