#include "../PreInclude.h"
#include "../Include/AILexicalAnalyzer.h"
#include "../Include/AICrc32.h"


AISYSTEM_SPACE_BEGIN

CLexicalAnalyzer::CLexicalAnalyzer(void)
{
}

CLexicalAnalyzer::~CLexicalAnalyzer(void)
{
}

/*  
@	功能：	初始化词法分析器
@	参数：	
@	返回值：
@	注：	
*/
void CLexicalAnalyzer::Init( void )
{
	InitKeywordsTable();
	InitOptTokensTable();
}

/*  
@	功能：	分析字符串
@	参数：	lpszString:	要分析的字符串
			vecTokens:	分析结果
@	返回值：如果分析失败，返回false
@	注：	
*/
bool CLexicalAnalyzer::Analyse( const char * lpszString, TLexTokens & vecTokens )
{
	static Crc32 crcGen;
	unsigned int crc = crcGen.GetCRC( lpszString );
	std::map<unsigned int,TLexTokens>::iterator iter = m_Tokens.find( crc );
	if( iter != m_Tokens.end() )
	{
		vecTokens = iter->second;
		return true;
	}

	vecTokens.clear();
	if( NULL == lpszString )
		return false;

	m_nStringLen	= (int)strlen( lpszString );
	if( m_nStringLen == 0 )
		return true;

	char * pszStr = new char[m_nStringLen+1];
	memcpy( pszStr, lpszString, m_nStringLen );
	pszStr[m_nStringLen] = '\0';

	m_nCurCharPos	= 0;
	m_lpszString = lpszString;
	
	while( true )
	{
		m_curState	= ELexState_Start;
		if( ! GetNextToken() )
		{
			vecTokens.clear();
			return false;
		}

		if( m_curToken.m_eTokenType == EToken_Complete )
			break;

		vecTokens.push_back( m_curToken );
		m_curToken.m_eTokenType = EToken_Invalid;
	}
	m_Tokens.insert( make_pair( crc, vecTokens ) );
	return true;
}

/*  
@	功能：	分析一个记号
@	参数：	
@	返回值：如果分析失败，返回false
@	注：	
*/
bool CLexicalAnalyzer::GetNextToken( void )
{
	if( m_nCurCharPos >= m_nStringLen )
	{
		m_curToken.m_eTokenType = EToken_Complete;
		return true;
	}
	bool bAddToLex = false;	// 当前符号是否加入记号符号中
	bool bDone = false;		// 是否完成当前记号的解析
	char cCurChar = 0;		// 当前字符
	static char szBuffer[1024];
	static char szOpt[8];
	int w = 0;
	int optW = 0;
	EToken	curTokenType;
	memset( szBuffer, 0, sizeof( szBuffer ) );
	memset( szOpt, 0, sizeof( szOpt ) );

	while( true )
	{
		cCurChar = m_lpszString[m_nCurCharPos++];
		if( cCurChar == '\0' )
			break;
		bAddToLex = true;

		switch( m_curState )
		{
			//--------开始状态
		case ELexState_Start:
			{
				// 略过前导空格
				if( IsWhiteChar( cCurChar) )
				{
					bAddToLex = false;
				}
				// 是否是一个整数
				else if( IsNumeric( cCurChar ) )
				{
					m_curState = ELexState_Int;
				}
				// 是否是一个浮点数
				else if( cCurChar == '.' )
				{
					m_curState = ELexState_Float;
				}
				// 是否是标识符
				else if( IsCharIdentifier( cCurChar ) )
				{
					m_curState = ELexState_Identifier;
				}
				// 分隔符
				else if( GetDelimiterType( cCurChar ) != EToken_Invalid )
				{
					m_curState = ELexState_Delimiter;
					curTokenType = GetDelimiterType( cCurChar );
					bDone = true;
				}
				// 开始字符串解析
				else if( cCurChar == '"' )
				{
					m_curState = ELexState_String;
					bAddToLex = false;
				}
				// 运算符
				else if( IsOptChar( cCurChar ) )
				{
					m_curState = ELexState_Operator;
					szOpt[optW++] = cCurChar;
				}
				// 非法字符，解析失败
				else
				{
					return false;
				}
			}
			break;

			//--------整数状态
		case ELexState_Int:
			{
				// 整数保持当前状态
				if( IsNumeric( cCurChar ) )
					m_curState = ELexState_Int;
				// 如果是小数点，则转到浮点数
				else if( cCurChar == '.' )
					m_curState = ELexState_Float;
				// 如果是空格，完成识别
				else if( IsWhiteChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
				}
				// 如果是运算符，完成识别
				else if( IsOptChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
					-- m_nCurCharPos;
				}
				// 其它都是非法的
				else
					return false;
			}
			break;

			//--------浮点数状态
		case ELexState_Float:
			{
				if( IsNumeric( cCurChar ) )
					m_curState = ELexState_Float;
				// 如果是空格，完成识别
				else if( IsWhiteChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
				}
				// 如果是运算符，完成识别
				else if( IsOptChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
					-- m_nCurCharPos;
				}
				// 其它都是非法的
				else
					return false;
			}
			break;

			//--------标识符状态
		case ELexState_Identifier:
			{
				// 如果是标识符字符，则保持当前状态
				if( IsCharIdentifier( cCurChar ) )
				{
					m_curState = ELexState_Identifier;
				}
				// 如果是空格，完成识别
				else if( IsWhiteChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
				}
				// 如果是运算符，完成识别
				else if( IsOptChar( cCurChar ) )
				{
					bAddToLex = false;
					bDone = true;
					-- m_nCurCharPos;
				}
				// 其它都是非法的
				else
					return false;
			}
			break;

			//---------字符串
		case ELexState_String:
			{
				// 如果是 " 字符串识别完成
				if( cCurChar == '"' )
				{
					bAddToLex = false;
					m_curState = ELexState_StringEnd;
				}
				// 如果是转义字符，则转到转义字符状态
				else if( cCurChar == '\\' )
				{
					bAddToLex = false;
					m_curState = ELexState_StringEscape;
				}
				// 其它字符全部添加到字符串中
			}
			break;

			//---------转义字符
		case ELexState_StringEscape:
			{
				// TODO 转换当前字符
				m_curState = ELexState_String;
			}
			break;

			//---------完成字符串识别
		case ELexState_StringEnd:
			{
				bAddToLex = false;
				bDone = true;
			}
			break;

			//---------运算符
		case ELexState_Operator:
			{
				szOpt[optW++] = cCurChar;
				if( GetOptTokenType( szOpt ) == EToken_Invalid )
				{
					bAddToLex = false;
					bDone = true;
					-- m_nCurCharPos;
				}
			}
			break;


		}	// end switch

		if( bAddToLex )
			szBuffer[w++] = cCurChar;
		if( bDone )
			break;

	}
	szBuffer[w++] = '\0';

	// 确定记号类型
	switch( m_curState )
	{
	case ELexState_Int:
		curTokenType = GetIntType( szBuffer );
		break;

	case ELexState_Float:
		curTokenType = EToken_Float;
		break;

	case ELexState_Identifier:
		curTokenType = GetKeywordType( szBuffer );
		break;

	case ELexState_Delimiter:
		curTokenType = GetDelimiterType( szBuffer[0] );
		break;

	case ELexState_Operator:
		curTokenType = GetOptTokenType( szBuffer );
		break;

	case ELexState_Start:
	default:
		curTokenType = EToken_Complete;
		break;
	}
	m_curToken.m_strTokenString = szBuffer;
	m_curToken.m_eTokenType		= curTokenType;

	return true;
}

bool CLexicalAnalyzer::IsWhiteChar( char ch )
{
	if( ch == ' ' || ch == '\t' || ch == '\n' )
		return true;
	return false;
}

bool CLexicalAnalyzer::IsNumeric( char ch )
{
	if( ch >= '0' && ch <= '9' )
		return true;
	return false;
}

bool CLexicalAnalyzer::IsCharIdentifier(char ch)
{
	if( ( ch >= '0' && ch <= '9' ) ||
		( ch >= 'A' && ch <= 'Z' ) ||
		( ch >= 'a' && ch <= 'z' ) ||
		( ch == '_' ) )
		return true;
	return false;
}

AISYSTEM_SPACE_END