/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIExpressionDefine.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  定义表达式解析用到的一些类型
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AILexicalAnalyzer.h"


AISYSTEM_SPACE_BEGIN

class CExpression;
class CProperty;


/****************************************************************
+	STRUCT
-----------------------------------------------------------------
+   名称:	CExpToken
+   功能:	一个表达式符号
+   描述:	进行表达式分析时，将用这种数据类型作为分析对象
-----------------------------------------------------------------
*****************************************************************/
struct CExpToken
{
	bool		m_bIsExp;		// 是否是一个表达式
	CToken		m_Token;		// 记号单词。
	CExpression	*m_pExp;		// 表达式
};


/****************************************************************
+	ENUM
-----------------------------------------------------------------
+   名称:	EDataType
+   功能:	描述表达式操作数类型的枚举
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
enum EDataType
{
	EDataType_Float,		// 浮点类型
	EDataType_Long,			// 长整数型
	EDataType_UnsignedLong,	// 无符号长整数型
	EDataType_Property,		// 属性，标识符
	EDataType_Expression,	// 表达式
	EDataType_End
};

/****************************************************************
+	ENUM
-----------------------------------------------------------------
+   名称:	EOptType
+   功能:	描述表达式操作类型的枚举
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
enum EOptType
{
	EOptType_Not,			// !
	EOptType_Equal,			// ==
	EOptType_NotEqual,		// !=
	EOptType_Less,			// <
	EOptType_Greater,		// >
	EOptType_LessEqual,		// <=
	EOptType_GreaterEqual,	// >=
	EOptType_And,			// &&
	EOptType_Or,			// ||
	EOptType_Add,			// +
	EOptType_Sub,			// -
	EOptType_Mul,			// *
	EOptType_Div,			// /
	EOptType_Neg,			// 负
	EOptType_End
};


/****************************************************************
+	STRUCT
-----------------------------------------------------------------
+   名称:	SData
+   功能:	存储一个表达式的操作数数据
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class SData
{
	////////////////////////////////////////////
	//	数据成员
public:
	EDataType	m_eType;				// 操作数类型
	union UData							// 操作数共用体类型
	{
		float			m_fData;		// 浮点数据
		long			m_lData;		// 长整数数据
		unsigned long	m_ulData;		// 无符号长整数数据
		CProperty		*m_pProperty;	// 属性
		CExpression		*m_pExpression;	// 表达式
	};
	UData		m_Data;					// 操作数


	////////////////////////////////////////////
	//	构造/析构
public:
	SData( void )
	{
		m_eType = EDataType_End;
		m_Data.m_ulData = 0;
	}
	~SData( void ){};
	void Release( void );

	////////////////////////////////////////////
	//	公共方法
public:

	bool CalculateLogic( void );
	double CalculateNumeric( void );

	/*  
	@	功能：	重载逻辑运算符
	@	参数：	
	@	返回值：
	@	注：	
	*/
	bool operator !  ( );
	bool operator && ( const SData &data );
	bool operator || ( const SData &data );

	/*  
	@	功能：	重载比较运算符
	@	参数：	
	@	返回值：
	@	注：	
	*/
	bool operator == ( const SData &data );
	bool operator != ( const SData &data );
	bool operator >  ( const SData &data );
	bool operator >= ( const SData &data );
	bool operator <  ( const SData &data );
	bool operator <= ( const SData &data );

	/*  
	@	功能：	重载算术运算符
	@	参数：	
	@	返回值：
	@	注：	
	*/
	double operator + ( const SData &data );
	double operator - ( const SData &data );
	double operator * ( const SData &data );
	double operator / ( const SData &data );
	double operator - ();

};


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CExpression
+   功能:	表达式，可执行单位
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class CExpression
{
	////////////////////////////////////////////
	//	友元声明
	friend class CExpressionAnalyzer;

	////////////////////////////////////////////
	//	数据成员
private:
	SData		m_LData;	// 左操作数
	SData		m_RData;	// 右操作数
	EOptType	m_eOptType;	// 操作类型
	std::string m_strExp;

public:
	CExpression(void);
	~CExpression(void);
	void Release( void );

	////////////////////////////////////////////
	//	公共接口
public:
	/*  
	@	功能：	执行表达式
	@	参数：	
	@	返回值：
	@	注：	
	*/
	double operator ()();
	double Execute( void )			{ return (*this)(); }

protected:
	typedef double(CExpression::*CompFunc)(void);
	static CompFunc	s_pCompFuncs[EOptType_End];
	static bool s_CompFuncInited;

	double Not( void )			{	return !m_RData;	}
	double And( void )			{	return m_LData && m_RData;	}
	double Or( void )			{	return m_LData || m_RData;	}
	double Equal( void )		{	return m_LData == m_RData;	}
	double NotEqual( void )		{	return m_LData != m_RData;	}
	double Less( void )			{	return m_LData < m_RData;	}
	double LeeeEqual( void )	{	return m_LData <= m_RData;	}
	double Greater( void )		{	return m_LData > m_RData;	}
	double GreaterEqual( void )	{	return m_LData >= m_RData;	}
	double Add( void )			{	return m_LData + m_RData;	}
	double Sub( void )			{	return m_LData - m_RData;	}
	double Mul( void )			{	return m_LData * m_RData;	}
	double Div( void )			{	return m_LData / m_RData;	}
	double Neg( void )			{	return - m_RData;	}
};

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CStack
+   功能:	实现一人栈模板
+   描述:	用双端队列实现
-----------------------------------------------------------------
*****************************************************************/
template< typename T >
class CStack
{
private:
	std::deque<T>	m_Stack;	// 双端队列
public:
	/*  
	@	功能：	将一个元素入栈
	@	参数：	t:	要入栈的元素
	@	返回值：
	@	注：	
	*/
	void Push( const T & t )
	{
		m_Stack.push_back( t );
	}

	/*  
	@	功能：	出栈一个元素
	@	参数：	
	@	返回值：出栈的元素
	@	注：	
	*/
	const T & Pop( void )
	{
		static T t;
		if( m_Stack.size() != 0 )
		{
			deque<T>::reverse_iterator iter = m_Stack.rbegin();
			t = *iter;
			m_Stack.pop_back();
		}
		return t;
	}

	/*  
	@	功能：	查询栈顶元素
	@	参数：	
	@	返回值：栈顶元素
	@	注：	
	*/
	const T & Top( void )
	{
		static T t;
		deque<T>::reverse_iterator iter = m_Stack.rbegin();
		t = *iter;
		return t;
	}

	/*  
	@	功能：	判断栈是否为空
	@	参数：	
	@	返回值：
	@	注：	
	*/
	bool Empty( void )
	{
		return ( (int)m_Stack.size() == 0 );
	}

	size_t Size( void )
	{
		return m_Stack.size();
	}

};


AISYSTEM_SPACE_END