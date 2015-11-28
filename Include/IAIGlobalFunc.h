/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIGlobalFunc.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  定义需要导出的全局的函数
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

class IAIBehaviorFactory;


/*  
@	功能：	设置状态机定义文件的目录
@	参数：	dtrDirectory:	目录
@	返回值：
@	注：	
*/
FKAISYSTEM_FUN void SetStateFilesDirectory( const std::string & strDirectory );

/*
@	功能：	设置行为状态工厂
@	参数：	pFactory 行为状态工厂
@	返回值：	
@	注：
*/
FKAISYSTEM_FUN bool SetBehaviorFactory( IAIBehaviorFactory *pFactory );

/*
@	功能：	设置错误输出函数
@	参数：	用户自定义函数指针
@	返回值：	
@	注：
*/
typedef void (*AIPErrorMsgReceiver)( const char *lpszErrorMsg );
FKAISYSTEM_FUN void RegisterErrorMsgReceiver( AIPErrorMsgReceiver pFunc );

FKAISYSTEM_FUN void OutPutErrorMsg( char * format, ... );


AISYSTEM_SPACE_END