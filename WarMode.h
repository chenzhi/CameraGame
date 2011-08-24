
#pragma once



/************************************
游戏模式基类
*************************************/

#include "WarManager.h"
#include "inputListen.h"



class GameState;


class  WarMode
{
public:

	WarMode(GameState* pGameState)
	:m_end(false),m_pGameState(pGameState){}

	virtual ~WarMode(){}

	
	/**开始游戏*/
	virtual void start()=0;

	/**游戏结束*/
    virtual	void end()=0;

	/**每帧更新*/
	virtual void update(float time)=0;


	/**点击按下事件*/
	virtual  void beginTouch(int x,int y){};

	/**点击离开事件*/
	virtual void  endTouch(int x,int y){};

	/**点击移动事件*/
	virtual void  moveTouch(int x,int y){}


	/**判断游戏是否结束*/
	bool    isEnd()const{return m_end;}


	/**更新重力计数据，控制摄像头运动*/
	virtual void updateAccelerometer(){return ;}


protected:

	


	GameState*       m_pGameState;

	bool             m_end;////true为游戏结束



};







/***************************************************
游戏模式2
****************************************************/
class UIWarModeTwo;
class Enemy;
class UIBase;

///阵型类
typedef std::vector<Ogre::Vector3> Vector3Collect;
class EnemyFormat
{
public:
	Vector3Collect m_EnemyCollect;
	Vector3Collect m_FriendCollect;

};

typedef std::vector<EnemyFormat> EnemyFormatCollect;



class WarModeTwo :public WarMode ,public WarListener
{
public:


public:

	WarModeTwo(GameState* pGameState);


	virtual ~WarModeTwo();


	/**开始游戏*/
	virtual void start();

	/**游戏结束*/
	virtual	void end();

	/**每帧更新*/
	virtual void update(float time);


	/**点击按下事件*/
	virtual  void beginTouch(int x,int y);

	/**点击离开事件*/
	virtual void  endTouch(int x,int y);

	/**点击移动事件*/
	virtual void  moveTouch(int x,int y);



protected:
	

	///初始化阵形
	void initEmemyFormat();

	///初始化ui游戏开始
	void initUI();

	///销毁ui
	void destroyUI();


	///杀死一队敌人
	virtual void onKillEnemyQueue(EnemyQueue* pEnemyQueue);

	///敌人逃跑
	virtual void onLostEnemyQueue(EnemyQueue* pEnemyQueue);

	///创建新敌人
	virtual void onCrateEnemyQueue(EnemyQueue* pEnemyQueue);


	void createEnemyQueue()
	{
		m_needCreate=true;

	}

	///内部方法用来创建队列
	void   _createEnemyQueue();


	/**更新重力计数据，控制摄像头运动*/
	virtual void updateAccelerometer();


protected:

	//Enemy* m_pEnemy;

	UIWarModeTwo*           m_pUI;///比赛的ui界面
	UIBase*                 m_pUIBalance;///结算界面
	Ogre::SceneManager*     m_pSceneMrg;
	unsigned int            m_KillCount;///本次杀死了多少敌人
	unsigned int            m_LostCount;///有多少人跑了


	///阵型列表,共14种队列
	EnemyFormatCollect      m_EnemyFormatCollect;
	bool                    m_needCreate;


	float                m_Minx;        ///最小x轴向角度
	float                m_Maxx;
	float                m_Miny;
	float                m_Maxy;
	float                m_Minz;
	float                m_Maxz;        
	float                m_EnemyLeftTime; ///敌人生命周期



};