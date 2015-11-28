/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAITriggerFactory.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  用户自定义触发器工厂
*********************************************************************/

//#pragma once

//--------------------------------------------------------------------
//
//#pragma warning(disable:4251)
//
//AISYSTEM_SPACE_BEGIN
//
///****************************************************************
//+	CLASS
//-----------------------------------------------------------------
//+   类名:	IAITriggerFactory
//+   功能：	触发器工厂，负责 用户自定义触发器 的创建工作
//+   描述:	
//-----------------------------------------------------------------
//*****************************************************************/
//class CAITrigger;
//class CAITriggerData;
//
//class FKAISYSTEM_API IAITriggerFactory
//{
//	////////////////////////////////////////////
//	//	类型定义
//	typedef CAITrigger* (*FuncCreateTrigger)( CAICustomTriggerParams *pTriggerData );
//	typedef std::map<unsigned int,FuncCreateTrigger> TCreatorDictionary;
//
//	////////////////////////////////////////////
//	//	数据成员
//protected:
//	TCreatorDictionary	m_TriggerCreators;	// 触发器构造器
//	unsigned int		m_uiConditionID;	// 条件触发器类型ID
//
//	////////////////////////////////////////////
//	//	构造/析构
//public:
//	IAITriggerFactory(void);
//	~IAITriggerFactory(void);
//
//	////////////////////////////////////////////
//	//	公共接口
//public:
//
//	/*  
//	@	功能：	获取触发器工厂的静态实例
//	@	参数：	
//	@	返回值：
//	@	注：	
//	*/
//	static IAITriggerFactory *Instance( void );
//
//	/*  
//	@	功能：	初始化
//	@	参数：	
//	@	返回值：注册所有的触发器创建器
//	@	注：	用户需要实现这个方法
//	*/
//	virtual bool Init( void ){ return false; };
//
//	/*  
//	@	功能：	创建一个触发器
//	@	参数：	pBehaviorParams:	触发器的参数
//	@	返回值：创建的AI
//	@	注：	
//	*/
//	CAITrigger *CreateTrigger( CAICustomTriggerParams *pTriggerData = NULL );
//
//	/*  
//	@	功能：	销毁一个触发器
//	@	参数：	pTrigger:	触发器指针
//	@	返回值：
//	@	注：	
//	*/
//	virtual void DestoryTrigger( CAITrigger *pTrigger ){};
//
//	/*  
//	@	功能：	生成一个触发器类型ID
//	@	参数：	strName:	行为的名字
//	@	返回值：ID
//	@	注：	
//	*/
//	unsigned int GenerateID( const std::string & strName );
//
//	/*  
//	@	功能：	查询条件触发器类型ID
//	@	参数：	strName:	触发器类型名称
//	@	返回值：
//	@	注：	
//	*/
//	unsigned int GetConditionTypeID( void );
//
//	////////////////////////////////////////////
//	//	内部接口
//protected:
//	/*  
//	@	功能：	注册一个触发器构造器
//	@	参数：	strName:	触发器构造器的名字
//				pCreator:	触发器构造器指针
//	@	返回值：如果已经有这个构造器名字了，返回失败
//	@	注：	
//	*/
//	bool _RegisterCreator( const std::string & strName, FuncCreateTrigger pCreator );
//
//	/*  
//	@	功能：	注销一个触发器构造器
//	@	参数：	strName:	要注销的触发器构造器的名字
//	@	返回值：
//	@	注：	
//	*/
//	void _UnregisterCreator( const std::string & strName );
//
//};
//
//
//AISYSTEM_SPACE_END
//
//#pragma warning(default:4251)