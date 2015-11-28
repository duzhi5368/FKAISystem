#include "TestFKAISystem/stdafx.h"
#include "MyBehaviorFactory.h"
#include "Monster.h"


//--------------------------------------------------------------------
CMyBehaviorFactory::CMyBehaviorFactory()
{

}
//--------------------------------------------------------------------
CMyBehaviorFactory::~CMyBehaviorFactory()
{

}
//--------------------------------------------------------------------
bool CMyBehaviorFactory::Init()
{
	return _RegisterAllCreator();
}
//--------------------------------------------------------------------
void CMyBehaviorFactory::DestoryBehavior()
{
	_UnregisterAllCreator();
}
//--------------------------------------------------------------------
bool CMyBehaviorFactory::_RegisterAllCreator()
{
	_RegisterCreator( "¹¥»÷", &CMonster::CreateBehavior  );
}
//--------------------------------------------------------------------
void CMyBehaviorFactory::_UnregisterAllCreator()
{
	_UnregisterCreator( "¹¥»÷" );
}
//--------------------------------------------------------------------