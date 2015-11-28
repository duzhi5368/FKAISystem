/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIBehaviorFactory.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  行为工厂 
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#pragma warning(disable:4251)

AISYSTEM_SPACE_BEGIN

//--------------------------------------------------------------------

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	IAIBehaviorFactory
+   功能：	AI工厂，负责AI的创建工作
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class IAIBehavior;
class CBehaviorParams;
class IAIObject;

class FKAISYSTEM_API IAIBehaviorFactory
{
	////////////////////////////////////////////
	//	内部类型定义
public:
	typedef IAIBehavior* (*FuncCreateBehavior)( CBehaviorParams *pBehaviorParams );	// 行为创建器指针类型
	typedef std::map<unsigned int,FuncCreateBehavior> TCreatorDictionary;			// 行为字典类型
	static IAIBehaviorFactory *s_pFactory;

	////////////////////////////////////////////
	//	构造/析构
public:
	IAIBehaviorFactory(void);
	~IAIBehaviorFactory(void);

	////////////////////////////////////////////
	//	公共接口
public:

	/*  
	@	功能：	获取AI工厂的静态实例
	@	参数：	
	@	返回值：
	@	注：	
	*/
	static IAIBehaviorFactory *Instance( void );

	/*  
	@	功能：	初始化
	@	参数：	
	@	返回值：注册所有的行为创建器
	@	注：	用户需要实现这个方法
	*/
	virtual bool Init( void ){ return false; };

	/*  
	@	功能：	创建一个AI行为
	@	参数：	pAIObject:		为哪个AI对象创建行为
				pBehaviorParams:行为的参数
	@	返回值：创建的AI
	@	注：	
	*/
	IAIBehavior *CreateBehavior( IAIObject *pAIObject, CBehaviorParams *pBehaviorParams = NULL );

	/*  
	@	功能：	销毁一个行为
	@	参数：	
	@	返回值：
	@	注：	
	*/
	virtual void DestoryBehavior( IAIBehavior *pBehavior ){};

	/*  
	@	功能：	生成一个行为类型ID
	@	参数：	strName:	行为的名字
	@	返回值：ID
	@	注：	
	*/
	unsigned int GenerateID( const std::string & strName );

	////////////////////////////////////////////
	//	内部接口
protected:
	/*  
	@	功能：	注册一个行为构造器
	@	参数：	strName:	行为构造器的名字
				pCreator:	行为构造器指针
	@	返回值：如果已经有这个构造器名字了，返回失败
	@	注：	
	*/
	bool _RegisterCreator( const std::string & strName, FuncCreateBehavior pCreator );

	/*  
	@	功能：	注销一个行为构造器
	@	参数：	strName:	要注销的行为构造器的名字
	@	返回值：
	@	注：	
	*/
	void _UnregisterCreator( const std::string & strName );


	////////////////////////////////////////////
	//	内部接口
protected:

	////////////////////////////////////////////
	//	数据成员
protected:
	TCreatorDictionary	m_BehaviorCreators;	// 行为构造器
};


//--------------------------------------------------------------------

AISYSTEM_SPACE_END


#pragma warning(default:4251)