/********************************************************************
// FileName: d:\work\FKAISystem\Include\AICondition.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  触发器条件定义
*********************************************************************/

//#pragma once

//--------------------------------------------------------------------
//
//#include "AIStateDefine.h"
//
//
//AISYSTEM_SPACE_BEGIN
//
//class CProperty;
//
//
//
///****************************************************************
//+	CLASS
//-----------------------------------------------------------------
//+   类名:	CAICondition
//+   功能:	条件类，实现判断条件
//+   描述:	
//-----------------------------------------------------------------
//*****************************************************************/
//class CAICondition
//{
//	enum ERefType
//	{
//		ERT_Dword = 0,
//		ERT_Float,
//		ERT_Int,
//		ERT_Property,
//		ERT_End
//	};
//	union URefData
//	{
//		DWORD		m_dwData;
//		float		m_fData;
//		int			m_iData;
//		CProperty	*m_pProperty;
//	};
//
//	////////////////////////////////////////////
//	//	数据成员
//private:
//	CProperty				*m_pProperty;	// 条件的属性
//	EAIStateTestOperator	m_eOpType;		// 测试操作类型
//	URefData				m_RefData[2];	// 参考数据
//	ERefType				m_eRefType[2];	// 参数数据的类型
//
//	typedef bool (CAICondition::*CompFunc)(void);
//	static CompFunc		s_CompFunc[EAISTestOperator_End];			// 测试函数指针数组
//
//	////////////////////////////////////////////
//	//	构造/析构
//public:
//	CAICondition( void );
//	~CAICondition( void );
//
//
//	////////////////////////////////////////////
//	//	公共接口
//public:
//	/*  
//	@	功能：	测试条件
//	@	参数：	fElapsedTimes:	逝去的时间
//	@	返回值：是否成立
//	@	注：	
//	*/
//	bool Test( float fElapsedTimes );
//
//	/*  
//	@	功能：	设置条件比较参数
//	@	参数：	pProperty:	属性
//				eOpType:	操作类型
//				fRefValue0:	测试参考值0
//				fRefValue1:	测试参考值1
//	@	返回值：
//	@	注：	
//	*/
//	void SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, DWORD fRefValue0, DWORD fRefValue1 = 0 );
//
//	/*  
//	@	功能：	设置条件比较参数
//	@	参数：	pProperty:	属性
//				eOpType:	操作类型
//				fRefValue0:	测试参考值0
//				fRefValue1:	测试参考值1
//	@	返回值：
//	@	注：	
//	*/
//	void SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, float fRefValue0, float fRefValue1 = .0f );
//
//	/*  
//	@	功能：	设置条件比较参数
//	@	参数：	pProperty:		属性
//				eOpType:		操作类型
//				pRefProperty:	参考属性
//	@	返回值：
//	@	注：	
//	*/
//	void SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, CProperty *pRefProperty0, CProperty *pRefProperty1 = NULL );
//
//
//	////////////////////////////////////////////
//	//	内部接口
//protected:
//
//	/*  
//	@	功能：	定义测试比较函数
//	@	参数：	
//	@	返回值：
//	@	注：	
//	*/
//	bool _TestAllways( void )		{ return true;	}
//	bool _TestNever( void )			{ return false;	}
//	bool _TestLess( void );		
//	bool _TestGreate( void );
//	bool _TestEqual( void );
//	bool _TestLessEqual( void );
//	bool _TestGreateEqual( void );
//	bool _TestNotEqual( void );
//	bool _TestInner( void );
//	bool _TestOutter( void );
//};
//
//
//
//AISYSTEM_SPACE_END