#include "../PreInclude.h"
#include "../Include/IAIAny.h"
#include "../Include/AIAny.h"





AISYSTEM_SPACE_BEGIN






CAIAny::CAIAny()
{
	m_pAny = new CAIAny_;
}

CAIAny::CAIAny(const std::string strData)
{
	m_pAny = new CAIAny_( strData );
}

CAIAny::CAIAny(const CAIAny &any )
{
	if( any.m_pAny )
	{
		m_pAny = new CAIAny_;
		m_pAny->m_bIsNumeric = any.m_pAny->m_bIsNumeric;
		m_pAny->m_bNeg = any.m_pAny->m_bNeg;
		m_pAny->m_dData = any.m_pAny->m_dData;
		m_pAny->m_strData = any.m_pAny->m_strData;
	}
}

const CAIAny & CAIAny::operator ==( const CAIAny & any )
{
	if( any.m_pAny )
	{
		m_pAny = new CAIAny_;
		m_pAny->m_bIsNumeric = any.m_pAny->m_bIsNumeric;
		m_pAny->m_bNeg = any.m_pAny->m_bNeg;
		m_pAny->m_dData = any.m_pAny->m_dData;
		m_pAny->m_strData = any.m_pAny->m_strData;
	}
	return *this;
}

CAIAny::~CAIAny( )
{
	delete m_pAny;
}

void CAIAny::SetData( int & value )
{
	m_pAny->SetData( value );
}

void CAIAny::SetData( unsigned int & value )
{
	m_pAny->SetData( value );
}

void CAIAny::SetData( long & value )
{
	m_pAny->SetData( value );
}

void CAIAny::SetData( unsigned long & value )
{
	m_pAny->SetData( value );
}

void CAIAny::SetData( float & value )
{
	m_pAny->SetData( value );
}

void CAIAny::SetData( const std::string & strData )
{
	m_pAny->SetData( strData );
}

bool CAIAny::IsNumeric( void )
{
	return m_pAny->IsNumeric();
}

bool CAIAny::GetInt(int &ret )
{
	return m_pAny->GetInt( ret );
}

bool CAIAny::GetUnsignedInt(unsigned int &ret )
{
	return m_pAny->GetUnsignedInt( ret );
}

bool CAIAny::GetLong(long &ret )
{
	return m_pAny->GetLong( ret );
}

bool CAIAny::GetUnsignedLong(unsigned long &ret)
{
	return m_pAny->GetUnsignedLong( ret );
}

bool CAIAny::GetFloat(float &ret )
{
	return m_pAny->GetFloat( ret );
}

bool CAIAny::GetDoulbe(double &ret )
{
	return m_pAny->GetDoulbe( ret );
}

bool CAIAny::GetString(std::string &ret)
{
	return m_pAny->GetString( ret );
}

int CAIAny::GetInt( void )
{
	int i = 0;
	m_pAny->GetInt( i );
	return i;
}

unsigned int CAIAny::GetUnsignedInt( void )
{
	unsigned int d = 0;
	m_pAny->GetUnsignedInt( d );
	return d;
}

long CAIAny::GetLong( void )
{
	long d = 0;
	m_pAny->GetLong( d );
	return d;
}

unsigned long CAIAny::GetUnsignedLong( void )
{
	unsigned long d = 0;
	m_pAny->GetUnsignedLong( d );
	return d;
}

const std::string & CAIAny::GetString( void )
{
	static std::string data = "";
	m_pAny->GetString( data );
	return data;
}

float CAIAny::GetFloat( void )
{
	float d = .0f;
	m_pAny->GetFloat( d );
	return d;
}

double CAIAny::GetDoulbe( void )
{
	double d = 0;
	m_pAny->GetDoulbe( d );
	return d;
}


AISYSTEM_SPACE_END