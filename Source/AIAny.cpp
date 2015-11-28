#include "../PreInclude.h"
#include "../Include/AIAny.h"


AISYSTEM_SPACE_BEGIN

CAIAny_::CAIAny_(void)
{
	m_bIsNumeric = false;
	m_dData = 0;
	m_bNeg = false;
}

CAIAny_::CAIAny_(const std::string strData )
{
	SetData( strData );
}

CAIAny_::~CAIAny_(void)
{
}


void CAIAny_::SetData( int & value )
{
	m_dData = value;
	m_bIsNumeric = true;
	if( value < 0 )
		m_bNeg = true;
	else
		m_bNeg = false;
}

void CAIAny_::SetData( unsigned int & value )
{
	m_dData = value;
	m_bIsNumeric = true;
	m_bNeg = false;
}

void CAIAny_::SetData( long & value )
{
	m_dData = value;
	m_bIsNumeric = true;
	if( value < 0 )
		m_bNeg = true;
	else
		m_bNeg = false;
}

void CAIAny_::SetData( unsigned long & value )
{
	m_dData = value;
	m_bIsNumeric = true;
	m_bNeg = false;
}

void CAIAny_::SetData(float &value )
{
	m_dData = value;
	m_bIsNumeric = true;
	if( value < .0f )
		m_bNeg = true;
	else
		m_bNeg = false;
}

void CAIAny_::SetData( const std::string & value )
{
	m_strData = value;
	if( IsNumeric() )
	{
		m_bIsNumeric = true;
		m_dData = atof( m_strData.c_str() );
		if( m_dData < 0 )
			m_bNeg = true;
	}
	else
	{
		m_bIsNumeric = false;
	}
}


bool CAIAny_::GetInt(int &ret )
{
	if( m_bIsNumeric )
	{
		ret = (int)m_dData;
		return true;
	}
	return false;
}

bool CAIAny_::GetUnsignedInt(unsigned int &ret )
{
	if( m_bIsNumeric && !m_bNeg )
	{
		ret = (unsigned int)m_dData;
		return true;
	}
	return false;
}

bool CAIAny_::GetLong(long &ret )
{
	if( m_bIsNumeric )
	{
		ret = (long)m_dData;
		return true;
	}
	return false;
}

bool CAIAny_::GetUnsignedLong(unsigned long &ret)
{
	if( m_bIsNumeric && !m_bNeg )
	{
		ret = (unsigned long)m_dData;
		return true;
	}
	return false;
}

bool CAIAny_::GetFloat(float &ret )
{
	if( m_bIsNumeric )
	{
		ret = (float)m_dData;
		return true;
	}
	return false;
}

bool CAIAny_::GetDoulbe(double &ret )
{
	if( m_bIsNumeric )
	{
		ret = m_dData;
		return true;
	}
	return false;
}

bool CAIAny_::GetString(std::string &ret)
{
	ret = m_strData;
	return true;
}

bool CAIAny_::IsNumeric()
{
	int nLen = (int)m_strData.length();
	char ch;
	int nDot = 0;
	for( int i = 0; i < nLen; ++ i )
	{
		ch = m_strData.at(i);
		if( ch >= '0' && ch <= '9' )
			continue;
		if( i == 0 && ch =='-' )
			continue;
		if( ch == '.' && nDot == 0 )
		{
			++ nDot;
			continue;
		}
		return false;
	}
	return true;
}





AISYSTEM_SPACE_END