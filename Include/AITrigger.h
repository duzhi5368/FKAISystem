/********************************************************************
// FileName: d:\work\FKAISystem\Include\AITrigger.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  触发器基类
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

class CAIState;
class CAIStateMachine;
class IAIObject;
class CExpression;
class CAITriggerData;
class CAIBrain;



/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAITrigger
+   功能:	AI对象的触发器
+   描述:	提供基本的触发更新接口
-----------------------------------------------------------------
*****************************************************************/
class CAITrigger
{
	////////////////////////////////////////////
	//	数据成员
protected:
	CExpression		*m_pExpression;		// 条件表达式
	CAIState		*m_pParentState;	// 所属的状态
	CAIState		*m_pNextState;		// 条件满足时要切换到的下一个状态
	std::string		m_strNextStateName;	// 下一个状态的名字
	std::string		m_strExp;

	////////////////////////////////////////////
	//	构造/析构
public:
	CAITrigger( void );
	~CAITrigger( void );

	////////////////////////////////////////////
	//	公共接口
public:
	/*  
	@	功能：	构建触发器
	@	参数：	pTriggerData:	触发器数据
	@	返回值：是否成功
	@	注：	
	*/
	bool Build( CAITriggerData *pTriggerData, CAIBrain *pAIObject, CAIState *pParentState );

	/*  
	@	功能：	触发触发器
	@	参数：	
	@	返回值：如果触发器被触发，返回true，否则返回false
	@	注：	
	*/
	bool TouchOff( float fElapsedTimes );

	/*  
	@	功能：	设置触发器所属的状态
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void SetParentState( CAIState *pState )
	{
		m_pParentState = pState;
	}

	/*  
	@	功能：	设置触发器触发后要跳转到哪个状态
	@	参数：	pNextState:	下一个状态
	@	返回值：
	@	注：	
	*/
	void SetNextState( CAIState *pNextState )
	{
		m_pNextState = pNextState;
	}

	/*  
	@	功能：	
	@	参数：	
	@	返回值：
	@	注：	
	*/
	CAIState * GetNextState( void )	{ return m_pNextState; }

	/*  
	@	功能：	查询触发器的所有者
	@	参数：	
	@	返回值：
	@	注：	
	*/
	IAIObject * GetTriggerOwner( void );


	/*  
	@	功能：	链接下一个状态
	@	参数：	pMachine:	所属的状态机
	@	返回值：是否成功
	@	注：	
	*/
	bool LinkState( CAIStateMachine *pMachine );

};





AISYSTEM_SPACE_END

