#pragma once

#include "States/IState.h"

/**
* Todo: add security and error management.
*/
class StateMachine
{
public:
	StateMachine() = default;
	virtual ~StateMachine();

	IState* Current() const;
	void Add(const std::string& id, IState* state);
	void Change(const std::string& id);
	
private:
	std::unordered_map<std::string, IState*> m_states;
	IState* m_current;
};
