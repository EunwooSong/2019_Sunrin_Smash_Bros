#pragma once
#include "Define.h"

class Timer
{
public:
	Timer();
	~Timer();

	void update(float dt);

	void reset(float duration = 0, int count = 0, bool autoStart = true);

	function<void()> onTick;
	function<void()> onFinish;

	pair<float, float> duration;
	pair<int, int> count;

	bool active;
	bool removing;
};

