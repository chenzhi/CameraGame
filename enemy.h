//
//  enemy.h
//  ogreApp
//
//  Created by thcz on 11-6-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once

class Bullet;


#define EnemyMask 0x0100



class Enemy
{
    
public:
    
    enum EnemyState
    {
        ES_NORMAL, ///出现，未受伤时状态
        ES_DODGE, ////受伤后躲避
        ES_DEATH, ///死亡状态
    };
    
    
    
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
    
    
    ///获取生命值
    float getLeftValue()const{return m_LeftValue;}
        
    ///设置生命值
    void  setLeftValue(float value){m_LeftValue=value;}

    
    ///重置,在指定的位置重新出现
    void reset(const Ogre::Vector3& pos);
    
    ///获取状态
    EnemyState getState()const {return m_State;}    

protected:
    
    ///死亡
    void death();
    
    ///消毁
    void destroy();
    
    
    ///更新出现时
    void updateNormal(float time);
    
    ///
    void updateDodge(float time);
    
    ///
    void updateDeath(float time);
    
    
    
    Ogre::Entity*     m_pEntity;
    Ogre::SceneNode*  m_pNode;
    Ogre::SceneManager* m_pSceneMrg;
    
    
    Ogre::AnimationState* m_pAniSate;
    
    static int     m_EntityIndex;
    
    
    float        m_LeftValue;///生命值
    
    EnemyState      m_State;///状态
    
    
    ///被击中后的旋转 
    float         m_Rotate;
    
    ///被击中后向哪个方向运动多
    Ogre::Vector3     m_Trans;
    
    Ogre::MaterialPtr    m_pMaterial;


	Ogre::Entity*        m_pHeadEnity;
    
    
    
};