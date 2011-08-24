/************************************
模式2的结算界面
************************************/


#include "UIBase.h"
#include "UILLayout.h"

class WarMode;

class UIWarTowModeBalance :public UILayout
{

public:

	UIWarTowModeBalance(WarMode* pWarMode);

	~UIWarTowModeBalance();


	//void init();
	
protected:


	///消毁所有
	void destroy();


	///按钮回调事件
	virtual void buttonHit(Widget* button);




protected:

	WarMode* m_pWarMode;


};
