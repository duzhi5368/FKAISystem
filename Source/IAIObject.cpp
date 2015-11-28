#include "../PreInclude.h"
#include "../Include/IAIObject.h"
#include "../Include/AIBrain.h"




AISYSTEM_SPACE_BEGIN



IAIObject::IAIObject()
{
	m_pAIBrain = NULL;
}


/*  
@	功能：	初始化AI系统，包括创建大脑，注册属性
@	参数：	strStateMachineName:	状态机的名字
@	返回值：操作成功的话返回去 true
@	注：	
*/
bool IAIObject::InitAISystem( const std::string & strStateMachineName )
{
	// 创建大脑并载入状态机
	m_pAIBrain = new CAIBrain( this );

	// 注册所有的属性
	_RegisterProperties();

	if( ! m_pAIBrain->LoadStateMachine( strStateMachineName ) )
	{
		delete m_pAIBrain;
		m_pAIBrain = NULL;
		return false;
	}



	return true;
}

/*  
@	功能：	更新AI
@	参数：	
@	返回值：
@	注：	
*/
void IAIObject::AIUpdate( float fElapsedTimes )
{
	if( m_pAIBrain )
		m_pAIBrain->Update( fElapsedTimes );
}

/*  
@	功能：	启动AI
@	参数：	
@	返回值：
@	注：	
*/
void IAIObject::AIStartUp( void )
{
	if( m_pAIBrain )
		m_pAIBrain->StartUp();
}

/*  
@	功能：	停止AI
@	参数：	
@	返回值：
@	注：	
*/
void IAIObject::AIShutDown( void )
{
	if( m_pAIBrain )
		m_pAIBrain->ShutDown();
}

/*  
@	功能：	暂停AI
@	参数：	
@	返回值：
@	注：	
*/
void IAIObject::AIPause( void )
{
	if( m_pAIBrain )
		m_pAIBrain->Pause();
}

/*  
@	功能：	恢复AI的运行
@	参数：	
@	返回值：
@	注：	
*/
void IAIObject::AIResume( void )
{
	if( m_pAIBrain )
		m_pAIBrain->Resume();
}


/*  
@	功能：	注册属性，返回一个ID
@	参数：	
@	返回值：属性ID，0表示注册失败
@	注：	
*/
unsigned long IAIObject::RegisterProperty( const std::string & strName, int *pValue )				
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}
unsigned long IAIObject::RegisterProperty( const std::string & strName, float *pValue )			
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}	
unsigned long IAIObject::RegisterProperty( const std::string & strName, bool *pValue )				
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}
unsigned long IAIObject::RegisterProperty( const std::string & strName, unsigned long *pValue )	
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}
unsigned long IAIObject::RegisterProperty( const std::string & strName, std::string *pValue )		
{ 
	if( m_pAIBrain )
		return m_pAIBrain->RegisterProperty( strName, pValue ); 
	return 0;
}

/*  
@	功能：	判断指定行为是否正在执行
@	参数：	strBehaviorName:	行为的名称
@	返回值：正在执行行为返回true；否则返回false
@	注：	
*/
bool IAIObject::IsBehaviorRunning( const std::string &strBehaviorName )
{
	return m_pAIBrain->IsBehaviorRunning( strBehaviorName );
}

/*  
@	功能：	强行中止一个行为
@	参数：	uiBehaviorTypeID:	要中止的行为的ID
@	返回值：如果当前状态正在执行行为，则中止并返回true，否则返回false
@	注：	
*/
bool IAIObject::StopBehavior( const std::string &strBehaviorName )
{
	return m_pAIBrain->StopBehavior( strBehaviorName );
}



AISYSTEM_SPACE_END