/**********************************************
战争模式1
*****************************************************/

#include "WarMode.h"

class GameState;
class WarManager;
class UIWarone;

class WarModeOne :public WarMode, public WarListener
{

public:

	WarModeOne(GameState* pGameState);

	~WarModeOne();


	/**开始战争*/
	virtual void start();

	/**战争结束*/
	virtual	void end();

	/**每帧更新*/
	virtual void update(float time);



protected:


	virtual void updateAccelerometer();

	///初始化所有的阵列
	void  initEnemyFormat();

	/**初始化ui*/
	void  initUI();

	/**销毁ui*/
	void  destroyUI();

	/**创建一个队列*/
	void _createEnemyQueue();

	/**点击按下事件*/
	virtual  void beginTouch(int x,int y);




	///回调函数
	///杀死一队敌人
	virtual void onKillEnemyQueue(EnemyQueue* pEnemyQueue);

	///敌人逃跑
	virtual void onLostEnemyQueue(EnemyQueue* pEnemyQueue);

	virtual void onCrateEnemyQueue(EnemyQueue* pEnemyQueue){}


protected:


	WarManager*    m_pWarManager;//

	Ogre::SceneManager*   m_pSceneMrg;
           
	EnemyFormatCollect   m_EnemyFormatCollect;


	float                m_GameLeft;///游戏周期
	float                m_CurrentTime; ///游戏当前时间

	bool                 m_needCreate;///是否需要创建一个队列
	unsigned int         m_CreateIndex; ///当前创建的第几个队列;
	UIWarone*            m_pUI;
	UIBase*              m_pUIBalance;

	float                m_Minx;        ///最小x轴向角度
	float                m_Maxx;
	float                m_Miny;
	float                m_Maxy;
	float                m_Minz;
	float                m_Maxz;      

	unsigned int            m_KillCount;///本次杀死了多少敌人
	unsigned int            m_LostCount;///有多少人跑了
	float                m_EnemyLeftTime; ///敌人生命周期
	
	

};
