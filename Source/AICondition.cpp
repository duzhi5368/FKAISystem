#include "../PreInclude.h"
//#include "AICondition.h"
//#include "AIProperty.h"
//
//
//
//
//AISYSTEM_SPACE_BEGIN
//
//
//
//
//////////////////////////////////////////////
////	注册比较函数
//CAICondition::CompFunc CAICondition::s_CompFunc[EAISTestOperator_End] = 
//{	
//	&CAICondition::_TestAllways,
//	&CAICondition::_TestNever,
//	&CAICondition::_TestLess,
//	&CAICondition::_TestGreate,
//	&CAICondition::_TestEqual,
//	&CAICondition::_TestLessEqual,
//	&CAICondition::_TestGreateEqual,
//	&CAICondition::_TestNotEqual,
//	&CAICondition::_TestInner,
//	&CAICondition::_TestOutter
//};
//
//
///*  
//@	功能：	构造函数
//@	参数：	
//@	返回值：
//@	注：	
//*/
//CAICondition::CAICondition()
//: m_pProperty( NULL )
//, m_eOpType( EAISTestOperator_End )
//{
//	m_RefData[0].m_dwData	= 0;
//	m_RefData[1].m_dwData	= 0;
//	m_eRefType[0]			= ERT_End;
//	m_eRefType[1]			= ERT_End;
//}
//
///*  
//@	功能：	析构函数
//@	参数：	
//@	返回值：
//@	注：	
//*/
//CAICondition::~CAICondition( void )
//{
//}
//
///*  
//@	功能：	测试条件
//@	参数：	fElapsedTimes:	逝去的时间
//@	返回值：是否成立
//@	注：	
//*/
//bool CAICondition::Test( float fElapsedTimes )
//{
//	return ( this->*s_CompFunc[m_eOpType] )( );
//}
//
///*  
//@	功能：	设置条件比较参数
//@	参数：	pProperty:	属性
//			eOpType:	操作类型
//			dwRefValue0:测试参考值0
//			dwRefValue1:测试参考值1
//@	返回值：
//@	注：	
//*/
//void CAICondition::SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, DWORD dwRefValue0, DWORD dwRefValue1 /*= 0*/ )
//{
//	m_pProperty				= pProperty;
//	m_eOpType				= eOpType;
//	m_RefData[0].m_dwData	= dwRefValue0;
//	m_eRefType[0]			= ERT_Dword;
//	m_RefData[1].m_dwData	= dwRefValue1;
//	m_eRefType[1]			= ERT_Dword;
//}
//
///*  
//@	功能：	设置条件比较参数
//@	参数：	pProperty:	属性
//			eOpType:	操作类型
//			fRefValue0:	测试参考值0
//			fRefValue1:	测试参考值1
//@	返回值：
//@	注：	
//*/
//void CAICondition::SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, float fRefValue0, float fRefValue1 /*= .0f*/ )
//{
//	m_pProperty				= pProperty;
//	m_eOpType				= eOpType;
//	m_RefData[0].m_fData	= fRefValue0;
//	m_eRefType[1]			= ERT_Float;
//	m_RefData[1].m_fData	= fRefValue1;
//	m_eRefType[1]			= ERT_Float;
//}
//
///*  
//@	功能：	设置条件比较参数
//@	参数：	pProperty:		属性
//			eOpType:		操作类型
//			pRefProperty:	参考属性
//@	返回值：
//@	注：	
//*/
//void CAICondition::SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, CProperty *pRefProperty0, CProperty *pRefProperty1 /*= NULL*/ )
//{
//	m_pProperty	= pProperty;
//	m_eOpType	= eOpType;
//	m_RefData[0].m_pProperty= pRefProperty0;
//	m_eRefType[0]			= ERT_Property;
//	m_RefData[1].m_pProperty= pRefProperty1;
//	if( m_RefData[1].m_pProperty == NULL )
//		m_eRefType[1]		= ERT_End;
//	else
//		m_eRefType[1]		= ERT_Property;
//}
//
///*  
//@	功能：	小于
//@	参数：	
//@	返回值：
//@	注：	
//*/
//bool CAICondition::_TestLess( void )			
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) < m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) < m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) < m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) < *m_RefData[0].m_pProperty;
//	}
//	return false;
//}	
//
///*  
//@	功能：	大于
//@	参数：	
//@	返回值：
//@	注：	
//*/
//bool CAICondition::_TestGreate( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) > m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) > m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) > m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) > *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	功能：	等于
//@	参数：	
//@	返回值：
//@	注：	
//*/
//bool CAICondition::_TestEqual( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) == m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) == m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) == m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) == *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	功能：	小于等于
//@	参数：	
//@	返回值：
//@	注：	
//*/
//bool CAICondition::_TestLessEqual( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) <= m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) <= m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) <= m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) <= *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	功能：	大于等于
//@	参数：	
//@	返回值：
//@	注：	
//*/
//bool CAICondition::_TestGreateEqual( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) >= m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) >= m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) >= m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) >= *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	功能：	不等于
//@	参数：	
//@	返回值：
//@	注：	
//*/
//bool CAICondition::_TestNotEqual( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return (*m_pProperty) != m_RefData[0].m_iData;
//	case ERT_Dword:
//		return (*m_pProperty) != m_RefData[0].m_dwData;
//	case ERT_Float:
//		return (*m_pProperty) != m_RefData[0].m_fData;
//	case ERT_Property:
//		return (*m_pProperty) != *m_RefData[0].m_pProperty;
//	}
//	return false;
//}
//
///*  
//@	功能：	在范围内
//@	参数：	
//@	返回值：
//@	注：	
//*/
//bool CAICondition::_TestInner( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return m_pProperty->Inner( m_RefData[0].m_iData, m_RefData[1].m_iData );
//	case ERT_Dword:
//		return m_pProperty->Inner( m_RefData[0].m_dwData, m_RefData[1].m_dwData );
//	case ERT_Float:
//		return m_pProperty->Inner( m_RefData[0].m_fData, m_RefData[1].m_fData );
//	case ERT_Property:
//		return m_pProperty->Inner( *m_RefData[0].m_pProperty, *m_RefData[1].m_pProperty );
//	}
//	return false;
//}
//
///*  
//@	功能：	在范围外
//@	参数：	
//@	返回值：
//@	注：	
//*/
//bool CAICondition::_TestOutter( void )
//{ 
//	switch( m_eRefType[0] )
//	{
//	case ERT_Int:
//		return m_pProperty->Inner( m_RefData[0].m_iData, m_RefData[1].m_iData );
//	case ERT_Dword:
//		return m_pProperty->Inner( m_RefData[0].m_dwData, m_RefData[1].m_dwData );
//	case ERT_Float:
//		return m_pProperty->Inner( m_RefData[0].m_fData, m_RefData[1].m_fData );
//	case ERT_Property:
//		return m_pProperty->Inner( *m_RefData[0].m_pProperty, *m_RefData[1].m_pProperty );
//	}
//	return false;
//}
//
//AISYSTEM_SPACE_END