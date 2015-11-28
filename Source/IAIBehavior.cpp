#include "../PreInclude.h"
#include "../Include/IAIBehavior.h"


AISYSTEM_SPACE_BEGIN




/*  
@	功能：	构造函数，初始化数据成员
@	参数：	
@	返回值：
@	注：	
*/
IAIBehavior::IAIBehavior(void)
: m_uiAIType( 0 )
, m_pAIObject( NULL )
, m_bStopped( false )
{
}

/*  
@	功能：	析构函数
@	参数：	
@	返回值：
@	注：	
*/
IAIBehavior::~IAIBehavior(void)
{
}

/*  
@	功能：	更新AI，做一些更新的测试，并调用用户实现的更新方法
@	参数：	fElpasedTimes:	逝去的时间
@	返回值：返回行为的执行状态
@	注：	
*/
EAIBehaviorState IAIBehavior::RealUpdate( float fElpasedTimes )
{
	if( m_bStopped )
		return EAIBS_Succeed;
	return Update( fElpasedTimes );
}


AISYSTEM_SPACE_END