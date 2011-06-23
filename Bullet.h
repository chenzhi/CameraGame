//
//  Bullet.h
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef Bullet_h_h_h_h_
#define Bullet_h_h_h_h_


class Bullet
{
    
    friend class BulletManager;
    protected:
    
    public:
    
    enum BulletState
    {
      BS_NONE,
      BS_SHOOT,
    };

    
    Bullet();
    
    ~Bullet();
    
    
      
  public:  
    ///每帧更新
    void update(float time);
    
    /**发射子弹
       *@param position，发射的初始位置，
       *@param dir    子弹的发射的方向，需要归一化向量
       */
    void shoot(const Ogre::Vector3& position, const Ogre::Vector3& dir);
    
    
    void setliftTime(float time){m_LiftTime=time;}

    
    BulletState getState()const {return m_State;}
    
    protected:
    
    /**销毁*/
    void destroy();
    
    /**重置*/
    void reset();
    
    
protected:
    Ogre::Entity*      m_pEntity;
    Ogre::SceneNode*   m_pNode;
    Ogre::Vector3     m_Gravity;///子弹的重力
    
    Ogre::Vector3     m_OrigiPosition;
    Ogre::Vector3     m_Dir;///子弹发射方向
    float         m_Force; ///动力
    float         m_LiftTime;///生命周期 
    float         m_CurrentTime;///当前生命时期 
    float         m_Speed; ///子弹的速度
    
    BulletState      m_State;
    
};






#endif