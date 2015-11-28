#pragma once

#include "../Include/IAIBehaviorFactory.h"
#include "Monster.h"

class CMyBehaviorFactory : public FKAISystem::IAIBehaviorFactory
{
public:
	CMyBehaviorFactory();
	~CMyBehaviorFactory();
public:
	bool Init();
	void DestoryBehavior();
private:
	bool _RegisterAllCreator();
	void _UnregisterAllCreator();
};