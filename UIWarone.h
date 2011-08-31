#include "UIBase.h"
#include "UILLayout.h"


class Widget;
class StaticImage;
class RotateImage;
class EnemyQueue;

class UIWarone :public UILayout
{

public:

	UIWarone();

	~UIWarone();


	/**初始化*/
	virtual void init();

	virtual void update(float time);

	/**更新时间
	*@param time 还剩多少秒
	*/
	void setTime(int time);


	///杀死一队敌人
	void onKillEnemyQueue(EnemyQueue* pEnemyQueue);

	///敌人逃跑
	void onLostEnemyQueue(EnemyQueue* pEnemyQueue);

	///创建新敌人
	void onCrateEnemyQueue(EnemyQueue* pEnemyQueue);

	/**设置分数*/
	void setScore(unsigned int    score);

	/**重置ui状态为初始*/
	void reset();


protected:


	/**按钮回调事件*/
	virtual void buttonHit(Widget* button);


	void updateEnemyDir();

	

protected:

//	Widget*        m_PauseButton;     ///暂停按钮
	//Widget*        m_FirePoint;       ///准心图标

	StaticImage*        m_HundredTime;     ///百秒
	StaticImage*        m_TenTime;          ///十秒
	StaticImage*        m_DigitTime;        ///个位数秒
	

	StaticImage*        m_ScoreImage[5];


	EnemyQueue*          m_pEnemy;
    RotateImage*          m_pRotateImage;//指向敌人的方向

};