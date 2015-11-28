/********************************************************************
// FileName: d:\work\FKAISystem\Include\AILexicalDefine.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  词法分析预定义的常量及函数、类型
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


/****************************************************************
+	ENUM
-----------------------------------------------------------------	
+   描述:	定义所有的词法分析状态
-----------------------------------------------------------------
*****************************************************************/
enum ELexState
{
	ELexState_Start = 0,				// 词法分析开始状态

	//--数值分析状态
	ELexState_Int,						// 整型值状态
	ELexState_Float,					// 浮点值状态

	//--标识符分析状态
	ELexState_Identifier,				// 标识符状态

	//--分隔符分析状态
	ELexState_Delimiter,				// 分隔符状态

	//--字符串分析状态
	ELexState_String,					// 字符串分析状态
	ELexState_StringEscape,				// 字符串转义处理状态
	ELexState_StringEnd,				// 字符串分析完成状态

	//--运算符分析状态
	ELexState_Operator,					// 运算符分析状态

	ELexState_End
};




/****************************************************************
+	ENUM
-----------------------------------------------------------------	
+   描述:	定义所有的记号类型
-----------------------------------------------------------------
*****************************************************************/
enum EToken
{
	EToken_Complete = 0,					// 解析的字符流结束

	//--数据类型
	EToken_NumericBegin,					// 开始定义数值数据类型
	EToken_Int,								// 整型类型
	EToken_Float,							// 浮点类型
	EToken_UnsignedInt,						// 无符号整数型
	EToken_Long,							// 长整型
	EToken_UnsignedLong,					// 无符号长整型
	EToken_NumericEnd,						// 结束定义数值数据类型

	//--标识符类型
	EToken_Identifier,						// 标识符类型

	//--关键字
	EToken_KeywordBegin,					// 关键字定义开始
	EToken_If,								// if
	EToken_Else,							// else
	EToken_Switch,							// switch
	EToken_Case,							// case
	EToken_While,							// while
	EToken_Do,								// do
	EToken_Continue,						// continue
	EToken_Break,							// break
	EToken_True,							// true
	EToken_False,							// false
	EToken_Return,							// return
	EToken_KeywordEnd,						// 关键字定义结束

	//--分隔符类型
	EToken_DelimiterBegin,					// 开始定义分隔符
	EToken_BracketOpen,						// 左括号分隔符类型
	EToken_BracketClose,					// 右括号分隔符类型
	EToken_DelimiterEnd,					// 结束定义分隔符

	//--字符串类型
	EToken_String,							// 字符串类型

	EToken_ArithmeticBegin,					//	运算符定义开始
	//--算术运算符
	EToken_Add,								// + 
	EToken_Sub,								// - 
	EToken_Mul,								// * 
	EToken_Div,								// / 
	EToken_Mod,								// % 
	EToken_Exp,								// ^ 
	EToken_Inc,								// ++
	EToken_Dec,								// --
	EToken_AssignAdd,						// +=
	EToken_AssignSub,						// -=
	EToken_AssignMul,						// *=
	EToken_AssignDiv,						// /=
	EToken_AssignMod,						// %=
	EToken_AssignExp,						// ^=
	EToken_Neg,								// 负

	//--位运算

	//--逻辑运算符
	EToken_Not,								// 逻辑非
	EToken_And,								// 逻辑与
	EToken_Or,								// 逻辑或
	
	//--关系运算符
	EToken_Equal,							// 等于
	EToken_NotEqual,						// 不等于
	EToken_Less,							// 小于
	EToken_Greater,							// 大于
	EToken_LessEqual,						// 小于等于
	EToken_GreaterEqual,					// 大于等于

	EToken_ArithmeticEnd,					// 运算符定义结束

	EToken_Invalid
};


/****************************************************************
+	STRUCT
-----------------------------------------------------------------
+   名称:	STokenType
+   功能:	记号类型
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
struct STokenType
{
	char			m_szToken[32];	// 记号字符串
	EToken			m_eTokenType;	// 记号类型
	unsigned long	m_ulIdentifier;	// 标识符
};




/****************************************************************
+	DEFINE
-----------------------------------------------------------------	
+   描述:	定义所有的分隔符
-----------------------------------------------------------------
*****************************************************************/
#define NUM_DELIMITER EToken_DelimiterEnd - EToken_DelimiterBegin - 1	// 定界符的数量
extern STokenType G_Delimiters[NUM_DELIMITER];							// 定界符表
/*  
@	功能：	判断字符是不是一个定界符
@	参数：	ch:	要判断的字符
@	返回值：如果是分隔符返回true
@	注：	
*/
EToken GetDelimiterType( char ch );



/****************************************************************
+	DEFINE
-----------------------------------------------------------------	
+   描述:	定义关键字表
-----------------------------------------------------------------
*****************************************************************/
#define NUM_KEYWORDS	EToken_KeywordEnd - EToken_KeywordBegin - 1		// 关键字的数量
extern STokenType G_Keywords[NUM_KEYWORDS];								// 所有的关键字

/*  
@	功能：	初始化关键字表
@	参数：	
@	返回值：
@	注：	
*/
bool InitKeywordsTable( void );

/*  
@	功能：	查询关键字类型
@	参数：	lpszStr:	要查询的字符
@	返回值：如果字符串是关键字，返回true
@	注：	
*/
EToken GetKeywordType( const char *lpszStr );



/****************************************************************
+	DEFINE
-----------------------------------------------------------------	
+   描述:	定义运算符
-----------------------------------------------------------------
*****************************************************************/
#define NUM_OPT	EToken_ArithmeticEnd - EToken_ArithmeticBegin - 1		// 运算符的数量
extern STokenType G_OptTokensTable[NUM_OPT];							// 运算符表

/*  
@	功能：	初始化运算符表
@	参数：	
@	返回值：
@	注：	
*/
bool InitOptTokensTable( void );

/*  
@	功能：	取得当前的记号类型
@	参数：	lpszToken:	字符串
@	返回值：如果是一个运算符，返回类型，否则返回 EToken_Invalid
@	注：	
*/
EToken GetOptTokenType( const char *lpszToken );

/*  
@	功能：	判断是不是一个运算符字符
@	参数：	ch:	字符
@	返回值：如果字符能作为运算符的开头，则返回true，否则返回false
@	注：	
*/
bool IsOptChar( char ch );


/*  
@	功能：	判断一个数值的类型
@	参数：	
@	返回值：
@	注：	
*/
EToken GetIntType( const char *lpszInt );

/*  
@	功能：	判断一个数据的类型
@	参数：	
@	返回值：
@	注：	
*/
template <typename T>
bool IsType( double dValue, T value );



AISYSTEM_SPACE_END