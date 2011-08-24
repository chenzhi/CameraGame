
/***************************************************
战斗模式2的ui界面
*******************************************************/



#pragma  once


#include "UIBase.h"
#include "WarManager.h"


class RotateImage;
class ImageButton;
class StaticImage;
class Widget;
class EnemyQueue;

class UIWarModeTwo :public UIBase
{

public:


	UIWarModeTwo();


	~UIWarModeTwo();


	 void init();


	 /**每帧更新*/
	 virtual void update(float time);


	 ///设置敌人所有的方向
	 void notityEmeny(EnemyQueue* pEnemyQueue){m_pEnemy=pEnemyQueue;}


	 ///更新指向敌人的箭方向
	 void updateEnemyDir();



	 ///杀死一队敌人
	 void onKillEnemyQueue(EnemyQueue* pEnemyQueue);

	 ///敌人逃跑
	 void onLostEnemyQueue(EnemyQueue* pEnemyQueue);

	 ///创建新敌人
	 void onCrateEnemyQueue(EnemyQueue* pEnemyQueue);


	 ///重置状态在游戏开始时调用
	 void reset();


protected:

	 /**按钮回调事件*/
	 virtual void buttonHit(Widget* button);

	 /**开始触摸,*/
	 virtual void onBeginTouch(int x,int y);





	  ImageButton* m_PauseButton;  ///暂停按钮
	  ImageButton* m_pFireButton;  ///开火按钮
	  StaticImage* m_FirePoint;    ///中间准心
      RotateImage* m_pRotateImage;//指向敌人的方向

	  EnemyQueue*  m_pEnemy;

	  typedef std::vector<Widget*> WidgetCollect;
	  WidgetCollect  m_LifeCollect;


};