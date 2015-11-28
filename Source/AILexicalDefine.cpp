#include "../PreInclude.h"
#include "../Include/AILexicalDefine.h"
#include "../Include/AICrc32.h"


AISYSTEM_SPACE_BEGIN

// 定义所有的定界符
STokenType G_Delimiters[NUM_DELIMITER] =	
{
	"(",	EToken_BracketOpen,		0,
	")",	EToken_BracketClose,	0,
};

/*  
@	功能：	判断字符是不是一个定界符
@	参数：	ch:	要判断的字符
@	返回值：如果是分隔符返回true
@	注：	
*/
EToken GetDelimiterType( char ch )
{
	for( int i = 0; i < NUM_DELIMITER; ++ i )
	{
		if( G_Delimiters[i].m_szToken[0] == ch )
			return G_Delimiters[i].m_eTokenType;
	}
	return EToken_Invalid;
}



// 所有的关键字
STokenType G_Keywords[NUM_KEYWORDS] =
{
	"if\0",			EToken_If,			0,
	"else\0",		EToken_Else,		0,
	"switch\0",		EToken_Switch,		0,
	"case\0",		EToken_Case,		0,
	"while\0",		EToken_While,		0,
	"do\0",			EToken_Do,			0,
	"continue\0",	EToken_Continue,	0,
	"break\0",		EToken_Break,		0,
	"true\0",		EToken_True,		0,
	"false\0",		EToken_False,		0,
	"return\0",		EToken_Return,		0,
};

/*  
@	功能：	初始化关键字表
@	参数：	
@	返回值：
@	注：	
*/
bool InitKeywordsTable( void )
{
	static Crc32 theCrc32;
	for( int i = 0; i < NUM_KEYWORDS; ++ i )
	{
		STokenType &curTokenType = G_Keywords[i];
		curTokenType.m_ulIdentifier = theCrc32.GetCRC( curTokenType.m_szToken );
	}
	return true;
}

/*  
@	功能：	查询关键字类型
@	参数：	lpszStr:	要查询的字符
@	返回值：如果字符串是关键字，返回true
@	注：	
*/
EToken GetKeywordType( const char *lpszStr )
{
	static Crc32 theCrc32;
	unsigned long ul = theCrc32.GetCRC( lpszStr );
	for( int i = 0; i < NUM_KEYWORDS; ++ i )
	{
		if( G_Keywords[i].m_ulIdentifier == ul )
			return G_Keywords[i].m_eTokenType;
	}
	return EToken_Identifier;
}


// 运算符表
STokenType G_OptTokensTable[NUM_OPT] = 
{
	"+\0",	EToken_Add,			0,
	"-\0",	EToken_Sub,			0,
	"*\0",	EToken_Mul,			0,
	"/\0",	EToken_Div,			0,
	"%\0",	EToken_Mod,			0,
	"^\0",	EToken_Exp,			0,
	"++\0",	EToken_Inc,			0,
	"--\0",	EToken_Dec,			0,
	"+=\0",	EToken_AssignAdd,	0,
	"-=\0",	EToken_AssignSub,	0,
	"*=\0",	EToken_AssignMul,	0,
	"/=\0",	EToken_AssignDiv,	0,
	"%=\0",	EToken_AssignMod,	0,
	"^=\0",	EToken_AssignExp,	0,
	"-\0",	EToken_Neg,			0,
	"!\0",	EToken_Not,			0,
	"$\0",	EToken_And,			0,
	"||\0",	EToken_Or,			0,
	"==\0",	EToken_Equal,		0,
	"!=\0",	EToken_NotEqual,	0,
	"@\0",	EToken_Less,		0,		// < 小于，因为XML不能将“<”当作标识符，所以用这个代替
	">\0",	EToken_Greater,		0,
	"<=\0",	EToken_LessEqual,	0,
	">=\0",	EToken_GreaterEqual,0,
};


/*  
@	功能：	初始化运算符表
@	参数：	
@	返回值：
@	注：	
*/
bool InitOptTokensTable( void )
{
	int len = 0;
	for( int i = 0; i < NUM_OPT; ++ i )
	{
		STokenType &curOpType = G_OptTokensTable[i];
		len = (int)strlen( curOpType.m_szToken );
		if( len == 1 )
		{
			curOpType.m_ulIdentifier = curOpType.m_szToken[0];
		}
		else if( len == 2 )
		{
			curOpType.m_ulIdentifier = curOpType.m_szToken[0];
			curOpType.m_ulIdentifier += ( curOpType.m_szToken[1] ) << 8;
		}
		else if( len == 3 )
		{
			curOpType.m_ulIdentifier = curOpType.m_szToken[0];
			curOpType.m_ulIdentifier += ( curOpType.m_szToken[1] ) << 8;
			curOpType.m_ulIdentifier += ( curOpType.m_szToken[2] ) << 16;
		}
		else
		{
			return false;
		}
	}
	return true;
}

/*  
@	功能：	取得当前的记号类型
@	参数：	lpszToken:	字符串
@	返回值：如果是一个运算符，返回类型，否则返回 EToken_Invalid
@	注：	
*/
EToken GetOptTokenType( const char *lpszToken )
{
	int len = (int)strlen( lpszToken );
	unsigned long identifier = 0;
	if( len == 1 )
	{
		identifier = lpszToken[0];
	}
	else if( len == 2 )
	{
		identifier = lpszToken[0];
		identifier += ( lpszToken[1] ) << 8;
	}
	else if( len == 3 )
	{
		identifier = lpszToken[0];
		identifier += ( lpszToken[1] ) << 8;
		identifier += ( lpszToken[1] ) << 16;
	}
	else
	{
		return EToken_Invalid;
	}

	for( int i = 0; i < NUM_OPT; ++ i )
	{
		STokenType &curOpType = G_OptTokensTable[i];
		if( curOpType.m_ulIdentifier == identifier )
			return curOpType.m_eTokenType;
	}
	return EToken_Invalid;
}

/*  
@	功能：	判断是不是一个运算符字符
@	参数：	ch:	字符
@	返回值：如果字符能作为运算符的开头，则返回true，否则返回false
@	注：	
*/
bool IsOptChar( char ch )
{
	for( int i = 0; i < NUM_OPT; ++ i )
	{
		STokenType &curOpType = G_OptTokensTable[i];
		if( curOpType.m_szToken[0] == ch )
			return true;
	}
	if( ch == '(' || ch == ')' )
		return true;
	return false;
}


/*  
@	功能：	判断一个数值的类型
@	参数：	
@	返回值：
@	注：	
*/
EToken GetIntType( const char *lpszInt )
{
	double dValue = atof( lpszInt );
	double dTemp = .0;

	// 整数
	if( IsType( dValue, (int)dValue ) )
		return EToken_Int;

	// 无符号整数
	if( IsType( dValue, (unsigned int)dValue ) )
		return EToken_UnsignedInt;

	// 长整数
	if( IsType( dValue, (long)dValue ) )
		return EToken_Long;

	// 无符号长整数
	if( IsType( dValue, (unsigned long)dValue ) )
		return EToken_UnsignedLong;

	return EToken_Long;
}


/*  
@	功能：	判断一个数据的类型
@	参数：	
@	返回值：
@	注：	
*/
template <typename T>
bool IsType( double dValue, T value )
{
	double dTemp;
	dTemp = (double)value;
	if( dTemp == dValue )
		return true;
	return false;
}


AISYSTEM_SPACE_END