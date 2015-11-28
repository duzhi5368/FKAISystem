#include "../PreInclude.h"
#include "../Include/AIBrain.h"
#include "../Include/AIStateMachine.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/AIPropertySet.h"
#include "../Include/IAIBehaviorFactory.h"


AISYSTEM_SPACE_BEGIN


int CAIBrain::s_eExecuting = EAIBS_Executing;
int CAIBrain::s_eInterrupt = EAIBS_Interrupt;
int CAIBrain::s_eFailed	= EAIBS_Failed;
int CAIBrain::s_eSucced	= EAIBS_Succeed;

/*  
@	功能：	构造函数，初始化成员数据
@	参数：	
@	返回值：
@	注：	
*/
CAIBrain::CAIBrain( IAIObject *pAIObject )
{
	m_pStateMachine = NULL;
	m_pAIObject = pAIObject;
	m_pPropertySet = new CPropertySet;

	RegisterProperty( "BehaviorState", &m_eBehaviorState );
	RegisterProperty( "Succeed", &CAIBrain::s_eSucced );
	RegisterProperty( "Failed", &CAIBrain::s_eFailed );
	RegisterProperty( "Interrupt", &CAIBrain::s_eInterrupt );
	RegisterProperty( "Executing", &CAIBrain::s_eExecuting );
}

/*  
@	功能：	析构函数，做一些清理工作
@	参数：	
@	返回值：
@	注：	删除状态机
*/
CAIBrain::~CAIBrain( void )
{
	if( m_pStateMachine )
		delete m_pStateMachine;
}

/*  
@	功能：	更新接口
@	参数：	fElapsedTimes:	逝去的时间
@	返回值：
@	注：	基类的实现只更新了状态机
*/
void CAIBrain::Update( float fElapsedTimes )
{
	if( m_pStateMachine )
		m_pStateMachine->Update( fElapsedTimes );
}

/*  
@	功能：	启动大脑
@	参数：	
@	返回值：
@	注：	
*/
void CAIBrain::StartUp( void )
{
	m_pStateMachine->StartUp();
}

/*  
@	功能：	停止大脑的工作
@	参数：	
@	返回值：
@	注：	
*/
void CAIBrain::ShutDown( void )
{
	m_pStateMachine->ShutDown();
}

/*  
@	功能：	让大脑暂停
@	参数：	
@	返回值：
@	注：	
*/
void CAIBrain::Pause( void )
{
	m_pStateMachine->Pause();
}

/*  
@	功能：	恢复大脑的动作
@	参数：	
@	返回值：
@	注：	
*/
void CAIBrain::Resume( void )
{
	m_pStateMachine->Resume();
}

/*  
@	功能：	载入状态机
@	参数：	strStateMachineName:	状态机的名字
@	返回值：是否成功
@	注：	
*/
bool CAIBrain::LoadStateMachine( const std::string strStateMachineName )
{
	if( m_pStateMachine != NULL )
	{
		delete m_pStateMachine;
		m_pStateMachine = NULL;
	}
	m_pStateMachine = new CAIStateMachine( this );
	CAIMachineTable *pMachineTable = CAIStateInfoManager::Instance()->FindMachineTable( strStateMachineName );
	if( NULL == pMachineTable )
		return false;

	bool res = m_pStateMachine->Build( pMachineTable, pMachineTable->m_strMainMachine );
	if( res )
	{
		res = m_pStateMachine->LinkStates( );
		return res;
	}
	return res;
}

/*  
@	功能：	查找一个属性
@	参数：	strName:	属性的名字
@	返回值：属性指针
@	注：	
*/
CProperty *CAIBrain::FindProperty( const std::string & strName )							
{ 
	return m_pPropertySet->FindProperty( strName ); 
}

/*  
@	功能：	注册属性，返回一个ID
@	参数：	
@	返回值：属性ID，0表示注册失败
@	注：	
*/
unsigned long CAIBrain::RegisterProperty( const std::string & strName, int *pValue )				
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}
unsigned long CAIBrain::RegisterProperty( const std::string & strName, float *pValue )			
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}	
unsigned long CAIBrain::RegisterProperty( const std::string & strName, bool *pValue )				
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}
unsigned long CAIBrain::RegisterProperty( const std::string & strName, unsigned long *pValue )	
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}
unsigned long CAIBrain::RegisterProperty( const std::string & strName, std::string *pValue )		
{ 
	return m_pPropertySet->Register( strName, pValue ); 
}

/*  
@	功能：	判断指定行为是否正在执行
@	参数：	strBehaviorName:	行为的名称
@	返回值：正在执行行为返回true；否则返回false
@	注：	
*/
bool CAIBrain::IsBehaviorRunning( const std::string &strBehaviorName )
{
	unsigned int uiTypeID = IAIBehaviorFactory::Instance()->GenerateID( strBehaviorName );
	return m_pStateMachine->IsBehaviorRunning( uiTypeID );
}

/*  
@	功能：	强行中止一个行为
@	参数：	uiBehaviorTypeID:	要中止的行为的ID
@	返回值：如果当前状态正在执行行为，则中止并返回true，否则返回false
@	注：	
*/
bool CAIBrain::StopBehavior( const std::string &strBehaviorName )
{
	unsigned int uiTypeID = IAIBehaviorFactory::Instance()->GenerateID( strBehaviorName );
	return m_pStateMachine->StopBehavior( uiTypeID );
}




AISYSTEM_SPACE_END