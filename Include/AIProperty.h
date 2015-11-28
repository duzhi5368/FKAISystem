/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIProperty.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  属性对象类
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	
+   功能:	
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class CProperty
{
	////////////////////////////////////////////
	//	类型定义
public:
	union UData
	{
		int				*m_pInt;			
		float			*m_pFloat;
		bool			*m_pBool;
		unsigned long	*m_pUnsignedLong;
		std::string		*m_pString;
	};

	enum EDataType
	{
		EDT_Int,
		EDT_Float,
		EDT_Bool,
		EDT_UnsignedLong,
		EDT_String,
		EDT_End
	};

	////////////////////////////////////////////
	//	数据成员
private:


	UData			m_Data;		// 数据
	EDataType		m_Type;		// 数据类型
	std::string		m_strName;	// 名字
	unsigned long	m_uiID;		// ID

	////////////////////////////////////////////
	//	构造/析构
public:
	CProperty( void );
	~CProperty( void );

	////////////////////////////////////////////
	//	提供给属性集的接口
public:
	// 设置名字
	void SetName( const std::string	& strName )	{ m_strName = strName; }
	// 访问名字
	const std::string & GetName( void )			{ return m_strName; }
	// 设置ID
	void SetID( unsigned long uiID )			{ m_uiID = uiID; }
	// 访问ID
	unsigned long GetID( void )					{ return m_uiID; }
	// 注册属性
	void Register( int *pInt );
	void Register( float *pFloat );
	void Register( unsigned long *pUnsignedLog );
	void Register( bool *pBool );
	void Register( std::string *pString );

	////////////////////////////////////////////
	//	公共接口 设置和取得属性值
public:
	// 设置值
	bool SetValue( int iValue );
	bool SetValue( float fValue );
	bool SetValue( bool bValue );
	bool SetValue( unsigned long ulValue );
	bool SetValue( const std::string & strVlaue );

	// 访问值
	bool GetValue( int &iValue );
	bool GetValue( float &fValue );
	bool GetValue( bool &bValue );
	bool GetValue( unsigned long &ulValue );
	bool GetValue( std::string &strValue );

	double GetDouble( void );

	EDataType GetType( void )					{ return m_Type; }

	////////////////////////////////////////////
	//	重载运算符
public:


};




AISYSTEM_SPACE_END