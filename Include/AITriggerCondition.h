/********************************************************************
// FileName: d:\work\FKAISystem\Include\AITriggerCondition.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  条件触发器
*********************************************************************/

//#pragma once

//--------------------------------------------------------------------
//
//#include "CAITrigger.h"
//
//#pragma warning(disable:4251)
//
//AISYSTEM_SPACE_BEGIN
//
//
//class CAITriggerData;
//class CExpression;
//class CAIBrain;
//
//
///****************************************************************
//+	CLASS
//-----------------------------------------------------------------
//+   类名:	CAITrigger
//+   功能:	AI对象的触发器
//+   描述:	触发器维护一系列条件，当条件满足时返回下一个状态
//-----------------------------------------------------------------
//*****************************************************************/
//class CAITriggerCondition : public CAITrigger
//{
//	////////////////////////////////////////////
//	//	数据成员
//protected:
//	CExpression		*m_pExpression;		// 条件表达式
//
//	////////////////////////////////////////////
//	//	构造/析构
//public:
//	CAITriggerCondition( void );
//	~CAITriggerCondition( void );
//
//	////////////////////////////////////////////
//	//	公共接口
//public:
//	/*  
//	@	功能：	构建触发器
//	@	参数：	pTriggerData:	触发器数据
//	@	返回值：是否成功
//	@	注：	
//	*/
//	bool Build( CAITriggerData *pTriggerData, CAIBrain *pAIObject );
//
//	/*  
//	@	功能：	触发触发器
//	@	参数：	
//	@	返回值：如果触发器被触发，返回true，否则返回false
//	@	注：	
//	*/
//	virtual bool TouchOff( float fElapsedTimes );
//
//	/*  
//	@	功能：	设置触发器所属的状态
//	@	参数：	
//	@	返回值：
//	@	注：	
//	*/
//	void SetParentState( CAIState *pState )
//	{
//		m_pParentState = pState;
//	}
//
//	/*  
//	@	功能：	链接下一个状态
//	@	参数：	pMachine:	所属的状态机
//	@	返回值：是否成功
//	@	注：	
//	*/
//	bool LinkState( CAIStateMachine *pMachine );
//
//};
//
//
//
//
//AISYSTEM_SPACE_END
//
//#pragma warning(default:4251)