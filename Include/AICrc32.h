/********************************************************************
// FileName: d:\work\FKAISystem\Include\AICrc32.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  CRC32ะฃั้
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

class Crc32
{
public:
	Crc32(void);
	Crc32( Crc32 &obj );
	Crc32 &operator = ( Crc32 &obj );
	~Crc32(void);

public:
	int GetCRC( const char* lpszData ); 
};


AISYSTEM_SPACE_END

