/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIPropertySet.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  属性集类
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIProperty.h"
#include "IAIGlobalFunc.h"

//--------------------------------------------------------------------

#pragma warning(disable:4251)

AISYSTEM_SPACE_BEGIN

//--------------------------------------------------------------------

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CPropertySet
+   功能:	属性集
+   描述:	提供保存和访问属性的接口
-----------------------------------------------------------------
*****************************************************************/
class CPropertySet
{
	////////////////////////////////////////////
	//	数据成员
private:
	// 属性字典
	typedef std::map<unsigned long,CProperty> TPropertyDictionary;
	typedef TPropertyDictionary::iterator TPropertyIter;

	TPropertyDictionary	m_Properties;	// 属性字典

	////////////////////////////////////////////
	//	构造/析构
public:
	CPropertySet( void );
	~CPropertySet( void );

	////////////////////////////////////////////
	//	公共接口
public:
	// 查找一个属性
	CProperty *FindProperty( unsigned long ID );
	CProperty *FindProperty( const std::string & strName );

	// 注册属性，返回一个ID
	unsigned long Register( const std::string & strName, int *pValue )				{ return __Register( strName, pValue ); }
	unsigned long Register( const std::string & strName, float *pValue )			{ return __Register( strName, pValue ); }
	unsigned long Register( const std::string & strName, bool *pValue )				{ return __Register( strName, pValue ); }
	unsigned long Register( const std::string & strName, unsigned long *pValue )	{ return __Register( strName, pValue ); }
	unsigned long Register( const std::string & strName, std::string *pValue )		{ return __Register( strName, pValue ); }

	// 设置属性值
	bool SetValue( const std::string & strName, int value )							{ return __SetValue( strName, value );	}
	bool SetValue( const std::string & strName, float value )						{ return __SetValue( strName, value );	}
	bool SetValue( const std::string & strName, bool value )						{ return __SetValue( strName, value );	}
	bool SetValue( const std::string & strName, unsigned long value )				{ return __SetValue( strName, value );	}
	bool SetValue( const std::string & strName, const std::string & value )			{ return __SetValue( strName, value );	}

	bool SetValue( unsigned long ulID, int value )									{ return __SetValue( ulID, value );		}
	bool SetValue( unsigned long ulID, float value )								{ return __SetValue( ulID, value );		}
	bool SetValue( unsigned long ulID, bool value )									{ return __SetValue( ulID, value );		}
	bool SetValue( unsigned long ulID, unsigned long value )						{ return __SetValue( ulID, value );		}
	bool SetValue( unsigned long ulID, const std::string & value )					{ return __SetValue( ulID, value );		}

	// 访问取属性值
	bool GetValue( const std::string & strName, int & value )						{ return __GetValue( strName, value );	}
	bool GetValue( const std::string & strName, float & value )						{ return __GetValue( strName, value );	}
	bool GetValue( const std::string & strName, bool & value )						{ return __GetValue( strName, value );	}
	bool GetValue( const std::string & strName, unsigned long & value )				{ return __GetValue( strName, value );	}
	bool GetValue( const std::string & strName, std::string & value )				{ return __GetValue( strName, value );	}

	bool GetValue( unsigned long ulID, int & value )								{ return __GetValue( ulID, value );		}
	bool GetValue( unsigned long ulID, float & value )								{ return __GetValue( ulID, value );		}
	bool GetValue( unsigned long ulID, bool & value )								{ return __GetValue( ulID, value );		}
	bool GetValue( unsigned long ulID, unsigned long & value )						{ return __GetValue( ulID, value );		}
	bool GetValue( unsigned long ulID, std::string & value )						{ return __GetValue( ulID, value );		}


	////////////////////////////////////////////
	//	私有接口
private:
	/*  
	@	功能：	生成一个属性ID
	@	参数：	
	@	返回值：属性ID
	@	注：	
	*/
	unsigned long __GenerateID( const char *lpszStr );

	/*  
	@	功能：	注册一个整数类型属性
	@	参数：	strName:	属性的名字
				pValue:		属性指针
	@	返回值：属性ID，0表示注册失败
	@	注：	模板方法
	*/
	template<typename T>
	inline unsigned long __Register( const std::string & strName, T *pValue );

	/*  
	@	功能：	根据名字设置属性的值
	@	参数：	strName:	属性名字
				value:		值
	@	返回值：是否成功
	@	注：	模板方法
	*/
	template<typename T>
	inline bool __SetValue( const std::string & strName, T value );

	/*  
	@	功能：	根据ID设置属性的值
	@	参数：	ID:		属性的ID
				value:	值
	@	返回值：是否成功
	@	注：	模板方法
	*/
	template<typename T>
	inline bool __SetValue( unsigned long uiID, T value );

	/*  
	@	功能：	根据名字访问属性的值
	@	参数：	strName:	属性名字
				value:		值
	@	返回值：是否成功
	@	注：	模板方法
	*/
	template<typename T>
	inline bool __GetValue( const std::string & strName, T & value );

	/*  
	@	功能：	根据ID设置访问属性的值
	@	参数：	ID:		属性的ID
				value:	值
	@	返回值：是否成功
	@	注：	模板方法
	*/
	template<typename T>
	inline bool __GetValue( unsigned long uiID, T & value );

};



/*  
@	功能：	注册一个整数类型属性
@	参数：	strName:	属性的名字
			pValue:		属性指针
@	返回值：属性ID，0表示注册失败
@	注：	模板方法
*/
template< typename T >
inline unsigned long CPropertySet::__Register(const std::string &strName, T* pValue)
{
	unsigned long ID = __GenerateID( strName.c_str() );

	// 名字不能重复
	TPropertyIter iter = m_Properties.find( ID );
	if( iter != m_Properties.end() )
		return 0;

	static CProperty NullProperty;
	std::pair<TPropertyIter,bool> res = m_Properties.insert( std::make_pair( ID, NullProperty ) );
	if( res.second == false )
	{
		OutPutErrorMsg( "向属性字典插入新属性失败！%s", strName.c_str() );
		return 0;
	}
	CProperty & NewProperty = ( res.first )->second;
	NewProperty.SetName( strName );
	NewProperty.SetID( ID );
	NewProperty.Register( pValue );
	return NewProperty.GetID();
}

/*  
@	功能：	根据名字设置属性的值
@	参数：	strName:	属性名字
			value:		值
@	返回值：是否成功
@	注：	模板方法
*/
template< typename T >
inline bool CPropertySet::__SetValue( const std::string & strName, T value )
{
	if( m_Properties.size() == 0 )
		return false;

	unsigned long ID = __GenerateID( strName.c_str() );
	TPropertyIter iter = m_Properties.find( ID );
	if( iter == m_Properties.end() )
		return false;
	iter->second.SetValue( value );
	return true;
}

/*  
@	功能：	根据ID设置属性的值
@	参数：	ID:		属性的ID
			value:	值
@	返回值：是否成功
@	注：	模板方法
*/
template< typename T >
inline bool CPropertySet::__SetValue( unsigned long ID, T value )
{
	if( m_Properties.size() == 0 )
		return false;

	TPropertyIter iter = m_Properties.find( ID );
	if( iter == m_Properties.end() )
		return false;
	iter->second.SetValue( value );
	return true;
}

/*  
@	功能：	根据名字访问属性的值
@	参数：	strName:	属性名字
			value:		值
@	返回值：是否成功
@	注：	模板方法
*/
template< typename T >
inline bool CPropertySet::__GetValue( const std::string & strName, T & value )
{
	if( m_Properties.size() == 0 )
		return false;

	unsigned long ID = __GenerateID( strName.c_str() );
	TPropertyIter iter = m_Properties.find( ID );
	if( iter == m_Properties.end() )
		return false;
	return iter->second.GetValue( value );
}

/*  
@	功能：	根据ID设置访问属性的值
@	参数：	ID:		属性的ID
			value:	值
@	返回值：是否成功
@	注：	模板方法
*/
template< typename T >
inline bool CPropertySet::__GetValue( unsigned long ID, T & value )
{
	if( m_Properties.size() == 0 )
		return false;

	TPropertyIter iter = m_Properties.find( ID );
	if( iter == m_Properties.end() )
		return false;
	return iter->second.GetValue( value );
}



AISYSTEM_SPACE_END

#pragma warning(default:4251)