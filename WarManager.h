//
//  WarManager.h
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#ifndef WarManager_h_h_h_h
#define WarManager_h_h_h_h


#include <vector>
//#include  "enemy.h"

class Bullet;
class Enemy;
class EnemyQueue;


typedef std::vector<Bullet*> BulletCollect;
typedef std::vector<Enemy*> EnemyCollect;


///战斗监听，用不获取各战斗事件
class WarListener
{
public:
	WarListener(){};
	virtual ~WarListener(){};


	///开始战斗
	//virtual void onWarStart()=0;

	///结整战斗
	//virtual void onWarEnd()=0;



	///杀死一队敌人
	virtual void onKillEnemyQueue(EnemyQueue* pEnemyQueue)=0;

	///敌人逃跑
	virtual void onLostEnemyQueue(EnemyQueue* pEnemyQueue)=0;


	///创建一个新的敌人队列
	virtual void onCrateEnemyQueue(EnemyQueue* pEnemyQueue)=0;


	/**打中一个不应打中的目标*/
	virtual void onHitFriend(Enemy* pEnemy){};


};


typedef std::vector<WarListener*>WarListenerCollect;


class WarManager :public Ogre::Singleton<WarManager>
{

public:
	enum Flag
	{
		F_InWar=1<<1,//在战斗中
		F_EndWar=1<<2,//结束战斗
	};


public:
    
    /**
      *@param pCameraNode 子弹发射的
      */
    WarManager();
    
    ~WarManager();
    
    /*初始化*/
    void init();
    
    
    /**发射子弹*/
    void fire(const Ogre::Vector3& pos,const Ogre::Vector3& dir);

	/**从当前的摄像机位置发射子弹*/
	void fire();
    
    
    void update(float time);
    
    
    ///判断游戏是否结束
    bool isGameEnd();
    
    
    ///战争开始
    void startWar();
    
    ///战争结束
    void endWar();
    

	/**在指定的范围内随机创建一个目标队列
	*@param minxangle   x轴最小出现角度
	*@param maxxangle   x轴最大出现角度
	*@param minyangle   y轴最小出现角度
	*@param maxyangle   y轴最大出现角度
	*@param mindis      z轴最近
	*@param maxdis      z轴最远
	*@param enemylist   敌人信息
	*@param friendlist  友人信息
	%@return 返回创建的目标队列。失败返回NULL
	*/
	EnemyQueue* createEnemyQueue(float minxangle,float maxxangle,float minyangle,float maxyangle,float mindis,float maxdis,
		const std::vector<Ogre::Vector3>& enemyList,
		const std::vector<Ogre::Vector3>& friendList);



	/**添加一个监听器
	*/
	void addListener(WarListener* pwarListen);


	/**移除一个监听器,
	*@remark 只移除不删除
	*/
    void removeListener(WarListener* pWarListen);


	/**回调函数一队敌人死亡
	*内部通知函数不需要主动调用
	*/
	void notifyEnemyQueuDeath(EnemyQueue* pEnemyQueue);


	/**内部通知函数。敌人逃跑
	*内部函数不需要主动调用
	*/
	void notifyEnemyQueuLost(EnemyQueue* pEnemyQueue);


	/**内部函数，通知打中了不应打中的目标*/
	void notifyHitFriend(Enemy* pEnemy);

    
public:



	///检测碰撞
	bool intersectEnemy(Bullet* pBullet);

	///碰撞检测
	void intersectEnemyQueue(Bullet* pBullet);

    
    ///@{
    
    ///创建一个敌人
    Enemy* createEnemy(const Ogre::Vector3& pos);
    
    
    ///通过ogre entityName获取到enemy指针
    Enemy* getEnemyByEntityName(const std::string& name) const ;


	///实际的战争结束
	void _endWar()
	{
		removeFlag(F_EndWar);
		destroyAllBullet();
		destroyAllEnemy();
		destroyAllEnemyQueue();

	}




	/**设置属性*/
	void    setFlag(Flag flag){m_Flag=flag;}
	void    addFlag(Flag roleFlag){m_Flag|=roleFlag;}
	void    removeFlag(Flag roleFlag){m_Flag&=~roleFlag;}
	unsigned int  getFlag()const {return m_Flag;}
	bool    hasFlag(Flag flag) const   {return (m_Flag&flag)!=0;}


protected:
    
    ///销毁所有的敌人
    void  destroyAllEnemy();
    
    ///每帧更新敌人
    void  updateEnemy(float time);

	void updateEnemyQueue(float time);
    
    ///敌人死亡回调
    void  hasEnemyDeath(Enemy* pEnemy);
    
    ///获取一个死记亡单位，如果没有返回空
    Enemy* getDeathEnemy();
    
    
	
    ///@}
    
protected:
    
    void destroyAllBullet();

	/**销毁所有的队列*/
	void destroyAllEnemyQueue();
    
    /**获取一个准备好的子弹,如果没有返回空*/
    Bullet*  getBullet();

	///广播杀死队列消息
	void fireKillEnemyQueue(EnemyQueue* pQueue);

	///广播敌人逃跑消息
	void fireLostEnemyQueue(EnemyQueue* pQueue);

	///广播创建新敌人消息
	void fireCreateEnemyQueue(EnemyQueue* pQueue);
     
    
protected:
    
    
      
    float         m_FireTime;///发射周期
    
    float         m_LastFireTime;///上一张的发射时间
    
    
    BulletCollect      m_BulletCollect;///所有子弹集合
  
    EnemyCollect       m_EnemyCollect;///所有目标的集合

	typedef std::vector<EnemyQueue*> EnemyQueueCollect;
	EnemyQueueCollect m_EnemyQueueCollect;

	EnemyQueueCollect  m_DeleteEnemyQueueCollect;
    
    Ogre::SceneManager*   m_pSceneMrg;
	WarListenerCollect    m_listenerCollect;  ///临听器容器

	unsigned int          m_Flag;            //设置标记
    
};






#endif