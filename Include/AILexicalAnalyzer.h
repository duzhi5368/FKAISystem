/********************************************************************
// FileName: d:\work\FKAISystem\Include\AILexicalAnalyzer.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  定义词法分析器
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AILexicalDefine.h"



AISYSTEM_SPACE_BEGIN


struct CToken
{
	EToken		m_eTokenType;		// 记号类型
	std::string	m_strTokenString;	// 记号字符串
};

typedef std::vector<CToken> TLexTokens;

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CLexicalAnalyzer
+   功能:	词法分析器
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class CLexicalAnalyzer
{
	////////////////////////////////////////////
	//	数据成员
private:
	const char	*m_lpszString;	// 要分析的字符串
	int			m_nStringLen;	// 要分析的字符串的长度
	int			m_nCurCharPos;	// 当前正在分析的字符位置
	CToken		m_curToken;		// 当前分析的记号
	ELexState	m_curState;		// 当前分析状态
	std::map<unsigned int,TLexTokens> m_Tokens;

	////////////////////////////////////////////
	//	构造/析构
public:
	CLexicalAnalyzer(void);
	~CLexicalAnalyzer(void);

	////////////////////////////////////////////
	//	公共接口
public:
	/*  
	@	功能：	初始化词法分析器
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void Init( void );

	/*  
	@	功能：	分析字符串
	@	参数：	lpszString:	要分析的字符串
				vecTokens:	分析结果
	@	返回值：如果分析失败，返回false
	@	注：	
	*/
	bool Analyse( const char * lpszString, TLexTokens & vecTokens );

	/*  
	@	功能：	分析一个记号
	@	参数：	
	@	返回值：如果分析失败，返回false
	@	注：	
	*/
	bool GetNextToken( void );

	bool IsWhiteChar( char ch );
	bool IsNumeric( char ch );
	bool IsCharIdentifier( char ch );
	
};


AISYSTEM_SPACE_END