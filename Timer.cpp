#include "DXUT.h"
#include "Timer.h"
#include "World.h"

Timer::Timer()
	:active(false), removing(false)
{
	onTick = [](){};
	onFinish = [](){};

	world.timerList.push_back(this);
}


Timer::~Timer()
{
}

void Timer::reset(float duration, int count, bool autoStart)
{
	active = autoStart;
	this->duration.first = 0;
	this->duration.second = duration;
	this->count.first = 0;
	this->count.second = count;
}

void Timer::update(float dt)
{
	if(!active) return;

	duration.first += dt;
	if(duration.first > duration.second)
	{
		onTick();
		duration.first = 0;
		if(++count.first >= count.second)
		{
			active = false;
			onFinish();
			return;
		}
	}
}