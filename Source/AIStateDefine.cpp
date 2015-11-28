#include "../PreInclude.h"
#include "../Include/AIStateDefine.h"




AISYSTEM_SPACE_BEGIN


/*  
@	功能：	将一个以特定符号分隔的数字字符串转换成数据序列
@	参数：	vecNumbers:	提取出来的数字序列 
			strNumbers:	数字字符串
			cSeparate:	分隔符
@	返回值：返回分析出来的数字的个数
@	注：	
*/
int Parse2Floats( std::vector<float> & vecNumbers, const std::string & strNumbers, char cSeparate /*= ','*/ )
{
	const char *lpszStr = strNumbers.c_str();
	size_t len = strNumbers.length();
	char szBuf[32];
	memset( szBuf, 0, sizeof( szBuf ) );
	float fNumber = 0;
	int w = 0;
	for( size_t i = 0; i < len; ++ i )
	{
		if( lpszStr[i] >= '0' && lpszStr[i] <= '9' )
			sprintf( szBuf, "%c", lpszStr[w++] );
		else if( lpszStr[i] == cSeparate )
		{
			fNumber = (float)atof( szBuf );
			vecNumbers.push_back( fNumber );
			memset( szBuf, 0, sizeof( szBuf ) );     
			w = 0;
		}
		else
			return 0;
	}
	fNumber = (float)atof( szBuf );
	vecNumbers.push_back( fNumber );

	return (int)vecNumbers.size();
}

int Parse2Strings( std::vector<std::string> &vecStrs, const std::string & strString, char cDeli /*= ','*/ )
{
	const char *lpszStr = strString.c_str();
	size_t len = strString.length();
	if( len == 0 )
		return 0;
	char szBuf[32];
	memset( szBuf, 0, sizeof( szBuf ) );
	int w = 0;
	for( size_t i = 0; i < len; ++ i )
	{
		if( lpszStr[i] == cDeli )
		{
			vecStrs.push_back( szBuf );
			memset( szBuf, 0, sizeof( szBuf ) );     
			w = 0;
		}
		else
			szBuf[w++] = lpszStr[i];
	}
	vecStrs.push_back( szBuf );

	return (int)vecStrs.size();
}

bool IsNumeric( const std::string &str )
{
	int nLen = (int)str.length();
	char ch;
	int nDot = 0;
	for( int i = 0; i < nLen; ++ i )
	{
		ch = str.at(i);
		if( ch >= '0' && ch <= '9' )
			continue;
		if( i == 0 && ch =='-' )
			continue;
		if( ch == '.' )
		{
			++ nDot;
			if( nDot <= 1 )
				continue;
		}
		return false;
	}
	return true;
}





AISYSTEM_SPACE_END