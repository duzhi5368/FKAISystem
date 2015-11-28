#include "../PreInclude.h"
#include "../Include/IAIGlobalFunc.h"
#include "../Include/AIStateInfoManager.h"
#include "../Include/IAIBehaviorFactory.h"




AISYSTEM_SPACE_BEGIN


/*  
@	功能：	设置状态机定义文件的目录
@	参数：	dtrDirectory:	目录
@	返回值：
@	注：	
*/
void SetStateFilesDirectory( const std::string & strDirectory )
{
	CAIStateInfoManager::Instance()->SetAIFileDirectory( strDirectory );
	CAIStateInfoManager::Instance()->Initialize();  
}



bool SetBehaviorFactory(IAIBehaviorFactory *pFactory )
{
	if( NULL != IAIBehaviorFactory::s_pFactory )
		return false;
	IAIBehaviorFactory::s_pFactory = pFactory;
	if( pFactory )
		pFactory->Init();
	return true;
}


AIPErrorMsgReceiver G_pErrorMsgReceiver = NULL;
FKAISYSTEM_FUN void RegisterErrorMsgReceiver( AIPErrorMsgReceiver pFunc )
{
	G_pErrorMsgReceiver = pFunc;
}




FKAISYSTEM_FUN void OutPutErrorMsg( char * format, ... )
{
	static char buf[2048];
	static char numBuf[2048];
	va_list arg_ptr;
	va_start(arg_ptr, format);
	memset( buf, 0, sizeof(buf) );

	int len = (int)strlen( format );
	int bufIndex = 0;
	for( int i = 0; i < len; ++ i )
	{
		if( format[i] != '%' )
		{
			buf[bufIndex++] = format[i];
		}
		else
		{
			switch( format[++i] )
			{
			case 'd':
			case 'D':
				{
					int data = va_arg( arg_ptr, int );
					_itoa( data, numBuf, 10 );
				}
				break;
			case 'l':
			case 'L':
				{
					long data = va_arg( arg_ptr, long );
					_ltoa( data, numBuf, 10 );
				}
				break;
			case 's':
			case 'S':
				{
					char * data = va_arg( arg_ptr, char*);
					strcpy( numBuf, data );
				}
				break;
			}
			int l = (int)strlen( numBuf );
			for( int j = 0; j < l; ++ j )
			{
				buf[bufIndex++] = numBuf[j];
			}
			memset( numBuf, 0, sizeof(numBuf) );
		}
	}
	va_end(arg_ptr);
	
	static std::string strMsg;
	strMsg = "AIERROR: ";
	strMsg += buf;
	(*G_pErrorMsgReceiver)(strMsg.c_str());
}



AISYSTEM_SPACE_END