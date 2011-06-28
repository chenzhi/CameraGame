//
//  BulletManager.h
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#ifndef BulletManager_h_h_h_h
#define BulletManager_h_h_h_h


#include <vector>
//#include  "enemy.h"

class Bullet;
class Enemy;

typedef std::vector<Bullet*> BulletCollect;
typedef std::vector<Enemy*> EnemyCollect;

class BulletManager :public Ogre::Singleton<BulletManager>
{
public:
    
    /**
      *@param pCameraNode 子弹发射的
      */
    BulletManager();
    
    ~BulletManager();
    
    /*初始化*/
    void init();
    
    
    /**发射子弹*/
    void fire(const Ogre::Vector3& pos,const Ogre::Vector3& dir);
    
    
    void update(float time);
    
    
    
    
public:
    
    ///@{
    
    ///创建一个敌人
    Enemy* createEnemy(const Ogre::Vector3& pos);
    
    
    ///通过ogre entityName获取到enemy指针
    Enemy* getEnemyByEntityName(const std::string& name) const ;
    
    ///销毁所有的敌人
    void  destroyAllEnemy();
    
    
    ///每帧更新敌人
    void  updateEnemy(float time);
    
    
    
    ///@}
    
protected:
    
    void destroy();
    
    /**获取一个准备好的子弹,如果没有返回空*/
    Bullet*  getBullet();
    
    
protected:
    
    
      
    float         m_FireTime;///发射周期
    
    float         m_LastFireTime;///上一张的发射时间
    
    
    BulletCollect      m_BulletCollect;///所有子弹集合
    
    
    EnemyCollect       m_EnemyCollect;///所有目标的集合
    
    Ogre::SceneManager*   m_pSceneMrg;
    
};






#endif