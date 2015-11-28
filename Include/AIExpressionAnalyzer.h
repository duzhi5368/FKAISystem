/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIExpressionAnalyzer.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  定义表达式分析器
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIExpressionDefine.h"

AISYSTEM_SPACE_BEGIN

class CAIBrain;



/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   类名:	CExpressionAnalyzer
+   功能:	分析给定的字符串表示的表达式，返回可执行表达式指针
+   描述:	
-----------------------------------------------------------------
*****************************************************************/
class CExpressionAnalyzer
{
	////////////////////////////////////////////
	//	数据成员
private:
	int m_iOptPriority[EToken_Invalid];			// 操作符优先级表
	std::vector<CExpression*>	m_pAllExpression;	// 所有创建的表达式

	////////////////////////////////////////////
	//	构造/析构
public:
	CExpressionAnalyzer(void);
	~CExpressionAnalyzer(void);

	////////////////////////////////////////////
	//	公共接口
	/*  
	@	功能：	初始化
	@	参数：	
	@	返回值：
	@	注：	
	*/
	void Init( void );

	/*  
	@	功能：	分析表达式字符串，返回表达式
	@	参数：	lpszString:	要分析的表达式字符串
	@	返回值：表达式指针
	@	注：	
	*/
	CExpression *Analyse( const TLexTokens & allTokens, CAIBrain *pBrain, const char *lpszString /*= NULL*/ );

	/*  
	@	功能：	判断一个记号类型是不是一个操作数
	@	参数：	eTokenType:	记号类型
	@	返回值：
	@	注：	包括数字和标识符
	*/
	bool IsOptTarget( EToken eTokenType )
	{
		if( ( eTokenType > EToken_NumericBegin && eTokenType < EToken_NumericEnd )
			|| eTokenType == EToken_Identifier )
			return true;
		return false;
	}

	/*  
	@	功能：	判断一个记号类型是不是一个操作符
	@	参数：	eTokenType:	记号类型
	@	返回值：
	@	注：	操作符包括逻辑、比较、左右括号
	*/
	bool IsOpt( EToken eTokenType )
	{
		if( eTokenType >= EToken_Not && eTokenType <= EToken_GreaterEqual )
			return true;
		if( eTokenType == EToken_BracketOpen || eTokenType == EToken_BracketClose )
			return true;
		if( eTokenType >= EToken_Add && eTokenType <= EToken_Div )
			return true;
		if( eTokenType == EToken_Neg )
			return true;
		return false;
	}

	/*  
	@	功能：	判断一个操作符记号类型是不是一个单目操作符
	@	参数：	eTokenType:	记号类型
	@	返回值：
	@	注：	非，负
	*/
	bool IsSingleOpt( EToken eTokenType )
	{
		if( IsOpt( eTokenType ) && ( eTokenType == EToken_Not || eTokenType == EToken_Neg ) )
			return true;
		return false;
	}

	/*  
	@	功能：	判断一个操作符记号是不是一个双目操作符
	@	参数：	eTokenType:	记号类型
	@	返回值：
	@	注：	除了非以外的所有的操作符都是双目的
	*/
	bool IsCoupleOpt( EToken eTokenType )
	{
		if( IsOpt( eTokenType ) && eTokenType != EToken_Not )
			return true;
		return false;
	}

	bool IsLogicOpt( EToken eTokenType )
	{
		if( eTokenType >= EToken_Not && eTokenType <= EToken_Or )
			return true;
		return false;
	}

	bool IsRelationOpt( EToken eTokenType )
	{
		if( eTokenType >= EToken_Equal && eTokenType <= EToken_GreaterEqual )
			return true;
		return false;
	}

	bool IsArithOpt( EToken eTokenType )
	{
		if( eTokenType >= EToken_Add && eTokenType <= EToken_Div )
			return true;
		if( eTokenType == EToken_Neg )
			return true;
		return false;
	}

	/*  
	@	功能：	构建一个表达式  双目
	@	参数：	Opt:	操作符表达式符号
				left:	左操作数表达式符号
				right:	右操作数表达式符号
	@	返回值：创建的表达式的指针
	@	注：	
	*/
	CExpression *BuildExpression( const CExpToken &Opt, const CExpToken &left, const CExpToken & right, CAIBrain *pBrain );

	/*  
	@	功能：	构建一个表达式	单目
	@	参数：	Opt:	操作符表达式符号
				right:	右操作数表达式符号
	@	返回值：创建的表达式的指针
	@	注：	
	*/
	CExpression *BuildExpression( const CExpToken &Opt, const CExpToken &right, CAIBrain *pBrain );

	/*  
	@	功能：	清除操作
	@	参数：	
	@	返回值：
	@	注：	如果分析失败，可能要清除创建的一些东西
	*/
	void Clear( );

	void EraseExpression( CExpression *pExp );
	
};



AISYSTEM_SPACE_END