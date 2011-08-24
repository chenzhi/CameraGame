

/***********************************************
游戏开始界面。点击play开始游戏，
*************************************************/


#include "UIBase.h"
#include "UILLayout.h"

class Widget;

class UIGamePlay :public UILayout
{
public:

	UIGamePlay();


	~UIGamePlay();



	/**初始化*/
	//virtual void init();

	//virtual void update(float time);



protected:


	/**点击按钮回调事件*/
	virtual void buttonHit(Widget* button);



	



};