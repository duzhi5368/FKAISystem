#include "TestFKAISystem/stdafx.h"
#include "Monster.h"

//--------------------------------------------------------------------
CMonster::CMonster()
	 : m_unHP			( 0 )
	 , m_unID			( 0 )
{
	m_szName.empty();
}
//--------------------------------------------------------------------
CMonster::~CMonster()
{
	m_szName.empty();
	m_unHP = 0;
	m_unID = 0;
}
//--------------------------------------------------------------------
void CMonster::Init( const std::string p_szStateMachineName )
{
	if ( ! this->InitAISystem(p_szStateMachineName) )
	{
		std::cout << "初始化AI系统，读表失败!" << std::endl;
	}
	this->AIStartUp();
}
//--------------------------------------------------------------------
void CMonster::Update( float fElapsedTimes )
{
	this->AIUpdate( fElapsedTimes );
}
//--------------------------------------------------------------------
void CMonster::Destory()
{
	this->AIShutDown();
}
//--------------------------------------------------------------------
void CMonster::_RegisterProperties()
{
	RegisterProperty( "生命值", &(m_unHP));
	RegisterProperty( "唯一ID", &(m_unID));
	RegisterProperty( "名称", &(m_szName)); 
}
//--------------------------------------------------------------------
CAttackBehavior* CMonster::CreateBehavior( FKAISystem::CBehaviorParams *pBehaviorParams )
{
	m_pAttack = new CAttackBehavior();
	m_pAttack->SetMaster( this );
	return m_pAttack;
}
//--------------------------------------------------------------------