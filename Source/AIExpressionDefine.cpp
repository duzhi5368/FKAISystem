#include "../PreInclude.h"
#include "../Include/AIExpressionDefine.h"
#include "../Include/AIProperty.h"
#include "../Include/IAIGlobalFunc.h"


AISYSTEM_SPACE_BEGIN



void SData::Release( void )
{
	if( m_eType == EDataType_Expression && m_Data.m_pExpression != NULL )
	{
		delete m_Data.m_pExpression;
		m_Data.m_pExpression = NULL;
	}
}


bool SData::CalculateLogic( void )
{
	double temp = CalculateNumeric();
	if( temp <= 0.0000000000001 )
		return false;
	return true;
}

/*  
@	功能：	重载逻辑运算符
@	参数：	
@	返回值：
@	注：	
*/
bool SData::operator ! ( )
{
	return ! CalculateLogic();
}

bool SData::operator && ( const SData &data )
{
	SData temp;
	temp = data;
	bool left = CalculateLogic();
	bool right = temp.CalculateLogic();

	return left && right;
}

bool SData::operator || ( const SData &data )
{
	SData temp;
	temp = data;
	bool left = CalculateLogic();
	bool right = temp.CalculateLogic();

	return left || right;
}

double SData::CalculateNumeric( void )
{
	switch( m_eType )
	{
	case EDataType_Property:
		return m_Data.m_pProperty->GetDouble();
	case EDataType_Expression:
		return (*m_Data.m_pExpression)();
	case EDataType_Float:
		return (double)m_Data.m_fData;
	case EDataType_Long:
		return (double)m_Data.m_lData;
	case EDataType_UnsignedLong:
		return (double)m_Data.m_ulData;

	default:
		OutPutErrorMsg( "表达式非法！无效的操作符" );
		return 0;
	}
}

/*  
@	功能：	重载比较运算符
@	参数：	
@	返回值：
@	注：	
*/
bool SData::operator == ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left == right;
}
bool SData::operator != ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left != right;
}
bool SData::operator >  ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left > right;
}
bool SData::operator >= ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left >= right;
}
bool SData::operator <  ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left < right;
}
bool SData::operator <= ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left <= right;
}

/*  
@	功能：	重载算术运算符
@	参数：	
@	返回值：
@	注：	
*/
double SData::operator + ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left + right;
}
double SData::operator - ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left - right;
}
double SData::operator * ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left * right;
}
double SData::operator / ( const SData &data )
{
	SData temp;
	temp = data;
	double left = CalculateNumeric();
	double right = temp.CalculateNumeric();
	return left / right;
}

double SData::operator - ( )
{
	return CalculateNumeric() * -1;
}


//////////////////////////////////////////////////////////////////////////
// 静态数据初始化
CExpression::CompFunc CExpression::s_pCompFuncs[EOptType_End];
bool CExpression::s_CompFuncInited = false;

/*  
@	功能：	构造函数，初始化静态比较函数数组
@	参数：	
@	返回值：
@	注：	
*/
CExpression::CExpression()
{
	if( false == s_CompFuncInited )
	{
		s_pCompFuncs[EOptType_Not]			= &CExpression::Not;
		s_pCompFuncs[EOptType_And]			= &CExpression::And;
		s_pCompFuncs[EOptType_Or]			= &CExpression::Or;
		s_pCompFuncs[EOptType_Equal]		= &CExpression::Equal;
		s_pCompFuncs[EOptType_NotEqual]		= &CExpression::NotEqual;
		s_pCompFuncs[EOptType_Less]			= &CExpression::Less;
		s_pCompFuncs[EOptType_LessEqual]	= &CExpression::LeeeEqual;
		s_pCompFuncs[EOptType_Greater]		= &CExpression::Greater;
		s_pCompFuncs[EOptType_GreaterEqual]	= &CExpression::GreaterEqual;
		s_pCompFuncs[EOptType_Add]			= &CExpression::Add;
		s_pCompFuncs[EOptType_Sub]			= &CExpression::Sub;
		s_pCompFuncs[EOptType_Mul]			= &CExpression::Mul;
		s_pCompFuncs[EOptType_Div]			= &CExpression::Div;
		s_pCompFuncs[EOptType_Neg]			= &CExpression::Neg;
		s_CompFuncInited = true;
	}
}

/*  
@	功能：	执行表达式
@	参数：	
@	返回值：
@	注：	
*/
double CExpression::operator ()()
{
	if( m_eOptType >= EOptType_Not && m_eOptType < EOptType_End )
	{
		if( s_CompFuncInited )
			return (this->*s_pCompFuncs[m_eOptType])();
		else
			OutPutErrorMsg( "表达式比较函数没有初始化" );
		return .0f;
	}
	OutPutErrorMsg( "表达式非法！无效的操作符" );
	return false;
}

void CExpression::Release()
{
	m_LData.Release();
	m_RData.Release();
}

CExpression::~CExpression( void )
{
	Release();
}



AISYSTEM_SPACE_END