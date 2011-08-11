/*************************************
游戏战争模式3
***************************************/


#pragma  once 

#include "WarMode.h"
#include  "WarItem.h"


class GameState;
class UIWarModeThree;
class WarItemManager;
class WarItem;

class Item;


class WarModeThree :public WarMode,public WarItemListen
	{

public:

	/**构造函数*/
	WarModeThree( GameState* pGameState);


	~WarModeThree();


	/**开始战争*/
	virtual void start();

	/**战争结束*/
	virtual	void end();

	/**每帧更新*/
	virtual void update(float time);


	/**点击按下事件*/
	virtual  void beginTouch(int x,int y);


	/**目标点敌人被道具击中后的回调*/
	virtual void onHitTarget(WarItem* pItem,Enemy* pEnemy);


	/**增加力量槽*/
	void addPower(float power){m_CurrentPower+=power;}

	/**获取当前力量槽*/
	float getCurrentPower()const {return m_CurrentPower;}

    /**获取力量槽的大小*/
	float getMaxPower()const     {return m_MaxPower;}

protected:


	void initUI();

	void destroyUI();


	/**更新能量显示
	*/
	void updatePower(float time);



protected:

	

	UIWarModeThree* m_pUIWar;

	float           m_CurrentPower;///当前能量。
	float           m_MaxPower;    ///满能量
	float           m_StopFireTime; ///停止攻击的时间 
	float           m_LastFireTime; ///上一次攻击的时间


	Enemy*          m_pTargetEnemy;
	WarItemManager* m_pWarItemManager;

	Ogre::StringVector m_AnimationCollect; ///被击中后的动作列表


};