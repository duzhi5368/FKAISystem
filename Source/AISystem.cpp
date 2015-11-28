/********************************************************************
// FileName: d:\work\FKAISystem\Source\AISystem.cpp
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  定义程序DLL入口
*********************************************************************/

#include "../PreInclude.h"
#include "../Include/IAISystem.h"

//--------------------------------------------------------------------

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif


