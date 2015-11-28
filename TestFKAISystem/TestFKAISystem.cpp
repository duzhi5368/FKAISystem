// TestFKAISystem.cpp : 定义控制台应用程序的入口点。
//

#include "TestFKAISystem/stdafx.h"
#include "../Include/IAIGlobalFunc.h"
#include "Monster.h"

float                   g_fTimeFromLastFrame    = 0.0f;
float					g_fAccumTime			= 0.0f;
unsigned int			g_dwSleepTime           = 0;

void OutPut( const char* p_szInfo )
{
	std::cout << p_szInfo << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// 注册错误回调函数
	FKAISystem::RegisterErrorMsgReceiver( OutPut );
	// 初始化状态机表
	FKAISystem::SetStateFilesDirectory( "Bin/Data/AIScript" );


	CMonster* pMonster = new CMonster();
	pMonster->Init("状态机表名称");
	for( ;; )
	{
		// 获取帧间隔时间
		static float lastTime = 0;
		lastTime = g_fAccumTime;
		g_fAccumTime = (float)timeGetTime() / 1000.0f;
		g_fTimeFromLastFrame = g_fAccumTime - lastTime;

		//最低帧数控制
		if (g_fTimeFromLastFrame>0.2f)
			g_fTimeFromLastFrame = 0.2f;

		// 每帧间隔CPU休眠时间
		if(g_dwSleepTime > 0) Sleep(g_dwSleepTime);

		pMonster->Update( g_fTimeFromLastFrame );
	}
	pMonster->Destory();
	return 0;
}

