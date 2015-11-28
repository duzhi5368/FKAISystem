#include "../PreInclude.h"
#include "../Include/AITrigger.h"
#include "../Include/AIStateMachine.h"
#include "../Include/AIState.h"
#include "../Include/AIBrain.h"
#include "../Include/AIExpressionAnalyzer.h"
#include "../Include/AIStateInfoManager.h"

#include "../Include/IAIGlobalFunc.h"



AISYSTEM_SPACE_BEGIN

/*  
@	功能：	构造函数，初始化数据
@	参数：	
@	返回值：
@	注：	
*/
CAITrigger::CAITrigger( void )
: m_pExpression( NULL )
, m_pParentState( NULL )
, m_pNextState( NULL )
{
}


/*  
@	功能：	析构函数，释放所有的条件
@	参数：	
@	返回值：
@	注：	
*/
CAITrigger::~CAITrigger(void)
{
	if( m_pExpression )
	{
		delete m_pExpression;
		m_pExpression = NULL;
	}
}

/*  
@	功能：	构建触发器
@	参数：	pTriggerData:	触发器数据
@	返回值：是否成功
@	注：	
*/
bool CAITrigger::Build( CAITriggerData *pTriggerData, CAIBrain *pAIObject, CAIState *pParentState )
{
	// 创建所有的条件
	static CExpressionAnalyzer expAnaylyzer;
	static bool bExpAnalyzeInited = false;
	if( ! bExpAnalyzeInited )
	{
		expAnaylyzer.Init();
		bExpAnalyzeInited = true;
	}

	static CLexicalAnalyzer lexAnaylyzer;
	static bool bLexAnaylzerInited = false;
	if( ! bLexAnaylzerInited )
	{
		lexAnaylyzer.Init();
		bLexAnaylzerInited = true;
	}

	m_pParentState = pParentState;

	static TLexTokens tokens;
	if( ! lexAnaylyzer.Analyse( pTriggerData->m_strExpression.c_str(), tokens ) )
	{
		// 条件词法分析失败
		OutPutErrorMsg( "词法分析失败，表达式：%s", pTriggerData->m_strExpression.c_str() );
		return false;
	}
	m_pExpression = expAnaylyzer.Analyse( tokens, m_pParentState->GetBrain(), pTriggerData->m_strExpression.c_str() );
	if( NULL == m_pExpression )
	{
		// 解析条件失败
		OutPutErrorMsg( "解析条件失败，表达式：%s", pTriggerData->m_strExpression.c_str() );
		return false;
	}

	m_strNextStateName = pTriggerData->m_strNextStateName;

	m_strExp = pTriggerData->m_strExpression;

	return true;
}

/*  
@	功能：	触发触发器
@	参数：	
@	返回值：如果触发器被触发，返回true，否则返回false
@	注：	
*/
bool CAITrigger::TouchOff(float fElapsedTimes)
{
	double res = (*m_pExpression)();
	if( res <= 0.000001 )
		return false;
	return true;
}

/*  
@	功能：	查询触发器的所有者
@	参数：	
@	返回值：
@	注：	
*/
IAIObject * CAITrigger::GetTriggerOwner( void )
{
	return m_pParentState->GetBrain()->GetAIObject();
}


/*  
@	功能：	链接下一个状态
@	参数：	pStateMachine:	所属的状态机
@	返回值：是否成功
@	注：	
*/
bool CAITrigger::LinkState(CAIStateMachine *pMachine)
{	
	if( m_strNextStateName == "" )
		return true;

	if( NULL == pMachine )
		return false;

	m_pNextState = pMachine->FindState( m_strNextStateName );
	if( NULL == m_pNextState )
		return false;
	else
		return true;
}


AISYSTEM_SPACE_END