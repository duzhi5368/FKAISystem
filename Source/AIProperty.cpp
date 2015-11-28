#include "../PreInclude.h"
#include "../Include/AIProperty.h"
#include "../Include/IAIGlobalFunc.h"


using namespace std;

AISYSTEM_SPACE_BEGIN



/*  
@	功能：	默认构造函数
@	参数：	
@	返回值：
@	注：	
*/
CProperty::CProperty( void )
: m_Type( EDT_End )
, m_uiID( 0 )
{
	m_Data.m_pBool = NULL;
}

/*  
@	功能：	析构函数
@	参数：	
@	返回值：
@	注：	
*/
CProperty::~CProperty( void )
{

}

/*  
@	功能：	注册整型数据
@	参数：	
@	返回值：
@	注：	
*/
void CProperty::Register( int *pInt )
{
	m_Data.m_pInt	= pInt;
	m_Type			= EDT_Int;
}

/*  
@	功能：	注册浮点型数据
@	参数：	
@	返回值：
@	注：	
*/
void CProperty::Register( float *pFloat )
{
	m_Data.m_pFloat	= pFloat;
	m_Type			= EDT_Float;
}

/*  
@	功能：	注册无符号长整型
@	参数：	
@	返回值：
@	注：	
*/
void CProperty::Register( unsigned long *pUnsignedLog )
{
	m_Data.m_pUnsignedLong	= pUnsignedLog;
	m_Type					= EDT_UnsignedLong;
}

/*  
@	功能：	注册布尔型
@	参数：	
@	返回值：
@	注：	
*/
void CProperty::Register( bool *pBool )
{
	m_Data.m_pBool	= pBool;
	m_Type			= EDT_Bool;
}

/*  
@	功能：	注册字符串类型
@	参数：	
@	返回值：
@	注：	
*/
void CProperty::Register( string *pString )
{
	m_Data.m_pString	= pString;
	m_Type				= EDT_String;
}

/*  
@	功能：	设置整数型数据
@	参数：	
@	返回值：是否成功设置
@	注：	
*/
bool CProperty::SetValue( int iValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		( *m_Data.m_pInt ) = (int)iValue;
		return true;
	case EDT_Float:
		( *m_Data.m_pFloat ) = (float)iValue;
		return true;
	case EDT_UnsignedLong:
		( *m_Data.m_pUnsignedLong ) = (unsigned long)iValue;
		return true;
	case EDT_Bool:
		( *m_Data.m_pBool ) = ( iValue == 0 ? false : true );
		return true;
	}

	return false;
}

/*  
@	功能：	设置浮点数据值
@	参数：	
@	返回值：是否成功设置
@	注：	
*/
bool CProperty::SetValue( float fValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		( *m_Data.m_pInt ) = (int)fValue;
		return true;
	case EDT_Float:
		( *m_Data.m_pFloat ) = (float)fValue;
		return true;
	case EDT_UnsignedLong:
		( *m_Data.m_pUnsignedLong ) = (unsigned long)fValue;
		return true;
	case EDT_Bool:
		( *m_Data.m_pBool ) = ( fValue == .0f ? false : true );
		return true;
	}

	return false;
}

/*  
@	功能：	设置无符号长整数型数据值
@	参数：	
@	返回值：是否成功设置
@	注：	
*/
bool CProperty::SetValue( unsigned long ulValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		( *m_Data.m_pInt ) = (int)ulValue;
		return true;
	case EDT_Float:
		( *m_Data.m_pFloat ) = (float)ulValue;
		return true;
	case EDT_UnsignedLong:
		( *m_Data.m_pUnsignedLong ) = (unsigned long)ulValue;
		return true;
	case EDT_Bool:
		( *m_Data.m_pBool ) = ( ulValue == 0 ? false : true );
		return true;
	}

	return false;
}

/*  
@	功能：	设置布尔型数据值
@	参数：	
@	返回值：是否成功设置
@	注：	
*/
bool CProperty::SetValue( bool bValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		( *m_Data.m_pInt ) = (int)bValue;
		return true;
	case EDT_Float:
		( *m_Data.m_pFloat ) = (float)bValue;
		return true;
	case EDT_UnsignedLong:
		( *m_Data.m_pUnsignedLong ) = (unsigned long)bValue;
		return true;
	case EDT_Bool:
		( *m_Data.m_pBool ) = bValue;
		return true;
	}

	return false;
}

/*  
@	功能：	设置字符串型数据值
@	参数：	
@	返回值：是否成功设置
@	注：	
*/
bool CProperty::SetValue( const string &strValue )
{
	if( m_Type == EDT_String )
	{
		( *m_Data.m_pString ) = strValue;
		return true;
	}
	return false;
}

/*  
@	功能：	查询整数型值
@	参数：	
@	返回值：是否成功
@	注：	
*/
bool CProperty::GetValue( int &iValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		iValue = (int)( *m_Data.m_pInt );
		return true;
	case EDT_Float:
		iValue = (int)( *m_Data.m_pFloat );
		return true;
	case EDT_UnsignedLong:
		iValue = (int)( *m_Data.m_pUnsignedLong );
		return true;
	case EDT_Bool:
		iValue = (int)( *m_Data.m_pBool );
		return true;
	}
	return false;
}

/*  
@	功能：	查询浮点型值
@	参数：	
@	返回值：是否成功
@	注：	
*/
bool CProperty::GetValue( float &fValue )
{
	switch( m_Type )
	{
	case EDT_Int:
		fValue = (float)( *m_Data.m_pInt );
		return true;
	case EDT_Float:
		fValue = (float)( *m_Data.m_pFloat );
		return true;
	case EDT_UnsignedLong:
		fValue = (float)( *m_Data.m_pUnsignedLong );
		return true;
	case EDT_Bool:
		fValue = (float)( *m_Data.m_pBool );
		return true;
	}
	return false;
}

/*  
@	功能：	查询浮点无符号长型值
@	参数：	
@	返回值：是否成功
@	注：	
*/
bool CProperty::GetValue( unsigned long &value )
{
	switch( m_Type )
	{
	case EDT_Int:
		value = (unsigned long)( *m_Data.m_pInt );
		return true;
	case EDT_Float:
		value = (unsigned long)( *m_Data.m_pFloat );
		return true;
	case EDT_UnsignedLong:
		value = (unsigned long)( *m_Data.m_pUnsignedLong );
		return true;
	case EDT_Bool:
		value = (unsigned long)( *m_Data.m_pBool );
		return true;
	}
	return false;
}

/*  
@	功能：	查询布尔型值
@	参数：	
@	返回值：是否成功
@	注：	
*/
bool CProperty::GetValue( bool &value )
{
	switch( m_Type )
	{
	case EDT_Int:
		value = ( ( *m_Data.m_pInt ) == 0 ? false : true );
		return true;
	case EDT_Float:
		value = ( ( *m_Data.m_pFloat ) == .0f ? false : true );
		return true;
	case EDT_UnsignedLong:
		value = ( ( *m_Data.m_pUnsignedLong ) == 0 ? false : true );
		return true;
	case EDT_Bool:
		value = ( *m_Data.m_pBool );
		return true;
	}
	return false;
}

/*  
@	功能：	查询字符串型值
@	参数：	
@	返回值：是否成功
@	注：	
*/
bool CProperty::GetValue( string &value )
{
	if( m_Type == EDT_String )
	{
		value = ( *m_Data.m_pString );
		return true;
	}
	return false;
}

double CProperty::GetDouble( void )
{
	switch( m_Type )
	{
	case EDT_Int:
		return *m_Data.m_pInt;
	case EDT_Float:
		return ( *m_Data.m_pFloat );
	case EDT_UnsignedLong:
		return ( *m_Data.m_pUnsignedLong );
	case EDT_Bool:
		return ( *m_Data.m_pBool );
	}
	// 想将一个字符串当数值用
	OutPutErrorMsg( "企图从一个非数字属性中取得一个数字" );
	return 0;
}


AISYSTEM_SPACE_END