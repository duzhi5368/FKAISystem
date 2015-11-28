/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIState.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  定义一个状态
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIStateDefine.h"


#pragma warning(disable:4251)


AISYSTEM_SPACE_BEGIN


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CState
+   功能：	表示状态机的一个状态
+   描述:	状态机的一个状态。
			一个状态有若干个触发器，当触发器条件满足触发时，激活一个
			行为，或者跳到下一个状态。
			一个状态可以有自己的状态机，当没有触发器能满足条件时，则
			执行自己的状态机。
-----------------------------------------------------------------
*****************************************************************/
class CAIStateMachine;
class CAITrigger;
class IAIBehavior;
class CAIBrain;
class CAIStateData;
class CAIMachineTable;
class CAIParams;
class CProperty;


class CAIState
{
	////////////////////////////////////////////
	//	友元类声明
public:
	friend class CAITrigger;

	////////////////////////////////////////////
	//	构造/析构函数
public:
	CAIState( CAIStateMachine *pParent, CAIBrain *pMaster );
	~CAIState( void );

	////////////////////////////////////////////
	//	外部接口
public:

	/*  
	@	功能：	构建一个状态
	@	参数：	pStateData:	状态的数据
	@	返回值：是否成功
	@	注：	
	*/
	bool Build( CAIStateData *pStateData, CAIMachineTable *pMachineTable );

	/*  
	@	功能：	进入状态
	@	参数：	
	@	返回值：
	@	注：	作一些初始化的工作，如果有AI，创建AI
	*/
	void Enter( void );

	/*  
	@	功能：	离开状态
	@	参数：	
	@	返回值：
	@	注：	如果有行为，删除AI
	*/
	void Leave( void );

	/*  
	@	功能：	状态执行
	@	参数：	fElapsedTimes	:逝去的时间
	@	返回值：如果发生了状态跳转，返回下一个状态
	@	注：	测试所有的状态转换器，更新行为的执行
	*/
	CAIState * Update( float fElapsedTimes );

	/*  
	@	功能：	查询状态的名字
	@	参数：	
	@	返回值：状态的名字
	@	注：	
	*/
	const std::string & GetStateName( void )
	{
		return m_strName;
	}

	/*  
	@	功能：	为所有的触发器链接下一个状态
	@	参数：	pStateMachine:	所属的状态机
	@	返回值：是否成功
	@	注：	
	*/
	bool LinkStates( CAIStateMachine *pMachine );

	/*  
	@	功能：	取得属于的那个大脑
	@	参数：	
	@	返回值：
	@	注：	
	*/
	CAIBrain *GetBrain( void )	{ return m_pMaster; }

	/*  
	@	功能：	判断指定行为是否正在执行
	@	参数：	uiBehaviorTypeID:	行为的类型ID
	@	返回值：
	@	注：	
	*/
	bool IsBehaviorRunning( unsigned int uiBehaviorTypeID );

	/*  
	@	功能：	强行中止一个行为
	@	参数：	uiBehaviorTypeID:	要中止的行为的ID
	@	返回值：如果当前状态正在执行行为，则中止并返回true，否则返回false
	@	注：	
	*/
	bool StopBehavior( unsigned int uiBehaviorTypeID );


	////////////////////////////////////////////
	//	数据成员
protected:
	CAIStateMachine				*m_pParentMachine;	// 状态所属的状态机的指针
	std::string					m_strName;			// 状态的名字
	CAIStateMachine				*m_pSubStateMachine;// 子状态机
	std::vector<CAITrigger*>	m_pStateTriggers;	// 状态的触发器
	CBehaviorParams				*m_pAIParams;		// 行为的参数
	IAIBehavior					*m_pBehavior;		// 当前正在执行的AI行为
	CAIBrain					*m_pMaster;			// AI对象
	std::vector<std::string>	m_strAIParams;
	std::vector<CProperty*>		m_ParamProp;
};



AISYSTEM_SPACE_END

#pragma warning(default:4251)