
#pragma  once

#include "UIBase.h"




class UISelectMode :public UIBase
{


public:

	UISelectMode();

	~UISelectMode();




	/**初始化*/
	virtual void init();



protected:


	///点击按钮回调函数
	virtual void buttonHit(Widget* button);





};