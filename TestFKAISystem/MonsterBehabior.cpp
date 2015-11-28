#include "TestFKAISystem/stdafx.h"
#include "MonsterBehabior.h"

//--------------------------------------------------------------------
CAttackBehavior::CAttackBehavior()
{

}
//--------------------------------------------------------------------
CAttackBehavior::~CAttackBehavior()
{

}
//--------------------------------------------------------------------
FKAISystem::EAIBehaviorState CAttackBehavior::Update( float fElpasedTimes )
{
	return FKAISystem::EAIBS_Executing;
}
//--------------------------------------------------------------------
bool CAttackBehavior::OnStartUp()
{
	return true;
}
//--------------------------------------------------------------------
void CAttackBehavior::OnShutDown()
{

}
//--------------------------------------------------------------------