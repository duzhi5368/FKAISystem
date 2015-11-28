/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIBehavior.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  定义行为基类
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAIBehabior
+   功能:	行为的基类
+   描述:	
-----------------------------------------------------------------
*****************************************************************/

class IAIObject;

class FKAISYSTEM_API IAIBehavior
{
	friend class IAIBehaviorFactory;

	////////////////////////////////////////////
	//	构造/析构函数
public:
	IAIBehavior(void);
	~IAIBehavior(void);

	////////////////////////////////////////////
	//	外部接口
public:

	/*  
	@	功能：	更新AI，做一些更新的测试，并调用用户实现的更新方法
	@	参数：	fElpasedTimes:	逝去的时间
	@	返回值：返回行为的执行状态
	@	注：	
	*/
	EAIBehaviorState RealUpdate( float fElpasedTimes );

	/*  
	@	功能：	更新AI的运行
	@	参数：	fElpasedTimes:	逝去的时间
	@	返回值：返回行为的执行状态
	@	注：	这是一个纯虚函数，需要由子类来实现
	*/
	virtual EAIBehaviorState Update( float fElpasedTimes ) = 0;

	/*  
	@	功能：	启动行为，做一些行为的初始化
	@	参数：	
	@	返回值：
	@	注：	
	*/
	virtual bool OnStartUp( void ) = 0;

	/*  
	@	功能：	停止行为，作一些善后工作
	@	参数：	
	@	返回值：
	@	注：	
	*/
	virtual void OnShutDown( void ) = 0;

	/*  
	@	功能：	停止行为，但并非立刻停止，仅作出停止的准备	
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void Stop( void )
	{
		m_bStopped = true;
	}

	////////////////////////////////////////////
	//	
public:

	/*  
	@	功能：	设置AI的类型
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void SetAIType( unsigned int uiType )
	{
		m_uiAIType = uiType;
	}

	unsigned int GetAIType( )
	{
		return m_uiAIType;
	}

	/*  
	@	功能：	设置AI的宿主
	@	参数：	pMaster:	宿主
	@	返回值：
	@	注：	
	*/
	void SetMaster( IAIObject *pMaster )
	{
		m_pAIObject = pMaster;
	}

	IAIObject * GetMaster( void )
	{
		return m_pAIObject;
	}


	////////////////////////////////////////////
	//	数据成员
protected:
	unsigned int	m_uiAIType;	// AI的类型
	IAIObject*		m_pAIObject;// AI的宿主
	bool			m_bStopped;	// AI被强行中止了
};

//--------------------------------------------------------------------

AISYSTEM_SPACE_END