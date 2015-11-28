/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIBrain.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  定义AI对象的大脑类,客户代码中的AI对象都要将这个类作为一个成员
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAIBrain
+   功能:	AI对象的大脑
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class CAIStateMachine;
class CProperty;
class CPropertySet;
class IAIObject;

class CAIBrain
{
	////////////////////////////////////////////
	//	数据成员
private:
	CPropertySet	*m_pPropertySet;	// 属性集
	CAIStateMachine	*m_pStateMachine;	// 状态机
	IAIObject		*m_pAIObject;		// AI对象

	int			m_eBehaviorState;	// 当前的行为状态
	static int	s_eExecuting;
	static int	s_eInterrupt;
	static int	s_eFailed;
	static int	s_eSucced;

	////////////////////////////////////////////
	//	构造/析构函数
public:
	CAIBrain( IAIObject *pAIObject );
	virtual ~CAIBrain( void );

	////////////////////////////////////////////
	//	公共接口
public:
	/*  
	@	功能：	更新接口
	@	参数：	fElapsedTimes:	逝去的时间
	@	返回值：
	@	注：	更新状态机
	*/
	void Update( float fElapsedTimes );

	/*  
	@	功能：	启动大脑
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void StartUp( void );

	/*  
	@	功能：	停止大脑的工作
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void ShutDown( void );

	/*  
	@	功能：	让大脑暂停
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void Pause( void );

	/*  
	@	功能：	恢复大脑的动作
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void Resume( void );

	/*  
	@	功能：	载入状态机
	@	参数：	strStateMachineName:	状态机的名字
	@	返回值：是否成功
	@	注：	
	*/
	bool LoadStateMachine( const std::string strStateMachineName );

	/*  
	@	功能：	注册属性，返回一个ID
	@	参数：	
	@	返回值：属性ID，0表示注册失败
	@	注：	
	*/
	unsigned long RegisterProperty( const std::string & strName, int *pValue );
	unsigned long RegisterProperty( const std::string & strName, float *pValue );
	unsigned long RegisterProperty( const std::string & strName, bool *pValue );
	unsigned long RegisterProperty( const std::string & strName, unsigned long *pValue );
	unsigned long RegisterProperty( const std::string & strName, std::string *pValue );

	/*  
	@	功能：	查找一个属性
	@	参数：	strName:	属性的名字
	@	返回值：属性指针
	@	注：	
	*/
	CProperty *FindProperty( const std::string & strName );

	/*  
	@	功能：	查询AI对象
	@	参数：	
	@	返回值：
	@	注：	
	*/
	IAIObject *GetAIObject( void )	{ return m_pAIObject; }

	/*  
	@	功能：	
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void SetCurBehaviorState( EAIBehaviorState eState )
	{
		m_eBehaviorState = (int)eState;
	}

	/*  
	@	功能：	判断指定行为是否正在执行
	@	参数：	strBehaviorName:	行为的名称
	@	返回值：正在执行行为返回true；否则返回false
	@	注：	
	*/
	bool IsBehaviorRunning( const std::string &strBehaviorName );

	/*  
	@	功能：	强行中止一个行为
	@	参数：	uiBehaviorTypeID:	要中止的行为的ID
	@	返回值：如果当前状态正在执行行为，则中止并返回true，否则返回false
	@	注：	
	*/
	bool StopBehavior( const std::string &strBehaviorName );
	
};




AISYSTEM_SPACE_END