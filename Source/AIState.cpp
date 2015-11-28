#include "../PreInclude.h"
#include "../Include/AIState.h"
#include "../Include/AIProperty.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/AIStateMachine.h"
#include "../Include/AIBrain.h"
#include "../Include/AITrigger.h"
#include "../Include/IAIBehavior.h"
#include "../Include/IAIBehaviorFactory.h"

#include "../Include/IAIGlobalFunc.h"




AISYSTEM_SPACE_BEGIN


/*  
@	功能：	构造函数，初始化数据
@	参数：	
@	返回值：
@	注：	
*/
CAIState::CAIState( CAIStateMachine *pParent, CAIBrain *pMaster )
: m_pParentMachine( pParent )
, m_pSubStateMachine( NULL )
, m_pAIParams( NULL )
, m_pBehavior( NULL )
, m_pMaster( pMaster )
{
}


/*  
@	功能：	析构函数，释放所有的触发器
@	参数：	
@	返回值：
@	注：	
*/
CAIState::~CAIState(void)
{
	// 释放AI
	if( m_pBehavior )
		delete m_pBehavior;

	// 释放触发器
	size_t size = m_pStateTriggers.size();
	CAITrigger *pTrigger = NULL;
	for( size_t i = 0; i < size; ++ i )
	{
		pTrigger = m_pStateTriggers[i];
		if( pTrigger )
			delete pTrigger;
	}
	m_pStateTriggers.clear();
}

/*  
@	功能：	进入状态
@	参数：	
@	返回值：
@	注：	作一些初始化的工作，如果有AI，创建AI
*/
void CAIState::Enter( void )
{
	// 创建AI，填充参数
	if( m_pAIParams )
	{
		int n = (int)m_ParamProp.size();
		for( int i = 0; i < n; ++ i )
		{
			if( m_ParamProp[i] )
			{
				CProperty *pProp = m_ParamProp[i];
				switch( pProp->GetType() )
				{
				case CProperty::EDT_Int:
					{
						int data;
						pProp->GetValue( data );
						m_pAIParams->m_Params[i].SetData( data );
					}
					break;
				case CProperty::EDT_Float:
					{
						float data;
						pProp->GetValue( data );
						m_pAIParams->m_Params[i].SetData( data );
					}
					break;
				case CProperty::EDT_UnsignedLong:
					{
						unsigned long data;
						pProp->GetValue( data );
						m_pAIParams->m_Params[i].SetData( data );
					}
					break;
				case CProperty::EDT_Bool:
					{
						bool data;
						pProp->GetValue( data );
						int i = (int)data;
						m_pAIParams->m_Params[i].SetData( i );
					}
					break;
				case CProperty::EDT_String:
					{
						std::string data;
						pProp->GetValue( data );
						m_pAIParams->m_Params[i].SetData( data );
					}
					break;
				}
			}
		}
		// 根据参数创建AI行为
		m_pBehavior = IAIBehaviorFactory::Instance()->CreateBehavior( m_pMaster->GetAIObject(), m_pAIParams );
		if( m_pBehavior && ! m_pBehavior->OnStartUp() )
		{
			IAIBehaviorFactory::Instance()->DestoryBehavior( m_pBehavior );
			m_pBehavior = NULL;
		}
	}

	if( m_pSubStateMachine )
		m_pSubStateMachine->StartUp();
}

/*  
@	功能：	离开状态
@	参数：	
@	返回值：
@	注：	如果有行为，删除AI
*/
void CAIState::Leave( void )
{
	if( m_pBehavior )
	{
		m_pBehavior->OnShutDown();
		IAIBehaviorFactory::Instance()->DestoryBehavior( m_pBehavior );
		m_pBehavior = NULL;
	}
	if( m_pSubStateMachine )
		m_pSubStateMachine->ShutDown();
}

/*  
@	功能：	状态执行
@	参数：	fElapsedTimes	:逝去的时间
@	返回值：如果发生了状态跳转，返回下一个状态
@	注：	测试所有的触发器，如果发生状态跳转，则返回新的状态
			否则如果有子状态机则执行子状态机，没有状态机则更新AI的执行，
*/
CAIState * CAIState::Update( float fElapsedTimes )
{
	// 有子状态机，更新子状态机
	if( m_pSubStateMachine )
		m_pSubStateMachine->Update( fElapsedTimes );

	// 有AI更新AI
	if( m_pBehavior )
	{
		EAIBehaviorState state = m_pBehavior->RealUpdate( fElapsedTimes );
		m_pMaster->SetCurBehaviorState( state );
	}

	// 执行触发器
	size_t size = m_pStateTriggers.size();
	CAITrigger *pTrigger	= NULL;
	CAIState *pNextState	= NULL;
	for( size_t i = 0; i < size; ++ i )
	{
		pTrigger = m_pStateTriggers[i];
		if( pTrigger )
		{
			if( pTrigger->TouchOff( fElapsedTimes ) )
				pNextState = pTrigger->GetNextState();
			if( pNextState )
				return pNextState;
		}
	}

	return NULL;
}

/*  
@	功能：	构建一个状态
@	参数：	pStateData:	状态的数据
@	返回值：是否成功
@	注：	
*/
bool CAIState::Build( CAIStateData *pStateData, CAIMachineTable *pMachineTable )
{
	// 如果有子状态机，创建子状态机
	if( pStateData->m_strSubStateMachineName != "" )
	{
		if( NULL == pMachineTable )
			return false;
		m_pSubStateMachine = new CAIStateMachine( m_pMaster );
		bool res = m_pSubStateMachine->Build( pMachineTable, pStateData->m_strSubStateMachineName );
		if( false == res )
			return false;
		m_pSubStateMachine->SetParentState( this );
	}
	// 有AI，保存AI参数
	if( pStateData->m_uiAIID != 0 )
	{
		m_pAIParams = new CBehaviorParams;
		m_pAIParams->m_uiAIID	= pStateData->m_uiAIID;
		int n = Parse2Strings( m_strAIParams, pStateData->m_AIParams );
		for( int i = 0; i < n; ++ i )
		{
			if( ! IsNumeric( m_strAIParams[i] ) )
			{
				CProperty *pProp = m_pMaster->FindProperty( m_strAIParams[i] );
				if( NULL == pProp )
				{
					// 没有找到属性
					OutPutErrorMsg( "没有找到属性: %s", m_strAIParams[i].c_str() );
					return false;
				}
				m_ParamProp.push_back( pProp );
			}
			else
				m_ParamProp.push_back( NULL );
			CAIAny any( m_strAIParams[i] );
			m_pAIParams->m_Params.push_back( any );
		}
	}

	// 创建所有的触发器
	std::vector<CAITriggerData> &TriggerDatas = pStateData->m_Triggers;
	size_t size = TriggerDatas.size();
	CAITrigger *pTrigger = NULL;
	for( size_t i = 0; i < size; ++ i )
	{
		CAITriggerData &TriggerData = TriggerDatas[i];
		pTrigger = new CAITrigger;
		if( ! pTrigger->Build( &TriggerData, m_pMaster, this ) )
		{
			// AI LOG
			OutPutErrorMsg( "创建触发器失败 状态：%s", pStateData->m_strName.c_str() );
			delete pTrigger;
			pTrigger = NULL;
			continue;
		}
		m_pStateTriggers.push_back( pTrigger );
	}

	m_strName = pStateData->m_strName;
	return true;
}

/*  
@	功能：	为所有的触发器链接下一个状态
@	参数：	pStateMachine:	所属的状态机
@	返回值：是否成功
@	注：	
*/
bool CAIState::LinkStates( CAIStateMachine *pMachine )
{
	size_t size = m_pStateTriggers.size();
	if( 0 == size )
		return true;

	if( NULL == pMachine )
		return false;

	CAITrigger *pTrigger = NULL;
	bool bLinked = false;
	for( size_t i = 0; i < size; ++ i )
	{
		pTrigger = m_pStateTriggers[i];
		if( pTrigger )
		{
			bLinked = pTrigger->LinkState( pMachine );
			if( false == bLinked )
				return false;
		}
	}

	if( m_pSubStateMachine )
	{
		return m_pSubStateMachine->LinkStates();
	}
	return true;
}

/*  
@	功能：	判断指定行为是否正在执行
@	参数：	uiBehaviorTypeID:	行为的类型ID
@	返回值：
@	注：	
*/
bool CAIState::IsBehaviorRunning( unsigned int uiBehaviorTypeID )
{
	bool running = false;
	if( m_pSubStateMachine )
		running |= m_pSubStateMachine->IsBehaviorRunning( uiBehaviorTypeID );
	if( m_pBehavior )
		running |= ( m_pBehavior->GetAIType() == uiBehaviorTypeID );
	return running;
}

/*  
@	功能：	强行中止一个行为
@	参数：	uiBehaviorTypeID:	要中止的行为的ID
@	返回值：如果当前状态正在执行行为，则中止并返回true，否则返回false
@	注：	
*/
bool CAIState::StopBehavior( unsigned int uiBehaviorTypeID )
{
	bool ok = false;
	if( m_pSubStateMachine )
		ok |= m_pSubStateMachine->StopBehavior( uiBehaviorTypeID );
	// 有AI更新AI
	if( m_pBehavior && m_pBehavior->GetAIType() == uiBehaviorTypeID )
	{
		m_pBehavior->Stop();
		ok |= true;
	}
	return ok;
}



AISYSTEM_SPACE_END