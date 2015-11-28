/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIStateDefine.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  AI状态机类型定义
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


/****************************************************************
+	ENUM
-----------------------------------------------------------------
+	描述:	测试操作符
-----------------------------------------------------------------
*****************************************************************/
//enum EAIStateTestOperator
//{
//	EAISTestOperator_Allways = 0,	// 总是通过
//	EAISTestOperator_Never,			// 永远为假
//	EAISTestOperator_Less,			// 小于
//	EAISTestOperator_Greate,		// 大于
//	EAISTestOperator_Equal,			// 等于
//	EAISTestOperator_LessEqual,		// 小于等于
//	EAISTestOperator_GreateEqual,	// 大于等于
//	EAISTestOperator_NotEqual,		// 不等于
//	EAISTestOperator_Inner,			// 在范围内
//	EAISTestOperator_Outter,		// 在范围外 
//	EAISTestOperator_End
//};


/****************************************************************
+	ENUM
-----------------------------------------------------------------
+	描述:	状态机运行状态
-----------------------------------------------------------------
*****************************************************************/
enum EStateMachineState
{
	ESMachineState_Stopped = 0,	// 停止状态
	ESMachineState_Running,		// 运行状态
	ESMachineState_Sleeping,	// 休眠状态
	ESMachineState_End
};




/*  
@	功能：	将一个浮点数转换成DWORD来存储
@	参数：	fValue:	要转换的浮点数
@	返回值：转换后的DWORD数
@	注：	
*/
inline DWORD F2DW( float fValue )
{
	return *((DWORD*)&fValue);
}

/*  
@	功能：	将一个以特定符号分隔的数字字符串转换成数据序列
@	参数：	vecNumbers:	提取出来的数字序列 
			strNumbers:	数字字符串
			cSeparate:	分隔符
@	返回值：返回分析出来的数字的个数
@	注：	
*/
int Parse2Floats( std::vector<float> & vecNumbers, const std::string & strNumbers, char cSeparate = ',' );

int Parse2Strings( std::vector<std::string> &vecStrs, const std::string & strString, char cDeli = ',' );

bool IsNumeric( const std::string &str );


AISYSTEM_SPACE_END