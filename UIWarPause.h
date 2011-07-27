/*******************************************
游戏暂时界面
**********************************************/

#pragma once

#include "UIBase.h"


class UIWarPause :public	UIBase
{

public:

	UIWarPause();


	~UIWarPause();


	void init();

	void setVisible(bool b);


protected:

///按钮回调事件
   virtual void buttonHit(Widget* button);


protected:
	Widget* m_pReturn ;
	Widget* m_pContinue;




};