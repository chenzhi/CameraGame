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


	/**设置是否可见*/
	void setVisible(bool b);


	/**设置当暂停结束后需要显示的界面*/
	void setEndShowUI(const std::vector<UIBase*>& UIList){m_ContinueShowUI=UIList;}


protected:

///按钮回调事件
   virtual void buttonHit(Widget* button);


protected:
	Widget* m_pReturn ;
	Widget* m_pContinue;

	///
	std::vector<UIBase*> m_ContinueShowUI;




};