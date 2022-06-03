#pragma once

class StateMachine;

class IState
{
public:
	virtual ~IState() = default;
	virtual void OnEnter() = 0;
	virtual void OnInput() = 0;
	virtual bool OnUpdate(float frameDelta) = 0;
	virtual void OnRender() = 0;
	virtual void OnExit() = 0;

	void SetStateMachine(StateMachine* sm) { if (!m_stateMachine) { m_stateMachine = sm; } }

protected:
	StateMachine* GetStateMachine() { return m_stateMachine; }

private:
	StateMachine* m_stateMachine = nullptr;
};