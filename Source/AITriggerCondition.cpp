#include "../PreInclude.h"
//
//#include "AITriggerCondition.h"
//#include "AIStateInfoManager.h"
//#include "AIStateMachine.h"
//#include "AIBrain.h"
//#include "AIExpressionAnalyzer.h"
//
//AISYSTEM_SPACE_BEGIN
//
///*  
//@	功能：	构造函数，初始化数据
//@	参数：	
//@	返回值：
//@	注：	
//*/
//CAITriggerCondition::CAITriggerCondition( void )
//{
//}
//
//
///*  
//@	功能：	析构函数，释放所有的条件
//@	参数：	
//@	返回值：
//@	注：	
//*/
//CAITriggerCondition::~CAITriggerCondition(void)
//{
//	if( m_pExpression )
//	{
//		delete m_pExpression;
//		m_pExpression = NULL;
//	}
//}
//
//
///*  
//@	功能：	触发触发器
//@	参数：	
//@	返回值：如果触发器被触发，返回true，否则返回false
//@	注：	
//*/
//bool CAITriggerCondition::TouchOff(float fElapsedTimes)
//{
//	double res = (*m_pExpression)();
//	if( res <= 0.000001 )
//		return false;
//	return true;
//}
//
///*  
//@	功能：	构建触发器
//@	参数：	pTriggerData:	触发器数据
//@	返回值：是否成功
//@	注：	
//*/
//bool CAITriggerCondition::Build( CAITriggerData *pTriggerData, CAIBrain *pAIObject )
//{
//	// 创建所有的条件
//	static CExpressionAnalyzer expAnaylyze;
//	static bool bExpAnalyzeInited = false;
//	if( ! bExpAnalyzeInited )
//	{
//		expAnaylyze.Init();
//		bExpAnalyzeInited = true;
//	}
//
//	m_pExpression = expAnaylyze.Analyse( pTriggerData->m_strExpression.c_str() );
//	if( NULL == m_pExpression )
//	{
//		// AI LOG 解析条件失败
//		return false;
//	}
//
//	m_strNextStateName = pTriggerData->m_strNextStateName;
//
//	return true;
//}
//
///*  
//@	功能：	链接下一个状态
//@	参数：	pStateMachine:	所属的状态机
//@	返回值：是否成功
//@	注：	
//*/
//bool CAITriggerCondition::LinkState(CAIStateMachine *pMachine)
//{	
//	if( m_strNextStateName == "" )
//		return true;
//
//	if( NULL == pMachine )
//		return false;
//
//	m_pNextState = pMachine->FindState( m_strNextStateName );
//	if( NULL == m_pNextState )
//		return false;
//	else
//		return true;
//}
//
//
//AISYSTEM_SPACE_END