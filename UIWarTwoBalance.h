/************************************
模式2的结算界面
************************************/


#include "UIBase.h"
#include "UILLayout.h"

class WarMode;
class StaticImage;

class UIWarTowModeBalance :public UILayout
{

public:

	UIWarTowModeBalance(WarMode* pWarMode);

	~UIWarTowModeBalance();


	/**设置分数*/
	void setScore(unsigned int    score);

	void init();

	/**重置分数为0*/
	void resetScore();
	
protected:


	///消毁所有
	void destroy();


	///按钮回调事件
	virtual void buttonHit(Widget* button);




protected:

	WarMode* m_pWarMode;

	StaticImage* m_Score[5];

};
