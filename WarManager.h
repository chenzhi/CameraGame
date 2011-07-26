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

class WarManager :public Ogre::Singleton<WarManager>
{
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
	*@param xangle 摄像机x轴左右xangle角度范围以内,角度值
	*@param yangle 摄像机y轴上下yangle角度范围以内
	%@return 返回创建的目标队列。失败返回NULL
	*/
	EnemyQueue* createEnemyQueue(float xangle,float yangle);
    
    
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
    
    ///销毁所有的敌人
    void  destroyAllEnemy();
    
    ///每帧更新敌人
    void  updateEnemy(float time);

	void updateEnemyQueue(float time);
    
    ///敌人死亡回调
    void  hasEnemyDeath(Enemy* pEnemy);
    
    ///获取一个死记亡单位，如果没有返回空
    Enemy* getDeathEnemy();
    
    
	///回调函数一队敌人死亡
	void notifyEnemyQueuDeath(EnemyQueue* pEnemyQueue);
    
    ///@}
    
protected:
    
    void destroyAllBullet();

	/**销毁所有的队列*/
	void destroyAllEnemyQueue();
    
    /**获取一个准备好的子弹,如果没有返回空*/
    Bullet*  getBullet();
    
    
protected:
    
    
      
    float         m_FireTime;///发射周期
    
    float         m_LastFireTime;///上一张的发射时间
    
    
    BulletCollect      m_BulletCollect;///所有子弹集合
  
    EnemyCollect       m_EnemyCollect;///所有目标的集合

	typedef std::vector<EnemyQueue*> EnemyQueueCollect;
	EnemyQueueCollect m_EnemyQueueCollect;
    
    Ogre::SceneManager*   m_pSceneMrg;
    
    
    bool            m_GameBegan;
    
};






#endif