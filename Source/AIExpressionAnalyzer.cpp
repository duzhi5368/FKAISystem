#include "../PreInclude.h"
#include "../Include/AIExpressionAnalyzer.h"
#include "../Include/AIBrain.h"
#include "../Include/IAIGlobalFunc.h"


using namespace std;


AISYSTEM_SPACE_BEGIN

CExpressionAnalyzer::CExpressionAnalyzer(void)
{
}

CExpressionAnalyzer::~CExpressionAnalyzer(void)
{
}


/*  
@	功能：	初始化
@	参数：	
@	返回值：
@	注：	
*/
void CExpressionAnalyzer::Init( void )
{
	// 初始化操作符优先级
	memset( m_iOptPriority, 9999, sizeof( m_iOptPriority ) );
	m_iOptPriority[EToken_Not]			= 1;
	m_iOptPriority[EToken_Neg]			= 1;
	m_iOptPriority[EToken_Mul]			= 2;
	m_iOptPriority[EToken_Div]			= 2;
	m_iOptPriority[EToken_Add]			= 3;
	m_iOptPriority[EToken_Sub]			= 4;
	m_iOptPriority[EToken_Equal]		= 5;
	m_iOptPriority[EToken_NotEqual]		= 5;
	m_iOptPriority[EToken_Less]			= 5;
	m_iOptPriority[EToken_Greater]		= 5;
	m_iOptPriority[EToken_LessEqual]	= 5;
	m_iOptPriority[EToken_GreaterEqual]	= 5;
	m_iOptPriority[EToken_And]			= 6;
	m_iOptPriority[EToken_Or]			= 7;
	m_iOptPriority[EToken_BracketClose] = 8;
	m_iOptPriority[EToken_BracketOpen]	= 8;
}

/*  
@	功能：	分析表达式字符串，返回表达式
@	参数：	lpszString:	要分析的表达式字符串
@	返回值：表达式指针
@	注：	
*/
CExpression *CExpressionAnalyzer::Analyse( const TLexTokens & allTokens, CAIBrain *pBrain, const char *lpszString /*= NULL*/ )
{
	int nTokens = (int)allTokens.size();

	// 填充未分析栈，并检查括号匹配
	int nBracket = 0;
	CStack<CExpToken> ExpTokens;
	for( int i = nTokens-1; i >= 0; -- i )
	{
		static CExpToken token;
		token.m_bIsExp = false;
		token.m_pExp = NULL;
		token.m_Token = allTokens[i];

		if( token.m_Token.m_eTokenType == EToken_BracketOpen )
			++ nBracket;
		if( token.m_Token.m_eTokenType == EToken_BracketClose )
			-- nBracket;

		ExpTokens.Push( token );
	}
	// 括号不匹配
	if( nBracket != 0 )
	{
		OutPutErrorMsg( "表达式非法！( 括号不匹配 )" );
		return NULL;
	}

	CStack<CExpToken>	TokenStack;

	CExpToken curToken;
	CExpToken nextToken;
	CExpToken topToken;
	bool bHasNext = false;
	bool bHasTop = false;

	// 处理只有一个操作数的情况
	if( ExpTokens.Size() == 1 )
	{
		curToken = ExpTokens.Pop();
		if( IsOptTarget( curToken.m_Token.m_eTokenType ) )
		{
			topToken.m_bIsExp = false;
			topToken.m_pExp = NULL;
			topToken.m_Token.m_eTokenType = EToken_And;
			topToken.m_Token.m_strTokenString = "&&";
			return BuildExpression( topToken, curToken, curToken, pBrain );
		}
	}

	// 开始分析
	while( true )
	{
		// 当前正在处理的记号
		curToken = ExpTokens.Pop();
		// 下一个要处理的记号
		if( ExpTokens.Empty() )
			bHasNext = false;
		else
		{
			nextToken = ExpTokens.Pop();
			bHasNext = true;
		}
		// 栈顶的记号
		if( TokenStack.Empty() )
			bHasTop = false;
		else
		{
			bHasTop = true;
			topToken = TokenStack.Pop();
		}

		// 如果未处理栈和处理栈都空了，则返回当前记号的表达式
		if( !bHasTop && !bHasNext )
		{
			if( !curToken.m_bIsExp )
			{
				OutPutErrorMsg( "表达式非法！( %s )", lpszString );
				Clear();
				return NULL;		
			}
			return curToken.m_pExp;
		}

		// 如果栈里没有的话，直接放入栈里
		if( ! bHasTop )
		{
			TokenStack.Push( curToken );
			if( bHasNext )
				ExpTokens.Push( nextToken );
			continue;
		}

		// 如果当前处理的是操作符，直接放入栈里
		if( ! curToken.m_bIsExp && IsOpt( curToken.m_Token.m_eTokenType ) )
		{
			if( bHasTop )
				TokenStack.Push( topToken );
			TokenStack.Push( curToken );
			if( bHasNext )
				ExpTokens.Push( nextToken );
			continue;
		}

		// 如果是左括号，直接放入栈里
		if( curToken.m_Token.m_eTokenType == EToken_BracketOpen )
		{
			if( bHasTop )
				TokenStack.Push( topToken );
			TokenStack.Push( curToken );
			if( bHasNext )
				ExpTokens.Push( nextToken );
			continue;
		}

		// 如果栈顶是左括号，下一个是右括号，则去掉括号
		if( topToken.m_Token.m_eTokenType == EToken_BracketOpen && nextToken.m_Token.m_eTokenType == EToken_BracketClose )
		{
			ExpTokens.Push( curToken );
			continue;
		}

		// 如果栈顶是左括号，直接放入栈里
		if( topToken.m_Token.m_eTokenType == EToken_BracketOpen )
		{
			if( bHasTop )
				TokenStack.Push( topToken );
			TokenStack.Push( curToken );
			if( bHasNext )
				ExpTokens.Push( nextToken );
			continue;
		}

		// 如果是操作数或者表达式的话
		if( curToken.m_bIsExp || IsOptTarget( curToken.m_Token.m_eTokenType ) )
		{
			// 如果栈顶非空且不是运算符，分析失败
			if( bHasTop && ! topToken.m_bIsExp && ! IsOpt( topToken.m_Token.m_eTokenType ) )
			{
				OutPutErrorMsg( "表达式非法！( %s )", lpszString );
				Clear();
				return NULL;
			}

			// 如果下一个非空且不是运算符，分析失败
			if( bHasNext && ! nextToken.m_bIsExp && ! IsOpt( nextToken.m_Token.m_eTokenType ) )
			{
				OutPutErrorMsg( "表达式非法！( %s )", lpszString );
				Clear();
				return NULL;
			}

			// 对于栈顶是 - 号，特殊处理一下
			// 如果栈顶的下一个符号是操作数或者表达式的话，就是双目的减法
			// 否则就是一个单目的负号
			if( topToken.m_Token.m_eTokenType == EToken_Sub )
			{
				if( TokenStack.Empty() )
					topToken.m_Token.m_eTokenType = EToken_Neg;
				else
				{
					CExpToken token = TokenStack.Top();
					if( !( token.m_bIsExp || !token.m_bIsExp && IsOptTarget( token.m_Token.m_eTokenType ) ) )
						topToken.m_Token.m_eTokenType = EToken_Neg;
				}
			}

			// 如果栈顶是一个单目运算符，构造表达式
			if( IsSingleOpt( topToken.m_Token.m_eTokenType) )
			{
				if( bHasNext )
					ExpTokens.Push( nextToken );
				CExpToken Exp;
				Exp.m_bIsExp = true;
				Exp.m_pExp = BuildExpression( topToken, curToken, pBrain );
				if( NULL == Exp.m_pExp )
				{
					OutPutErrorMsg( "表达式非法！( %s )", lpszString );
					Clear();
					return NULL;
				}
				ExpTokens.Push( Exp );
				continue;
			}

			// 如果栈顶是一个双目运算符，且下一个运算符优先级低于它，构造表达式
			if( IsCoupleOpt( topToken.m_Token.m_eTokenType ) )
			{
				if(  ( ! nextToken.m_bIsExp && m_iOptPriority[topToken.m_Token.m_eTokenType] <= m_iOptPriority[nextToken.m_Token.m_eTokenType] )
					|| nextToken.m_bIsExp )
				{
					if( TokenStack.Empty() )
					{
						OutPutErrorMsg( "表达式非法！( %s )", lpszString );
						Clear();
						return NULL;
					}
					if( bHasNext )
						ExpTokens.Push( nextToken );
					CExpToken Left, Exp;
					Left = TokenStack.Pop();
					Exp.m_bIsExp = true;
					Exp.m_pExp = BuildExpression( topToken, Left, curToken, pBrain );
					if( NULL == Exp.m_pExp )
					{
						OutPutErrorMsg( "表达式非法！( %s )", lpszString );
						Clear();
						return NULL;
					}
					ExpTokens.Push( Exp );
					continue;
				}
				// 后面的操作符的优先级高于前面的，入栈
				else
				{
					if( bHasTop )
						TokenStack.Push( topToken );
					TokenStack.Push( curToken );
					if( bHasNext )
						ExpTokens.Push( nextToken );
					continue;
				}
			}

			// 其它情况都是错误的
			OutPutErrorMsg( "表达式非法！( %s )", lpszString );
			Clear();
			return NULL;

		}

	}
	return NULL;
}

/*  
@	功能：	清除操作
@	参数：	
@	返回值：
@	注：	如果分析失败，可能要清除创建的一些东西
*/
void CExpressionAnalyzer::Clear( void )
{
	CExpression* pExp = NULL;
	for( int i = 0; i < (int)m_pAllExpression.size(); ++ i )
	{
		pExp = m_pAllExpression[i];
		if( pExp )
			delete pExp;
	}
	m_pAllExpression.clear();
}

/*  
@	功能：	构建一个表达式	单目
@	参数：	Opt:	操作符表达式符号
			right:	右操作数表达式符号
@	返回值：创建的表达式的指针
@	注：	
*/
CExpression *CExpressionAnalyzer::BuildExpression(const CExpToken &Opt, const CExpToken &right, CAIBrain *pBrain )
{
	CExpression *pNewExp = new CExpression;

	switch( Opt.m_Token.m_eTokenType )
	{
	case EToken_Not:	
		pNewExp->m_eOptType = EOptType_Not;
		pNewExp->m_strExp = "!";
		break;

	case EToken_Neg:	
		pNewExp->m_eOptType = EOptType_Neg;
		pNewExp->m_strExp = "-";
		break;
	default:
		delete pNewExp;	
		OutPutErrorMsg( "表达式非法 操作符" );
		return NULL;
	}		

	double dValue = 0;

	if( right.m_bIsExp )
	{
		pNewExp->m_RData.m_eType = EDataType_Expression;
		pNewExp->m_strExp += "Exp";
		pNewExp->m_RData.m_Data.m_pExpression = right.m_pExp;
		EraseExpression( right.m_pExp );
	}
	else if( right.m_Token.m_eTokenType == EToken_Identifier )
	{
		if( pBrain )
		{
			pNewExp->m_RData.m_eType = EDataType_Property;
			pNewExp->m_RData.m_Data.m_pProperty = pBrain->FindProperty( right.m_Token.m_strTokenString );
			if( NULL == pNewExp->m_RData.m_Data.m_pProperty )
			{
				delete pNewExp;
				OutPutErrorMsg( "表达式非法！ 属性不存在 %s ", right.m_Token.m_strTokenString.c_str() );
				return NULL;
			}
		}
	}
	else
	{
		dValue = atof( right.m_Token.m_strTokenString.c_str() );
		pNewExp->m_strExp += right.m_Token.m_strTokenString;

		switch( right.m_Token.m_eTokenType )
		{
		case EToken_Float:
			pNewExp->m_RData.m_eType = EDataType_Float;
			pNewExp->m_RData.m_Data.m_fData = (float)dValue;
			break;

		case EToken_Int:
		case EToken_Long:
			pNewExp->m_RData.m_eType = EDataType_Long;
			pNewExp->m_RData.m_Data.m_lData = (long)dValue;
			break;

		case EToken_UnsignedInt:
		case EToken_UnsignedLong:
			pNewExp->m_RData.m_eType = EDataType_UnsignedLong;
			pNewExp->m_RData.m_Data.m_ulData = (unsigned long )dValue;
			break;

		default:
			delete pNewExp;
			OutPutErrorMsg( "表达式非法！ 无法识别的数据类型" );
			return NULL;
		}
	}

	m_pAllExpression.push_back( pNewExp );
	return pNewExp;
}

/*  
@	功能：	构建一个表达式  双目
@	参数：	Opt:	操作符表达式符号
			left:	左操作数表达式符号
			right:	右操作数表达式符号
@	返回值：创建的表达式的指针
@	注：	
*/
CExpression *CExpressionAnalyzer::BuildExpression(const CExpToken &Opt, const CExpToken &left, const CExpToken &right, CAIBrain *pBrain )
{
	CExpression *pNewExp = new CExpression;

	double dValue;

	// 左操作数
	if( left.m_bIsExp )
	{
		pNewExp->m_LData.m_eType = EDataType_Expression;
		pNewExp->m_LData.m_Data.m_pExpression = left.m_pExp;
		pNewExp->m_strExp = "Exp";
		EraseExpression( left.m_pExp );
	}
	else if( left.m_Token.m_eTokenType == EToken_Identifier )
	{
		if( pBrain )
		{
			pNewExp->m_LData.m_eType = EDataType_Property;
			pNewExp->m_LData.m_Data.m_pProperty = pBrain->FindProperty( left.m_Token.m_strTokenString );
			if( NULL == pNewExp->m_LData.m_Data.m_pProperty )
			{
				delete pNewExp;
				OutPutErrorMsg( "表达式非法！ 属性不存在 %s ", left.m_Token.m_strTokenString.c_str() );
				return NULL;
			}
		}
	}
	else
	{
		dValue = atof( left.m_Token.m_strTokenString.c_str() );
		pNewExp->m_strExp = left.m_Token.m_strTokenString;

		switch( left.m_Token.m_eTokenType )
		{
		case EToken_Float:
			pNewExp->m_LData.m_eType = EDataType_Float;
			pNewExp->m_LData.m_Data.m_fData = (float)dValue;
			break;

		case EToken_Int:
		case EToken_Long:
			pNewExp->m_LData.m_eType = EDataType_Long;
			pNewExp->m_LData.m_Data.m_lData = (long)dValue;
			break;

		case EToken_UnsignedInt:
		case EToken_UnsignedLong:
			pNewExp->m_LData.m_eType = EDataType_UnsignedLong;
			pNewExp->m_LData.m_Data.m_ulData = (unsigned long )dValue;
			break;

		default:
			delete pNewExp;
			OutPutErrorMsg( "表达式非法！ 无法识别的数据类型" );
			return NULL;
		}
	}


	switch( Opt.m_Token.m_eTokenType )
	{
	case EToken_And:
		pNewExp->m_eOptType = EOptType_And;
		pNewExp->m_strExp += "&&";
		break;
	case EToken_Or:
		pNewExp->m_eOptType = EOptType_Or;
		pNewExp->m_strExp += "||";
		break;
	case EToken_Equal:
		pNewExp->m_eOptType = EOptType_Equal;
		pNewExp->m_strExp += "==";
		break;
	case EToken_NotEqual:
		pNewExp->m_eOptType = EOptType_NotEqual;
		pNewExp->m_strExp += "!=";
		break;
	case EToken_Less:
		pNewExp->m_eOptType = EOptType_Less;
		pNewExp->m_strExp += "<";
		break;
	case EToken_Greater:
		pNewExp->m_eOptType = EOptType_Greater;
		pNewExp->m_strExp += ">";
		break;
	case EToken_LessEqual:
		pNewExp->m_eOptType = EOptType_LessEqual;
		pNewExp->m_strExp += "<=";
		break;
	case EToken_GreaterEqual:
		pNewExp->m_eOptType = EOptType_GreaterEqual;
		pNewExp->m_strExp += ">=";
		break;
	case EToken_Add:
		pNewExp->m_eOptType = EOptType_Add;
		pNewExp->m_strExp += "+";
		break;
	case EToken_Sub:
		pNewExp->m_eOptType = EOptType_Sub;
		pNewExp->m_strExp += "-";
		break;
	case EToken_Mul:
		pNewExp->m_eOptType = EOptType_Mul;
		pNewExp->m_strExp += "*";
		break;
	case EToken_Div:
		pNewExp->m_eOptType = EOptType_Div;
		pNewExp->m_strExp += "/";
		break;

	default:
		delete pNewExp;	
		OutPutErrorMsg( "表达式非法 操作符" );
		return NULL;
	}


	// 右操作数
	if( right.m_bIsExp )
	{
		pNewExp->m_RData.m_eType = EDataType_Expression;
		pNewExp->m_RData.m_Data.m_pExpression = right.m_pExp;
		pNewExp->m_strExp += "Exp";
		EraseExpression( right.m_pExp );
	}
	else if( right.m_Token.m_eTokenType == EToken_Identifier )
	{
		if( pBrain )
		{
			pNewExp->m_RData.m_eType = EDataType_Property;
			pNewExp->m_RData.m_Data.m_pProperty = pBrain->FindProperty( right.m_Token.m_strTokenString );
			if( NULL == pNewExp->m_RData.m_Data.m_pProperty )
			{
				delete pNewExp;
				OutPutErrorMsg( "表达式非法！ 属性不存在 %s ", right.m_Token.m_strTokenString.c_str() );
				return NULL;
			}
		}
	}
	else
	{
		dValue = atof( right.m_Token.m_strTokenString.c_str() );
		pNewExp->m_strExp += right.m_Token.m_strTokenString;

		switch( right.m_Token.m_eTokenType )
		{
		case EToken_Float:
			pNewExp->m_RData.m_eType = EDataType_Float;
			pNewExp->m_RData.m_Data.m_fData = (float)dValue;
			break;

		case EToken_Int:
		case EToken_Long:
			pNewExp->m_RData.m_eType = EDataType_Long;
			pNewExp->m_RData.m_Data.m_lData = (long)dValue;
			break;

		case EToken_UnsignedInt:
		case EToken_UnsignedLong:
			pNewExp->m_RData.m_eType = EDataType_UnsignedLong;
			pNewExp->m_RData.m_Data.m_ulData = (unsigned long )dValue;
			break;

		default:
			delete pNewExp;
			OutPutErrorMsg( "表达式非法！ 无法识别的数据类型" );
			return NULL;
		}
	}

	m_pAllExpression.push_back( pNewExp );
	return pNewExp;
}

void CExpressionAnalyzer::EraseExpression(CExpression *pExp)
{
	int size = (int)m_pAllExpression.size();
	for( int i = 0; i < size; ++ i )
	{
		if( pExp == m_pAllExpression[i] )
		{
			m_pAllExpression[i] = NULL;
			return;
		}
	}
}


AISYSTEM_SPACE_END