/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIStateInfoManager.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIStateDefine.h"

#pragma warning(disable:4251)


AISYSTEM_SPACE_BEGIN


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAITriggerData
+   功能：	结构体，保存触发器的数据，以及触发器关联的状态
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class CAITriggerData
{
	////////////////////////////////////////////
	//	数据成员
public:
	std::string					m_strExpression;	// 条件表达式
	std::string					m_strNextStateName;	// 条件满足时跳转到的状态的名字
};


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAIStateData
+   功能：	存储状态数据
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class CAIStateData
{
	////////////////////////////////////////////
	//	数据成员
public:
	std::string					m_strName;	// 状态的名字
	unsigned int				m_uiAIID;	// 状态的AI类型ID
	std::string					m_AIParams;	// 状态的AI参数
	std::vector<CAITriggerData>	m_Triggers;	// 状态的触发器
	std::string					m_strSubStateMachineName;	// 子状态机名字
};


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAIMachineData
+   功能：	保存一个状态机
+   描述:	保存一个状态机的所有的状态
-----------------------------------------------------------------
*****************************************************************/
class CAIMachineData
{
	////////////////////////////////////////////
	//	外部接口
public:
	/*  
	@	功能：	查找一个状态
	@	参数：	strStateName:	状态的名字
	@	返回值：状态指针
	@	注：	
	*/
	CAIStateData * FindState( const std::string & strStateName );

	////////////////////////////////////////////
	//	数据成员
public:
	std::string							m_strName;			// 状态机的名字
	std::string							m_strDefaultState;	// 状态机的默认启动状态
	std::map<std::string,CAIStateData>	m_StateMap;			// 状态表，保存所有的状态
};


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAIMachineTable
+   功能：	保存一系列的状态机
+   描述:	每种AI体的状态机保存在一个文件里，
			这个类保存从文件里读入的数据，供创建状态时用
-----------------------------------------------------------------
*****************************************************************/
class CAIMachineTable
{
	////////////////////////////////////////////
	//	外部接口
public:
	/*  
	@	功能：	查找一个状态机
	@	参数：	strMachineName:	状态机的名字
	@	返回值：查找到的状态机数据指针
	@	注：	
	*/
	CAIMachineData * FindMachine( const std::string & strMachineName );

	////////////////////////////////////////////
	//	数据成员
public:
	std::string								m_strName;		// 状态机表的名字
	std::map<std::string,CAIMachineData>	m_MachineMap;	// 状态机表，保存所有的状态机
	std::string								m_strMainMachine;	// 主状态机的名字
};

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CAIStateInfoManager
+   功能：	管理所有的状态机表
+   描述:	1、	每个状态机表是一个AI体(如某类怪物)的AI系统，当创建一个
				AI体时，从这里查询相应的AI系统，来创建状态机
			2、	单体类
-----------------------------------------------------------------
*****************************************************************/
class TiXmlElement;

class CAIStateInfoManager
{
	////////////////////////////////////////////
	//	构造/析构
public:
	CAIStateInfoManager(void);
	~CAIStateInfoManager(void);

	////////////////////////////////////////////
	//	外部接口
public:

	/*  
	@	功能：	获得该类的单体实例
	@	参数：	
	@	返回值：该类的单体实例
	@	注：	
	*/
	static CAIStateInfoManager * Instance( void );

	/*  
	@	功能：	查找一个状态机表
	@	参数：	strMachineName:	要查找的状态机表的名字
	@	返回值：状态机表指针，如果没有找到，返回NULL
	@	注：	
	*/
	CAIMachineTable * FindMachineTable( const std::string & strMachineTableName );

	/*  
	@	功能：	
	@	参数：	
	@	返回值：
	@	注：	
	*/
	bool Initialize( void )
	{
		return _LoadInfo();
	}

	/*  
	@	功能：	设置状态机定义文件的路径
	@	参数：	strFilePath:	路径名称
	@	返回值：
	@	注：	
	*/
	void SetAIFileDirectory( const std::string & strFilePath );

	////////////////////////////////////////////
	//	内部接口
protected:
	/*  
	@	功能：	从AI目录载入所有的状态表
	@	参数：	
	@	返回值：是否成功
	@	注：	
	*/
	bool _LoadInfo( void );

	/*  
	@	功能：	从指定文件载入一个状态表
	@	参数：	strFileName:	状态表文件名
	@	返回值：是否成功
	@	注：	
	*/
	bool _LoadInfoFromFile( const std::string & strFileName );

	/*  
	@	功能：	从文件载入一个状态机
	@	参数：	pMachine:		状态机的文件访问指针
				MachineTable:	载入的状态机的容器
	@	返回值：是否成功
	@	注：	
	*/
	bool _LoadMachine( TiXmlElement *pMachine, CAIMachineTable &MachineTable );

	/*  
	@	功能：	从文件载入一个状态
	@	参数：	pState:			状态的文件访问指针
				MachineData:	状态机，载入的状态的容器
	@	返回值：是否成功
	@	注：	
	*/
	bool _LoadState( TiXmlElement *pState, CAIMachineData &MachineData );

	/*  
	@	功能：	从文件载入触发器
	@	参数：	pTrigger:	触发器的文件访问指针
				StateData:	状态，触发器的容器
	@	返回值：是否成功
	@	注：	
	*/
	bool _LoadTrigger( TiXmlElement *pTrigger, CAIStateData &StateData );

	////////////////////////////////////////////
	//	数据成员
private:
	std::map<std::string,CAIMachineTable>	m_MachineTableMap;	// 状态机表的表，因为每个AI对象的AI有多个状态机，是一个状态机表，所以这里保存所有AI对象的状态机就是表的表了
	bool									m_bInited;			// 是否初始化
	std::string								m_strFilePath;		// AI文件路径
};


AISYSTEM_SPACE_END


#pragma warning(default:4251)