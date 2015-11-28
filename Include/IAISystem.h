/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAISystem.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#ifdef FKAISYSTEM_EXPORTS
	#define FKAISYSTEM_API __declspec(dllexport)
	#define FKAISYSTEM_FUN extern "C" __declspec(dllexport)
	#define FKAISYSTEM_VAR extern  __declspec(dllexport)
#else
	#define FKAISYSTEM_API __declspec(dllimport)
	#define FKAISYSTEM_FUN extern "C" __declspec(dllimport)
	#define FKAISYSTEM_VAR extern  __declspec(dllimport)
#endif

//--------------------------------------------------------------------

#define AISYSTEM_SPACE_BEGIN	namespace FKAISystem{
#define AISYSTEM_SPACE_END		}

//--------------------------------------------------------------------

#ifndef FKAISYSTEM_EXPORTS
	#ifdef _DEBUG
		#pragma comment( lib, "bin/FKAISystem_D.lib" )
	#else
		#pragma comment( lib, "bin/FKAISystem.lib" )
	#endif
#endif

//--------------------------------------------------------------------

#include <string>
#include <map>
#include <vector>
#include <deque>

//--------------------------------------------------------------------

#include "IAIDefine.h"

//--------------------------------------------------------------------
