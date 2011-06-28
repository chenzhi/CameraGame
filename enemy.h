//
//  enemy.h
//  ogreApp
//
//  Created by thcz on 11-6-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once

class Bullet;


#define EnemyMask 1000



class Enemy
{
    public:
    
    /**构造函数
     *@param meshName mesh文件名
     *@param pos     出现的初始位
     */
    Enemy(const Ogre::String& meshName,const Ogre::Vector3&  pos, Ogre::SceneManager* pSceneMrg);

    
    ~Enemy();
    
    
    
    /**被打中时的回调
     *@param hitPos 打中的点
     *@param pBullet 打中的子弹
     */
    virtual void onHit(const Ogre::Vector3& hitPos,Bullet* pBullet );
    
    
    ///
    void setVisible(bool b);
    
    
    ///
    void update(float time);
    
    
    
    ///获取名字
    const std::string& getEntityName()const;
    
    

protected:
    
    ///消毁
    void destroy();
    
    
    Ogre::Entity*     m_pEntity;
    Ogre::SceneNode*  m_pNode;
    Ogre::SceneManager* m_pSceneMrg;
    
    
    Ogre::AnimationState* m_pAniSate;
    
    static int     m_EntityIndex;
    
};