/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIStateMachine.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIStateDefine.h"


AISYSTEM_SPACE_BEGIN

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAIStateMachine
+   功能：	状态机
+   描述:	每个AI对象都会有一个状态机来控制它的行为。
这是一个状态机的基类，每种类型的对象应该派生自己的状态
机类型，这样状态机才有自己的AI类型
-----------------------------------------------------------------
*****************************************************************/
class CAIBrain;
class CAIMachineTable;

class CAIStateMachine
{
	////////////////////////////////////////////
	//	友元类声明
public:
	friend class CAIState;

	////////////////////////////////////////////
	//	构造/析构
public:
	CAIStateMachine( CAIBrain * pMaster );
	~CAIStateMachine(void);

	////////////////////////////////////////////
	//	外部接口
public:

	/*  
	@	功能：	构造状态机
	@	参数：	strMachineName:			状态机的名字
				strMachineTableName:	状态机表的名字
	@	返回值：构建成功，返回true，否则返回false
	@	注：	方法会从状态机的配置表中找到这个状态机，并构建它
	*/
	bool Build( const std::string & strMachineTableName, const std::string & strMachineName );

	/*  
	@	功能：	构造状态机
	@	参数：	strMachineName:	状态机的名字
				pMachineTable:	状态机表的指针
	@	返回值：构建成功，返回true，否则返回false
	@	注：	方法会从状态机的配置表中找到这个状态机，并构建它
	*/
	bool Build( CAIMachineTable *pMachineTable, const std::string & strMachineName );

	/*  
	@	功能：	链接所有的状态
	@	参数：	
	@	返回值：
	@	注：	
	*/
	bool LinkStates( void );

	/*  
	@	功能：	启动状态机
	@	参数：	
	@	返回值：
	@	注：	
	*/
	bool StartUp( void );

	/*  
	@	功能：	停止状态机
	@	参数：	
	@	返回值：
	@	注：	
	*/
	bool ShutDown( void );

	/*  
	@	功能：	更新状态机
	@	参数：	fElapsedTimes	:逝去的时间
	@	返回值：
	@	注：	
	*/
	void Update( float fElapsedTimes );

	/*  
	@	功能：	暂停
	@	参数：	
	@	返回值：
	@	注：	当不需要更新AI对象时，暂停它。比如当没有玩家能看到时，可以暂停。
	*/
	void Pause( void )
	{
		m_eMachineState = ESMachineState_Sleeping;
	}

	/*  
	@	功能：	恢复AI的执行
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void Resume( void )
	{
		m_eMachineState = ESMachineState_Running;
	}

	/*  
	@	功能：	查找一个状态
	@	参数：	strStateName:	状态的名字
	@	返回值：状态指针
	@	注：	
	*/
	CAIState * FindState( const std::string & strStateName );

	/*  
	@	功能：	如果这是个子状态机，设置状态机的父状态
	@	参数：	pState:	父状态指针
	@	返回值：
	@	注：	
	*/
	void SetParentState( CAIState *pState )
	{
		m_pParentState = pState;
	}

	/*  
	@	功能：	查询状态机的宿主
	@	参数：	
	@	返回值：状态机宿主对象指针
	@	注：	
	*/
	CAIBrain * GetMaster( void )
	{
		return m_pMaster;
	}

	/*  
	@	功能：	设置状态机的宿主
	@	参数：	
	@	返回值：状态机宿主对象指针
	@	注：	
	*/
	void GetMaster( CAIBrain * pMaster )
	{
		m_pMaster = pMaster;
	}

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
	EStateMachineState		m_eMachineState;	// 状态机的运行状态
	CAIState				*m_pActiveState;	// 当前正在执行的状态
	CAIState				*m_pParentState;	// 如果这个状态机是一个子状态机的话，这是他的父状态
	CAIBrain				*m_pMaster;			// 状态机的宿主
	std::string				m_strName;			// 状态机的名字
	CAIState				*m_pDefaultState;	// 状态机的默认启动状态
#pragma warning(disable:4251)
	std::map<std::string,CAIState*>	m_pStates;	// 状态
#pragma warning(default:4251)
};



AISYSTEM_SPACE_END