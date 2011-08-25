#include "UIBase.h"
#include "UILLayout.h"


class Widget;
class StaticImage;

class UIWarone :public UILayout
{

public:

	UIWarone();

	~UIWarone();


	/**初始化*/
	virtual void init();

	/**更新时间
	*@param time 还剩多少秒
	*/
	void setTime(int time);


protected:


	/**按钮回调事件*/
	virtual void buttonHit(Widget* button);




protected:

//	Widget*        m_PauseButton;     ///暂停按钮
	//Widget*        m_FirePoint;       ///准心图标

	StaticImage*        m_HundredTime;     ///百秒
	StaticImage*        m_TenTime;          ///十秒
	StaticImage*        m_DigitTime;        ///个位数秒




};