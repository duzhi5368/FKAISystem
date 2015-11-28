/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIAny.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

class CAIAny_;


class FKAISYSTEM_API CAIAny
{
public:
	CAIAny_ *m_pAny;

public:
	CAIAny( void );
	CAIAny( const std::string strData );
	CAIAny( const CAIAny &any );
	const CAIAny & operator == ( const CAIAny &any );
	~CAIAny(void);

	void SetData( int & value );
	void SetData( unsigned int & value );
	void SetData( long & value );
	void SetData( unsigned long & value );
	void SetData( float &value );
	void SetData( const std::string & value );
	
	bool IsNumeric( void );

	bool GetInt( int &ret );
	bool GetUnsignedInt( unsigned int &ret );
	bool GetLong( long &ret );
	bool GetUnsignedLong( unsigned long &ret );
	bool GetString( std::string & ret );
	bool GetFloat( float &ret );
	bool GetDoulbe( double &ret );

	int GetInt( void );
	unsigned int GetUnsignedInt( void );
	long GetLong( void );
	unsigned long GetUnsignedLong( void );
	const std::string & GetString( void );
	float GetFloat( void );
	double GetDoulbe( void );
};

AISYSTEM_SPACE_END