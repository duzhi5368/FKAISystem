#include "../PreInclude.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/IAIBehaviorFactory.h"
#include "../Include/IAITriggerFactory.h"
#include "../Include/AITinyxml.h"

using namespace std;


AISYSTEM_SPACE_BEGIN

/*  
@	功能：	查找一个状态
@	参数：	strStateName:	状态的名字
@	返回值：状态指针
@	注：	
*/
CAIStateData * CAIMachineData::FindState( const std::string & strStateName )
{
	if( m_StateMap.size() == 0 )
		return NULL;

	map<string,CAIStateData>::iterator iter = m_StateMap.find( strStateName );
	if( iter != m_StateMap.end() )
		return &iter->second;

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


/*  
@	功能：	查找一个状态机
@	参数：	strMachineName:	状态机的名字
@	返回值：查找到的状态机数据指针
@	注：	
*/
CAIMachineData * CAIMachineTable::FindMachine( const std::string & strMachineName )
{
	if( m_MachineMap.size() == 0 )
		return NULL;

	map<string,CAIMachineData>::iterator iter = m_MachineMap.find( strMachineName );
	if( iter != m_MachineMap.end() )
		return &iter->second;

	return NULL;
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



CAIStateInfoManager::CAIStateInfoManager(void)
: m_bInited( false )
{
	m_strFilePath = "";
}

CAIStateInfoManager::~CAIStateInfoManager(void)
{
}


/*  
@	功能：	获得该类的单体实例
@	参数：	
@	返回值：该类的单体实例
@	注：	
*/
CAIStateInfoManager * CAIStateInfoManager::Instance( void )
{
	static CAIStateInfoManager CStateInfoManagerObj;
	return &CStateInfoManagerObj;
}

/*  
@	功能：	查找一个状态机表
@	参数：	strMachineName:	要查找的状态机表的名字
@	返回值：状态机表指针，如果没有找到，返回NULL
@	注：	
*/
CAIMachineTable * CAIStateInfoManager::FindMachineTable( const std::string & strMachineTableName )
{
	if( ! m_bInited || m_MachineTableMap.size() == 0 )
		return NULL;

	map<string,CAIMachineTable>::iterator iter = m_MachineTableMap.find( strMachineTableName );
	if( iter != m_MachineTableMap.end() )
		return &iter->second;
	return NULL;
}

/*  
@	功能：	设置状态机定义文件的路径
@	参数：	strFilePath:	路径名称
@	返回值：
@	注：	
*/
void CAIStateInfoManager::SetAIFileDirectory( const std::string & strFilePath )
{
	m_strFilePath = strFilePath;
}

/*  
@	功能：	从AI目录载入所有的状态表
@	参数：	
@	返回值：是否成功
@	注：	
*/
bool CAIStateInfoManager::_LoadInfo( void )
{
	// 枚举所有的文件，并载入
	WIN32_FIND_DATA FindData;
	size_t len = m_strFilePath.length();
	char ch = m_strFilePath.at( len - 1 );
	string strFileFilter;
	if( ch != '/' && ch != '\\' )
		m_strFilePath += "/";

	strFileFilter = m_strFilePath + "*.xml";
	HANDLE hFileFind = FindFirstFile( strFileFilter.c_str(), &FindData );
	if( INVALID_HANDLE_VALUE == hFileFind )
		return false;

	BOOL bSuccFound = FALSE;
	string strFileFullPath;
	do 
	{
		strFileFullPath = m_strFilePath + FindData.cFileName;
		if( ! _LoadInfoFromFile( strFileFullPath ) )
		{
			// AILOG;
		}
		bSuccFound = FindNextFile( hFileFind, &FindData );
	} while( bSuccFound == TRUE );

	m_bInited = true;
	return true;
}

/*  
@	功能：	从指定文件载入一个状态机表
@	参数：	strFileName:	状态机表文件名
@	返回值：是否成功
@	注：	
*/
bool CAIStateInfoManager::_LoadInfoFromFile( const std::string & strFileName )
{
	TiXmlDocument Doc;
	if( ! Doc.LoadFile( strFileName.c_str() ) )
		return false;

	CAIMachineTable MachineTable;

	// 载入所有的状态机
	TiXmlElement *pMachineTable = Doc.FirstChildElement();
	TiXmlElement *pMachine		= pMachineTable->FirstChildElement();

	while( pMachine )
	{
		if( !_LoadMachine( pMachine, MachineTable ) )
		{
			// AILOG;	
		}		
		pMachine = pMachine->NextSiblingElement();
	}

	MachineTable.m_strName = pMachineTable->Value();	// 文件名作为状态机表的名字
	MachineTable.m_strMainMachine = pMachineTable->Attribute( "StartMachine" );
	m_MachineTableMap.insert( make_pair( MachineTable.m_strName, MachineTable ) );
	MachineTable.m_MachineMap.clear();
	return true;
}

/*  
@	功能：	从文件载入一个状态机
@	参数：	pMachine:		状态机的文件访问指针
			MachineTable:	载入的状态机的容器
@	返回值：是否成功
@	注：	
*/
bool CAIStateInfoManager::_LoadMachine( TiXmlElement *pMachine, CAIMachineTable &MachineTable )
{
	if( NULL == pMachine )
		return false;
	CAIMachineData MachineData;

	// 载入所有的状态
	TiXmlElement *pState = pMachine->FirstChildElement();
	while( pState )
	{
		if( ! _LoadState( pState, MachineData ) )
		{
			// AILOG;
		}
		pState = pState->NextSiblingElement();
	}
	MachineData.m_strName = pMachine->Attribute( "MachineName" );
	MachineData.m_strDefaultState	= pMachine->Attribute( "DefaultState" );
	MachineTable.m_MachineMap.insert( make_pair( MachineData.m_strName, MachineData ) );
	MachineData.m_StateMap.clear();
	return true;
}

/*  
@	功能：	从文件载入一个状态
@	参数：	pState:			状态的文件访问指针
			MachineData:	状态机，载入的状态的容器
@	返回值：是否成功
@	注：	
*/
bool CAIStateInfoManager::_LoadState( TiXmlElement *pState, CAIMachineData &MachineData )
{
	if( NULL == pState )
		return false;

	CAIStateData StateData;
	// 载入AI数据
	TiXmlElement *pAI = pState->FirstChildElement( "AI" );
	if( pAI )
	{
		// AI类型
		static std::string strAIType = "";
		strAIType = pAI->Attribute( "AIType" );
		if( strAIType != "" )
		{
			StateData.m_uiAIID = IAIBehaviorFactory::Instance()->GenerateID( strAIType );
			// AI参数
			StateData.m_AIParams = pAI->Attribute( "AIParams" );
		}
		else
		{
			StateData.m_uiAIID = 0;
		}

	}

	// 载入触发器数据
	TiXmlElement *pTrigger	= pState->FirstChildElement( "Triggers" )->FirstChildElement();
	while( pTrigger )
	{
		if( ! _LoadTrigger( pTrigger, StateData ) )
		{
			// AILOG;
		}
		pTrigger = pTrigger->NextSiblingElement();
	}

	// 子状态机
	StateData.m_strSubStateMachineName = pState->Attribute( "SubState" );

	StateData.m_strName = pState->Attribute( "StateName" );
	MachineData.m_StateMap.insert( make_pair( StateData.m_strName, StateData ) );

	return true;
}

/*  
@	功能：	从文件载入触发器
@	参数：	pTrigger:	触发器的文件访问指针
			StateData:	状态，触发器的容器
@	返回值：是否成功
@	注：	
*/
bool CAIStateInfoManager::_LoadTrigger( TiXmlElement *pTrigger, CAIStateData &StateData )
{
	if( NULL == pTrigger )
		return false;

	CAITriggerData TriggerData;
	TriggerData.m_strNextStateName = pTrigger->Attribute( "NextState" );
	TriggerData.m_strExpression = pTrigger->Attribute( "TriParams" );
	StateData.m_Triggers.push_back( TriggerData );

	return true;
}


AISYSTEM_SPACE_END