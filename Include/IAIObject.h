/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIObject.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  AI对象定义
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


class CAIBrain;

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	IAIObject
+   功能:	AI对象的基类，游戏中如果要使用AI系统，则游戏中的AI对象
			必须从该类派生，并且实现注册属性集的方法
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class FKAISYSTEM_API IAIObject
{
	////////////////////////////////////////////
	//	数据成员
private:
	CAIBrain	*m_pAIBrain;		// 大脑


	////////////////////////////////////////////
	//	构造/析构
public:
	IAIObject( void );
	virtual ~IAIObject( void ){}

	////////////////////////////////////////////
	//	方法
public:
	/*  
	@	功能：	初始化AI系统，包括创建大脑，注册属性
	@	参数：	strStateMachineName:	状态机的名字
	@	返回值：操作成功的话返回去 true
	@	注：	
	*/
	bool InitAISystem( const std::string & strStateMachineName );

	/*  
	@	功能：	更新AI
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void AIUpdate( float fElapsedTimes );

	/*  
	@	功能：	启动AI
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void AIStartUp( void );

	/*  
	@	功能：	停止AI
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void AIShutDown( void );

	/*  
	@	功能：	暂停AI
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void AIPause( void );

	/*  
	@	功能：	恢复AI的运行
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void AIResume( void );

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

	////////////////////////////////////////////
	//	私有方法
protected:
	/*  
	@	功能：	注册所有的属性
	@	参数：	
	@	返回值：
	@	注：	
	*/
	virtual void _RegisterProperties( void ) {};
};








AISYSTEM_SPACE_END