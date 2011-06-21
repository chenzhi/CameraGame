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

class Bullet;
typedef std::vector<Bullet*> BulletCollect;

class BulletManager :public Ogre::Singleton<BulletManager>
{
public:
    
    /**
      *@param pCameraNode 子弹发射的摄像机
      */
    BulletManager(Ogre::SceneNode* pCameraNode);
    
    ~BulletManager();
    
    /*初始化*/
    void init();
    
    
    /**发射子弹*/
    void fire(const Ogre::Vector3& pos,const Ogre::Vector3& dir);
    
    
    void update(float time);
    
protected:
    
    void destroy();
    
    /**获取一个准备好的子弹,如果没有返回空*/
    Bullet*  getBullet();
    
    
protected:
    
    
    Ogre::SceneNode*   m_pCameraNode;///发射子弹的摄像机
    
    float         m_FireTime;///发射周期
    
    float         m_LastFireTime;///上一张的发射时间
    
    
    BulletCollect      m_BulletCollect;///所有子弹集合
    
};






#endif