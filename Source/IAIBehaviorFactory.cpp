#include "../PreInclude.h"
#include "../Include/IAIBehaviorFactory.h"
#include "../Include/IAIBehavior.h"
#include "../Include/AIStateDefine.h"
#include "../Include/AICrc32.h"

#include "../Include/IAIGlobalFunc.h"



AISYSTEM_SPACE_BEGIN


using namespace std;

IAIBehaviorFactory *IAIBehaviorFactory::s_pFactory = NULL;


IAIBehaviorFactory::IAIBehaviorFactory(void) 
{
}

IAIBehaviorFactory::~IAIBehaviorFactory(void)
{
	m_BehaviorCreators.clear();
}

/*  
@	功能：	获取AI工厂的静态实例
@	参数：	
@	返回值：
@	注：	
*/
IAIBehaviorFactory *IAIBehaviorFactory::Instance( void )
{
	return s_pFactory;
}

/*  
@	功能：	创建一个AI行为
@	参数：	pBehaviorParams:	行为的参数
@	返回值：创建的AI
@	注：	
*/
IAIBehavior *IAIBehaviorFactory::CreateBehavior( IAIObject *pAIObject, CBehaviorParams *pBehaviorParams /*= NULL*/ )
{
	if( NULL == pBehaviorParams || NULL == pAIObject )
		return NULL;

	std::map<unsigned int,FuncCreateBehavior>::iterator iter = m_BehaviorCreators.find( pBehaviorParams->m_uiAIID );
	if( iter == m_BehaviorCreators.end() )
	{
		// 试图创建一个没有注册的行为
		OutPutErrorMsg( "试图创建一个没有注册的行为" );
		return NULL;
	}

	FuncCreateBehavior pFunc = iter->second;
	IAIBehavior *pNewBehavior = pFunc( pBehaviorParams );
	if( pNewBehavior )
		pNewBehavior->SetMaster( pAIObject );
	return pNewBehavior;
}

/*  
@	功能：	生成一个行为类型ID
@	参数：	strName:	行为的名字
@	返回值：ID
@	注：	
*/
unsigned int IAIBehaviorFactory::GenerateID( const string & strName )
{
	static Crc32 theCrc;
	return theCrc.GetCRC( strName.c_str() );
}

/*  
@	功能：	注册一个行为构造器
@	参数：	strName:	行为构造器的名字
			pCreator:	行为构造器指针
@	返回值：如果已经有这个构造器名字了，返回失败
@	注：	
*/
bool IAIBehaviorFactory::_RegisterCreator( const string & strName, FuncCreateBehavior pCreator )
{
	unsigned int ID = GenerateID( strName );
	TCreatorDictionary::iterator iter = m_BehaviorCreators.find( ID );
	if( iter != m_BehaviorCreators.end() )
		return false;

	m_BehaviorCreators.insert( make_pair( ID, pCreator ) );
	return true;
}

/*  
@	功能：	注销一个行为构造器
@	参数：	strName:	要注销的行为构造器的名字
@	返回值：
@	注：	
*/
void IAIBehaviorFactory::_UnregisterCreator( const string & strName )
{
	unsigned int ID = GenerateID( strName );
	TCreatorDictionary::iterator iter = m_BehaviorCreators.find( ID );
	if( iter != m_BehaviorCreators.end() )
		m_BehaviorCreators.erase( iter );
}






AISYSTEM_SPACE_END