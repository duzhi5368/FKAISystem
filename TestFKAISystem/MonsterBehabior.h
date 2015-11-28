#pragma once

#include "../Include/IAIBehavior.h"

class CAttackBehavior : public FKAISystem::IAIBehavior
{
public:
	CAttackBehavior();
	~CAttackBehavior();
public:
	FKAISystem::EAIBehaviorState Update( float fElpasedTimes );
	bool OnStartUp();
	void OnShutDown();
};