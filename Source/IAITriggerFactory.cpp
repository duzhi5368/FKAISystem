#include "../PreInclude.h"
//#include "IAITriggerFactory.h"
//#include "AIStateInfoManager.h"
//#include "AICrc32.h"
//#include "AITriggerCondition.h"
//
//
//AISYSTEM_SPACE_BEGIN
//
//
//using namespace std;
//
//
//IAITriggerFactory::IAITriggerFactory(void)
//{
//	m_uiConditionID = GenerateID( "Condition" );
//}
//
//IAITriggerFactory::~IAITriggerFactory(void)
//{
//	m_TriggerCreators.clear();
//}
//
///*  
//@	功能：	获取AI工厂的静态实例
//@	参数：	
//@	返回值：
//@	注：	
//*/
//IAITriggerFactory *IAITriggerFactory::Instance( void )
//{
//	static IAITriggerFactory CTriggerFactoryObj;
//	return &CTriggerFactoryObj;
//	return NULL;
//}
//
///*  
//@	功能：	创建一个AI行为
//@	参数：	pBehaviorParams:	行为的参数
//@	返回值：创建的AI
//@	注：	
//*/
//CAITrigger *IAITriggerFactory::CreateTrigger( CAICustomTriggerParams *pTriggerData /*= NULL*/ )
//{
//	if( NULL == pTriggerData )
//		return NULL;
//
//	std::map<unsigned int,FuncCreateTrigger>::iterator iter = m_TriggerCreators.find( pTriggerData->m_uiTriggerTypeID );
//	if( iter == m_TriggerCreators.end() )
//	{
//		// AI LOG 试图创建一个没有注册的用户自定义触发器
//		return NULL;
//	}
//
//	FuncCreateTrigger pFunc = iter->second;
//	return pFunc( pTriggerData );
//}
//
///*  
//@	功能：	生成一个行为类型ID
//@	参数：	strName:	行为的名字
//@	返回值：ID
//@	注：	
//*/
//unsigned int IAITriggerFactory::GenerateID( const string & strName )
//{
//	static Crc32 theCrc;
//	return theCrc.GetCRC( strName.c_str() );
//}
//
///*  
//@	功能：	查询条件触发器类型ID
//@	参数：	strName:	触发器类型名称
//@	返回值：
//@	注：	
//*/
//unsigned int IAITriggerFactory::GetConditionTypeID( void )
//{
//	return m_uiConditionID;
//}
//
///*  
//@	功能：	注册一个行为构造器
//@	参数：	strName:	行为构造器的名字
//pCreator:	行为构造器指针
//@	返回值：如果已经有这个构造器名字了，返回失败
//@	注：	
//*/
//bool IAITriggerFactory::_RegisterCreator( const string & strName, FuncCreateTrigger pCreator )
//{
//	unsigned int ID = GenerateID( strName );
//	TCreatorDictionary::iterator iter = m_TriggerCreators.find( ID );
//	if( iter != m_TriggerCreators.end() )
//		return false;
//
//	m_TriggerCreators.insert( make_pair( ID, pCreator ) );
//	return true;
//}
//
///*  
//@	功能：	注销一个行为构造器
//@	参数：	strName:	要注销的行为构造器的名字
//@	返回值：
//@	注：	
//*/
//void IAITriggerFactory::_UnregisterCreator( const string & strName )
//{
//	unsigned int ID = GenerateID( strName );
//	TCreatorDictionary::iterator iter = m_TriggerCreators.find( ID );
//	if( iter != m_TriggerCreators.end() )
//		m_TriggerCreators.erase( iter );
//}
//
//
//AISYSTEM_SPACE_END