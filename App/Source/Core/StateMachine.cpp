#include "pch.h"
#include "StateMachine.h"

IState* StateMachine::Current() const
{
	return m_current;
}

void StateMachine::Add(const std::string& id, IState* state)
{
	m_states.emplace(id, state);
	state->SetStateMachine(this);
}

void StateMachine::Change(const std::string& id)
{
	if (m_current) {
		m_current->OnExit();
	}
	IState* next = m_states[id];
	next->OnEnter();
	m_current = next;
}

StateMachine::~StateMachine()
{
	for (auto it = m_states.begin(); it != m_states.end(); it++) {
		SafeDelete(it->second);
	}
}