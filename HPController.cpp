#include "DXUT.h"
#include "HPController.h"
#include "World.h"
#include "Local_GameManager.h"

HPController::HPController(Scene * cs, string url1, string url2) : winner(nullptr), duce(false)
{
	fillSkillbar.clear();

	outFlame = new Sprite("image/UI/CONTENT.png");
	outFlame->scale.x = 0.5f;
	outFlame->scale.y = 0.5f;
	cs->addUI(outFlame);

	outFlame2 = new Sprite("image/UI/CONTENT.png");
	outFlame2->scale.x = -0.5f;
	outFlame2->scale.y = 0.5f;
	outFlame2->pos.x = 1280.0f;
	cs->addUI(outFlame2);

	Player1HP1 = new Sprite("image/Health/ga.png");
	Player1HP1->scale.x = 0.5f;
	Player1HP1->scale.y = 0.5f;
	Player1HP1->pos.x = 129.0f;
	Player1HP1->pos.y = 28.0f;
	cs->addUI(Player1HP1);

	Player1HP2 = new Sprite("image/Health/ga.png");
	Player1HP2->scale.x = 0.5f;
	Player1HP2->scale.y = 0.5f;
	Player1HP2->pos.x = 179.0f;
	Player1HP2->pos.y = 28.0f;
	cs->addUI(Player1HP2);

	Player1HP3 = new Sprite("image/Health/ga.png");
	Player1HP3->scale.x = 0.5f;
	Player1HP3->scale.y = 0.5f;
	Player1HP3->pos.x = 229.0f;
	Player1HP3->pos.y = 28.0f;
	cs->addUI(Player1HP3);

	Player1HP4 = new Sprite("image/Health/ga.png");
	Player1HP4->scale.x = 0.5f;
	Player1HP4->scale.y = 0.5f;
	Player1HP4->pos.x = 279.0f;
	Player1HP4->pos.y = 28.0f;
	cs->addUI(Player1HP4);

	Player1HP5 = new Sprite("image/Health/ga.png");
	Player1HP5->scale.x = 0.5f;
	Player1HP5->scale.y = 0.5f;
	Player1HP5->pos.x = 329.0f;
	Player1HP5->pos.y = 28.0f;
	cs->addUI(Player1HP5);

	////////////////////////////////////////////////
	Player2HP1 = new Sprite("image/Health/ga.png");
	Player2HP1->scale.x = -0.5f;
	Player2HP1->scale.y = 0.5f;
	Player2HP1->pos.x = 951.0f;
	Player2HP1->pos.y = 28.0f;
	cs->addUI(Player2HP1);

	Player2HP2 = new Sprite("image/Health/ga.png");
	Player2HP2->scale.x = -0.5f;
	Player2HP2->scale.y = 0.5f;
	Player2HP2->pos.x = 1001.0f;
	Player2HP2->pos.y = 28.0f;
	cs->addUI(Player2HP2);

	Player2HP3 = new Sprite("image/Health/ga.png");
	Player2HP3->scale.x = -0.5f;
	Player2HP3->scale.y = 0.5f;
	Player2HP3->pos.x = 1051.0f;
	Player2HP3->pos.y = 28.0f;
	cs->addUI(Player2HP3);

	Player2HP4 = new Sprite("image/Health/ga.png");
	Player2HP4->scale.x = -0.5f;
	Player2HP4->scale.y = 0.5f;
	Player2HP4->pos.x = 1101.0f;
	Player2HP4->pos.y = 28.0f;
	cs->addUI(Player2HP4);

	Player2HP5 = new Sprite("image/Health/ga.png");
	Player2HP5->scale.x = -0.5f;
	Player2HP5->scale.y = 0.5f;
	Player2HP5->pos.x = 1151.0f;
	Player2HP5->pos.y = 28.0f;
	cs->addUI(Player2HP5);
	/////////////////////////////////////////////////
	Player1si1 = new Sprite("image/Health/si.png");
	Player1si1->scale.x = 0.5f;
	Player1si1->scale.y = 0.5f;
	Player1si1->pos.x = 138.0f;
	Player1si1->pos.y = 5.0f;
	cs->addUI(Player1si1);

	Player1si2 = new Sprite("image/Health/si.png");
	Player1si2->scale.x = 0.5f;
	Player1si2->scale.y = 0.5f;
	Player1si2->pos.x = 173.0f;
	Player1si2->pos.y = 5.0f;
	cs->addUI(Player1si2);

	Player1si3 = new Sprite("image/Health/si.png");
	Player1si3->scale.x = 0.5f;
	Player1si3->scale.y = 0.5f;
	Player1si3->pos.x = 208.0f;
	Player1si3->pos.y = 5.0f;
	cs->addUI(Player1si3);

	Player1si4 = new Sprite("image/Health/si.png");
	Player1si4->scale.x = 0.5f;
	Player1si4->scale.y = 0.5f;
	Player1si4->pos.x = 243.0f;
	Player1si4->pos.y = 5.0f;
	cs->addUI(Player1si4);

	Player1si5 = new Sprite("image/Health/si.png");
	Player1si5->scale.x = 0.5f;
	Player1si5->scale.y = 0.5f;
	Player1si5->pos.x = 278.0f;
	Player1si5->pos.y = 5.0f;
	cs->addUI(Player1si5);
	////////////////////////////////////////////////

	Player2si1 = new Sprite("image/Health/si.png");
	Player2si1->scale.x = -0.5f;
	Player2si1->scale.y = 0.5f;
	Player2si1->pos.x = 1143.0f;
	Player2si1->pos.y = 5.0f;
	cs->addUI(Player2si1);

	Player2si2 = new Sprite("image/Health/si.png");
	Player2si2->scale.x = -0.5f;
	Player2si2->scale.y = 0.5f;
	Player2si2->pos.x = 1108.0f;
	Player2si2->pos.y = 5.0f;
	cs->addUI(Player2si2);

	Player2si3 = new Sprite("image/Health/si.png");
	Player2si3->scale.x = -0.5f;
	Player2si3->scale.y = 0.5f;
	Player2si3->pos.x = 1073.0f;
	Player2si3->pos.y = 5.0f;
	cs->addUI(Player2si3);

	Player2si4 = new Sprite("image/Health/si.png");
	Player2si4->scale.x = -0.5f;
	Player2si4->scale.y = 0.5f;
	Player2si4->pos.x = 1038.0f;
	Player2si4->pos.y = 5.0f;
	cs->addUI(Player2si4);

	Player2si5 = new Sprite("image/Health/si.png");
	Player2si5->scale.x = -0.5f;
	Player2si5->scale.y = 0.5f;
	Player2si5->pos.x = 1003.0f;
	Player2si5->pos.y = 5.0f;
	cs->addUI(Player2si5);

	printf("초기화 성공\n");
	// 7 12 15
	if (url1 == "jae") {
		Head1 = new Sprite("image/UI/head/leehead.png");
		skill1 = new Sprite("image/skillicon/hio.png");
		skill2 = new Sprite("image/skillicon/sc.png");
		skill3 = new Sprite("image/skillicon/zedu.png");
	}
	if (url1 == "song") {
		Head1 = new Sprite("image/UI/head/songhead.png");
		skill1 = new Sprite("image/skillicon/dragon.png");
		skill2 = new Sprite("image/skillicon/gukbab.png");
		skill3 = new Sprite("image/skillicon/drink.png");
	}
	if (url1 == "woo") {
		Head1 = new Sprite("image/UI/head/woohead.png");
		skill1 = new Sprite("image/skillicon/head.png");
		skill2 = new Sprite("image/skillicon/think.png");
		skill3 = new Sprite("image/skillicon/light.png");
	}
	if (url1 == "black") {
		Head1 = new Sprite("image/UI/head/blackhead.png");
		skill1 = new Sprite("image/skillicon/pho.png");
		skill2 = new Sprite("image/skillicon/nico.png");
		skill3 = new Sprite("image/skillicon/book.png");
	}

	if (url2 == "jae") {
		Head2 = new Sprite("image/UI/head/leehead.png");
		skill4 = new Sprite("image/skillicon/hio.png");
		skill5 = new Sprite("image/skillicon/sc.png");
		skill6 = new Sprite("image/skillicon/zedu.png");
	}
	if (url2 == "song") {
		Head2 = new Sprite("image/UI/head/songhead.png");
		skill4 = new Sprite("image/skillicon/dragon.png");
		skill5 = new Sprite("image/skillicon/gukbab.png");
		skill6 = new Sprite("image/skillicon/drink.png");
	}
	if (url2 == "woo") {
		Head2 = new Sprite("image/UI/head/woohead.png");
		skill4 = new Sprite("image/skillicon/head.png");
		skill5 = new Sprite("image/skillicon/think.png");
		skill6 = new Sprite("image/skillicon/light.png");
	}
	if (url2 == "black") {
		Head2 = new Sprite("image/UI/head/blackhead.png");
		skill4 = new Sprite("image/skillicon/pho.png");
		skill5 = new Sprite("image/skillicon/nico.png");
		skill6 = new Sprite("image/skillicon/book.png");
	}
	skill1->scale.x = 0.5;
	skill1->scale.y = 0.5;
	skill1->pos.x = 134;
	skill1->pos.y = 82;
	cs->addUI(skill1);

	skill2->scale.x = 0.5;
	skill2->scale.y = 0.5;
	skill2->pos.x = 212;
	skill2->pos.y = 82;
	cs->addUI(skill2);

	skill3->scale.x = 0.5;
	skill3->scale.y = 0.5;
	skill3->pos.x = 282;
	skill3->pos.y = 82;
	cs->addUI(skill3);

	skill4->scale.x = 0.5;
	skill4->scale.y = 0.5;
	skill4->pos.x = 962;
	skill4->pos.y = 82;
	cs->addUI(skill4);

	skill5->scale.x = 0.5;
	skill5->scale.y = 0.5;
	skill5->pos.x = 1040;
	skill5->pos.y = 82;
	cs->addUI(skill5);

	skill6->scale.x = 0.5;
	skill6->scale.y = 0.5;
	skill6->pos.x = 1107;
	skill6->pos.y = 82;
	cs->addUI(skill6);

	skillbar1 = new Sprite("image/skillicon/skillbar.png");
	skillbar1->scale.x = 0.5;
	skillbar1->scale.y = 0.5;
	skillbar1->pos.x = 134;
	skillbar1->pos.y = 140;
	cs->addUI(skillbar1);
	Sprite * tmp = new Sprite("image/Health/skill.png");
	tmp->pos = skillbar1->pos;
	tmp->scale = skillbar1->scale;
	cs->addUI(tmp);
	fillSkillbar.push_back(tmp);

	skillbar2 = new Sprite("image/skillicon/skillbar.png");
	skillbar2->scale.x = 0.5;
	skillbar2->scale.y = 0.5;
	skillbar2->pos.x = 212;
	skillbar2->pos.y = 140;
	cs->addUI(skillbar2);
	tmp = new Sprite("image/Health/skill.png");
	tmp->pos = skillbar2->pos;
	tmp->scale = skillbar2->scale;
	cs->addUI(tmp);
	fillSkillbar.push_back(tmp);

	skillbar3 = new Sprite("image/skillicon/skillbar.png");
	skillbar3->scale.x = 0.5;
	skillbar3->scale.y = 0.5;
	skillbar3->pos.x = 282;
	skillbar3->pos.y = 140;
	cs->addUI(skillbar3);
	tmp = new Sprite("image/Health/skill.png");
	tmp->pos = skillbar3->pos;
	tmp->scale = skillbar3->scale;
	cs->addUI(tmp);
	fillSkillbar.push_back(tmp);

	skillbar4 = new Sprite("image/skillicon/skillbar.png");
	skillbar4->scale.x = 0.5;
	skillbar4->scale.y = 0.5;
	skillbar4->pos.x = 962;
	skillbar4->pos.y = 140;
	cs->addUI(skillbar4);
	tmp = new Sprite("image/Health/skill.png");
	tmp->pos = skillbar4->pos;
	tmp->scale = skillbar4->scale;
	cs->addUI(tmp);
	fillSkillbar.push_back(tmp);

	skillbar5 = new Sprite("image/skillicon/skillbar.png");
	skillbar5->scale.x = 0.5;
	skillbar5->scale.y = 0.5;
	skillbar5->pos.x = 1040;
	skillbar5->pos.y = 140;
	cs->addUI(skillbar5);
	tmp = new Sprite("image/Health/skill.png");
	tmp->pos = skillbar5->pos;
	tmp->scale = skillbar5->scale;
	cs->addUI(tmp);
	fillSkillbar.push_back(tmp);

	skillbar6 = new Sprite("image/skillicon/skillbar.png");
	skillbar6->scale.x = 0.5;
	skillbar6->scale.y = 0.5;
	skillbar6->pos.x = 1107;
	skillbar6->pos.y = 140;
	cs->addUI(skillbar6);
	tmp = new Sprite("image/Health/skill.png");
	tmp->pos = skillbar6->pos;
	tmp->scale = skillbar6->scale;
	cs->addUI(tmp);
	fillSkillbar.push_back(tmp);


	Head1->pos.x = 10;
	Head1->pos.y = 11;
	Head1->scale.x = 2.0f;
	Head1->scale.y = 2.0f;
	cs->addUI(Head1);

	Head2->pos.x = 1265;
	Head2->pos.y = 11;
	Head2->scale.x = -2.0f;
	Head2->scale.y = 2.0f;
	cs->addUI(Head2);
}


HPController::~HPController()
{
}

void HPController::updateHPGUI(PlayerFrame * p1, PlayerFrame * p2)
{
	float p1CurrentHp = p1->current_Hp_Gauge / p1->max_Hp_Gauge;

	if (p1CurrentHp <= 0) {
		winner = p2;
		LOCAL_GM->isEnd = true;
		Player1HP5->visible = false;
	}
	else {
		Player1HP5->visible = true;
	}
	if (p1CurrentHp <= 0.2f)
		Player1HP4->visible = false;
	else
		Player2HP4->visible = true;
	if (p1CurrentHp <= 0.4f)
		Player1HP3->visible = false;
	else
		Player1HP3->visible = true;

	if (p1CurrentHp <= 0.6f)
		Player1HP2->visible = false;
	else
		Player1HP2->visible = true;

	if (p1CurrentHp <= 0.8f)
		Player1HP1->visible = false;
	else
		Player1HP1->visible = true;

	//Player02

	float p2CurrentHp = p2->current_Hp_Gauge / p2->max_Hp_Gauge;

	if (p2CurrentHp <= 0) {
		if (winner != nullptr) {
			duce = true;
		}
		else {
			winner = p1;
		}
		LOCAL_GM->isEnd = true;
		Player2HP5->visible = false;
	}
	else {
		Player2HP5->visible = true;
	}

	if (p2CurrentHp <= 0.2f)
		Player2HP4->visible = false;
	else
		Player2HP4->visible = true;

	if (p2CurrentHp <= 0.4f)
		Player2HP3->visible = false;
	else
		Player2HP3->visible = true;

	if (p2CurrentHp <= 0.6f)
		Player2HP2->visible = false;
	else
		Player2HP2->visible = true;

	if (p2CurrentHp <= 0.8f)
		Player2HP1->visible = false;
	else
		Player2HP1->visible = true;
}

void HPController::updateShieldGUI(PlayerFrame * p1, PlayerFrame * p2)
{
	float p1CurrentSi = p1->shield_Gauge / p1->max_Shield_Gauge;

	if (p1CurrentSi <= 0) {
		Player1si5->visible = false;
	}
	else {
		Player1si5->visible = true;
	}
	if (p1CurrentSi <= 0.2f)
		Player1si4->visible = false;
	else
		Player1si4->visible = true;

	if (p1CurrentSi <= 0.4f)
		Player1si3->visible = false;
	else
		Player1si3->visible = true;

	if (p1CurrentSi <= 0.6f)
		Player1si2->visible = false;
	else
		Player1si2->visible = true;

	if (p1CurrentSi <= 0.8f)
		Player1si1->visible = false;
	else
		Player1si1->visible = true;

	//Player02

	float p2CurrentSi = p2->shield_Gauge / p2->max_Shield_Gauge;

	if (p2CurrentSi <= 0) {
		Player2si5->visible = false;
	}
	else {
		Player2si5->visible = true;
	}

	if (p2CurrentSi <= 0.2f)
		Player2si4->visible = false;
	else
		Player2si4->visible = true;

	if (p2CurrentSi <= 0.4f)
		Player2si3->visible = false;
	else
		Player2si3->visible = true;

	if (p2CurrentSi <= 0.6f)
		Player2si2->visible = false;
	else
		Player2si2->visible = true;

	if (p2CurrentSi <= 0.8f)
		Player2si1->visible = false;
	else
		Player2si1->visible = true;
}

void HPController::updateSkillCoolFill(PlayerFrame * p1, PlayerFrame * p2)
{
	//set player 1
	fillSkillbar[0]->visibleRect = Rect(0, 0, (int)((p1->sk1_Timer->duration.first / p1->sk1_Timer->duration.second) * 103.0f), fillSkillbar[0]->visibleRect.bottom);
	if ((int)((p1->sk1_Timer->duration.first / p1->sk1_Timer->duration.second) * 103.0f) == 0)
		fillSkillbar[0]->visibleRect = Rect(0, 0, 103, fillSkillbar[0]->visibleRect.bottom);

	fillSkillbar[1]->visibleRect = Rect(0, 0, (int)((p1->sk2_Timer->duration.first / p1->sk2_Timer->duration.second) * 103.0f ), fillSkillbar[1]->visibleRect.bottom );
	if ((int)((p1->sk2_Timer->duration.first / p1->sk2_Timer->duration.second) * 103.0f) == 0)
		fillSkillbar[1]->visibleRect = Rect(0, 0, 103, fillSkillbar[1]->visibleRect.bottom);

	fillSkillbar[2]->visibleRect = Rect(0, 0, (int)((p1->current_suq_Gauge / p1->suq_Gauge_Max) * 103.0f), fillSkillbar[2]->visibleRect.bottom);
	if ((int)((p1->current_suq_Gauge / p1->suq_Gauge_Max) * 103.0f) == 0 || p1->current_suq_Gauge >= p1->suq_Gauge_Max)
		fillSkillbar[2]->visibleRect = Rect(0, 0, 103, fillSkillbar[2]->visibleRect.bottom);



	//set player2
	fillSkillbar[3]->visibleRect = Rect(0, 0, (int)((p2->sk1_Timer->duration.first / p2->sk1_Timer->duration.second) * 103.0f), fillSkillbar[3]->visibleRect.bottom);
	if ((int)((p2->sk1_Timer->duration.first / p2->sk1_Timer->duration.second) * 103.0f) == 0)
		fillSkillbar[3]->visibleRect = Rect(0, 0, 103, fillSkillbar[3]->visibleRect.bottom);

	fillSkillbar[4]->visibleRect = Rect(0, 0, (int)((p2->sk2_Timer->duration.first / p2->sk2_Timer->duration.second) * 103.0f), fillSkillbar[4]->visibleRect.bottom);
	if ((int)((p2->sk2_Timer->duration.first / p2->sk2_Timer->duration.second) * 103.0f) == 0)
		fillSkillbar[4]->visibleRect = Rect(0, 0, 103, fillSkillbar[4]->visibleRect.bottom);

	fillSkillbar[5]->visibleRect = Rect(0, 0, (int)((p2->current_suq_Gauge / p2->suq_Gauge_Max) * 103.0f), fillSkillbar[5]->visibleRect.bottom);
	if ((int)((p2->current_suq_Gauge / p2->suq_Gauge_Max) * 103.0f) == 0 || p2->current_suq_Gauge >= p2->suq_Gauge_Max)
		fillSkillbar[5]->visibleRect = Rect(0, 0, 103, fillSkillbar[5]->visibleRect.bottom);
}
