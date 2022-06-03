#pragma once

#include "Core/StateMachine.h"

class Highscore : public IState
{
public:
	Highscore() = default;
	virtual ~Highscore() = default;

	void OnEnter() override
	{

	}

	void OnInput() override
	{

	}

	bool OnUpdate(float frameDelta) override
	{
		return true;
	}

	void OnRender() override
	{

	}

	void OnExit() override
	{

	}

private:

};