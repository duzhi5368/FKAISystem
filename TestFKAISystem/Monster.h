#pragma once

#include "../Include/IAIObject.h"
#include "MonsterBehabior.h"

class CMonster : public FKAISystem::IAIObject
{
public:
	CMonster();
	~CMonster();
public:
	static CAttackBehavior* CreateBehavior( FKAISystem::CBehaviorParams *pBehaviorParams );
public:
	void Init( const std::string p_szStateMachineName );
	void Update( float fElapsedTimes );
	void Destory();
protected:
	void _RegisterProperties();
public:
	unsigned long		m_unHP;
	unsigned long		m_unID;
	std::string			m_szName;

	CAttackBehavior*	m_pAttack;
};