#include "../PreInclude.h"
#include "../Include/AIpropertyset.h"
#include "../Include/AICrc32.h"


using namespace std;


AISYSTEM_SPACE_BEGIN



/*  
@	功能：	构造函数
@	参数：	
@	返回值：
@	注：	
*/
CPropertySet::CPropertySet( void )
{

}

/*  
@	功能：	析构函数
@	参数：	
@	返回值：
@	注：	
*/
CPropertySet::~CPropertySet( void )
{

}

/*  
@	功能：	根据ID查找一个属性
@	参数：	ID:	
@	返回值：
@	注：	
*/
CProperty *CPropertySet::FindProperty(unsigned long ID)
{
	if( m_Properties.size() == 0 )
		return NULL;

	TPropertyIter iter = m_Properties.find( ID );
	if( iter != m_Properties.end() )
	{
		return &iter->second;
	}

	return NULL;
}

/*  
@	功能：	根据名字查找一个属性
@	参数：	strName:	属性名字
@	返回值：
@	注：	
*/
CProperty *CPropertySet::FindProperty(const std::string &strName)
{
	if( m_Properties.size() == 0 )
		return NULL;

	unsigned long ID = __GenerateID( strName.c_str() );
	TPropertyIter iter = m_Properties.find( ID );
	if( iter != m_Properties.end() )
	{
		return &iter->second;
	}

	return NULL;
}

/*  
@	功能：	生成一个属性ID
@	参数：	
@	返回值：属性ID
@	注：	
*/
unsigned long CPropertySet::__GenerateID( const char *lpszStr )
{
	static Crc32 theCrc32Gen;
	return theCrc32Gen.GetCRC( lpszStr );
}



AISYSTEM_SPACE_END