#include "../PreInclude.h"
#include "../Include/AIStateMachine.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/AIState.h"
#include "../Include/AIBrain.h"
#include "../Include/IAIGlobalFunc.h"



AISYSTEM_SPACE_BEGIN

using namespace std;


/*  
@	功能：	构造函数，初始化数据
@	参数：	
@	返回值：
@	注：	
*/
CAIStateMachine::CAIStateMachine( CAIBrain * pMaster )
: m_eMachineState( ESMachineState_End )
, m_pActiveState( NULL )
, m_pParentState( NULL )
, m_pMaster( pMaster )
{
}


/*  
@	功能：	析构函数，释放所有的状态
@	参数：	
@	返回值：
@	注：	
*/
CAIStateMachine::~CAIStateMachine(void)
{
	size_t size = m_pStates.size();
	CAIState *pState = NULL;

	map<string,CAIState*>::iterator iter = m_pStates.begin();
	while( iter != m_pStates.end() )
	{
		pState = iter->second;
		if( pState )
			delete pState;
		iter = m_pStates.erase( iter );
	}
	m_pStates.clear();
}


/*  
@	功能：	启动状态机
@	参数：	
@	返回值：
@	注：	
*/
bool CAIStateMachine::StartUp( void )
{
	if( ESMachineState_Running == m_eMachineState )
		return true;

	m_eMachineState = ESMachineState_Running;
	m_pActiveState = m_pDefaultState;
	m_pActiveState->Enter();
	return true;
}

/*  
@	功能：	停止状态机
@	参数：	
@	返回值：
@	注：	
*/
bool CAIStateMachine::ShutDown( void )
{
	if( ESMachineState_Stopped == m_eMachineState )
		return true;

	m_eMachineState = ESMachineState_Stopped;
	m_pActiveState->Leave();
	return true;
}

/*  
@	功能：	更新状态机
@	参数：	fElapsedTimes	:逝去的时间
@	返回值：
@	注：	
*/
void CAIStateMachine::Update( float fElapsedTimes )
{
	if( m_eMachineState != ESMachineState_Running )
		return;

	if( m_pActiveState )
	{
		CAIState *pNewState;
		pNewState = m_pActiveState->Update( fElapsedTimes );
		if( NULL != pNewState && pNewState != m_pActiveState )
		{
			m_pActiveState->Leave();
			m_pActiveState = pNewState;
			m_pActiveState->Enter();
		}
	}
}


/*  
@	功能：	查找一个状态
@	参数：	strStateName:	状态的名字
@	返回值：状态指针
@	注：	
*/
CAIState * CAIStateMachine::FindState( const std::string & strStateName )
{
	if( m_pStates.size() == 0 )
		return NULL;

	map<string,CAIState*>::iterator iter = m_pStates.find( strStateName );
	if( iter != m_pStates.end() )
		return iter->second;
	return NULL;
}


/*  
@	功能：	构造状态机
@	参数：	strMachineName:			状态机的名字
			strMachineTableName:	状态机表的名字
@	返回值：构建成功，返回true，否则返回false
@	注：	方法会从状态机的配置表中找到这个状态机，并构建它
*/
bool CAIStateMachine::Build( const std::string & strMachineTableName, const std::string & strMachineName )
{
	// 找到状态机表
	CAIMachineTable *pMachineTable = CAIStateInfoManager::Instance()->FindMachineTable( strMachineTableName );
	if( NULL == pMachineTable )
		return false;

	Build( pMachineTable, strMachineName );
	return true;
}

/*  
@	功能：	构造状态机
@	参数：	strMachineName:	状态机的名字
			pMachineTable:	状态机表的指针
@	返回值：构建成功，返回true，否则返回false
@	注：	方法会从状态机的配置表中找到这个状态机，并构建它
*/
bool CAIStateMachine::Build( CAIMachineTable *pMachineTable, const std::string & strMachineName )
{
	if( NULL == pMachineTable )
		return false;

	// 找到状态机
	CAIMachineData *pMachineData = pMachineTable->FindMachine( strMachineName );
	if( NULL == pMachineData || pMachineData->m_StateMap.size() == 0 )
		return false;

	// 构建所有的状态
	CAIState		*pState		= NULL;
	CAIStateData	*pStateData = NULL;
	map<string,CAIStateData> &StateMap = pMachineData->m_StateMap;
	map<string,CAIStateData>::iterator iter = StateMap.begin();
	for( ; iter != StateMap.end(); ++ iter )
	{
		pStateData = &iter->second;
		pState = new CAIState( this, m_pMaster );
		if( ! pState->Build( pStateData, pMachineTable ) )
		{
			if( pState )
				delete pState;
			return false;
		}
		else
		{
			m_pStates.insert( make_pair( pStateData->m_strName, pState ) );
		}
	}

	m_strName = pMachineData->m_strName;
	m_pDefaultState	= FindState( pMachineData->m_strDefaultState );
	if( NULL == m_pDefaultState )
		OutPutErrorMsg( "没有指定默认状态或默认状态查找失败！！ 状态机：%s", strMachineName.c_str() );

	return true;
}

/*  
@	功能：	链接所有的状态
@	参数：	
@	返回值：
@	注：	
*/
bool CAIStateMachine::LinkStates( void )
{
	if( m_pStates.size() == 0 )
		return true;

	map<string,CAIState*>::iterator iter = m_pStates.begin();
	bool bLinked = false;
	for( ; iter != m_pStates.end(); ++ iter )
	{
		bLinked = iter->second->LinkStates( this );
		if( false == bLinked )
			return false;
	}
	return true;
}


/*  
@	功能：	判断指定行为是否正在执行
@	参数：	uiBehaviorTypeID:	行为的类型ID
@	返回值：
@	注：	
*/
bool CAIStateMachine::IsBehaviorRunning( unsigned int uiBehaviorTypeID )
{
	if( m_pActiveState )
	{
		return m_pActiveState->IsBehaviorRunning( uiBehaviorTypeID );
	}
	return false;
}

/*  
@	功能：	强行中止一个行为
@	参数：	uiBehaviorTypeID:	要中止的行为的ID
@	返回值：如果当前状态正在执行行为，则中止并返回true，否则返回false
@	注：	
*/
bool CAIStateMachine::StopBehavior( unsigned int uiBehaviorTypeID )
{
	if( m_pActiveState )
	{
		return m_pActiveState->StopBehavior( uiBehaviorTypeID );
	}
	return false;
}



AISYSTEM_SPACE_END