//
//  enemy.cpp
//  ogreApp
//
//  Created by thcz on 11-6-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//







#include "enemy.h"
#include  "bulletManager.h"

int Enemy::m_EntityIndex=0;

//------------------------------------------
Enemy::Enemy(const Ogre::String& meshName,const Ogre::Vector3& pos, Ogre::SceneManager* pSceneMrg)
:m_pEntity(NULL),m_pNode(NULL),m_pSceneMrg(pSceneMrg),m_pAniSate(NULL),m_LeftValue(100),m_State(ES_NORMAL),m_Rotate(0)
{
    
    m_pEntity=m_pSceneMrg->createEntity("Enemy"+Ogre::StringConverter::toString(m_EntityIndex++),meshName);
    m_pNode=pSceneMrg->getRootSceneNode()->createChildSceneNode();
    m_pNode->attachObject(m_pEntity);
    m_pNode->setPosition(pos);
    
    m_pNode->showBoundingBox(true);
    
    m_pEntity->setQueryFlags(EnemyMask);
    
    
    m_pAniSate=m_pEntity->getAnimationState("auto");
    m_pAniSate->setLoop(false);
    
    m_pMaterial=Ogre::MaterialManager::getSingleton().getByName("Material_#30_Material_#0_B");
    
    
    
}

//------------------------------------------
Enemy::~Enemy()
{
    destroy();
    
}

//------------------------------------------
void Enemy::onHit(const Ogre::Vector3& hitPos,Bullet* pBullet )
{
    m_LeftValue-=35;
    if(m_LeftValue<=0)
    {
        m_State=ES_DEATH;
        death();
        return ;
    }
    
    
    ///如果被击中未成亡进入躲避状态
    m_State=ES_DODGE;
    if(m_pAniSate->getEnabled()==false||m_pAniSate->hasEnded()==true)
    {
     m_pAniSate->setEnabled(true);
     m_pAniSate->setTimePosition(0);
    }
    
    
    
    ///计算旋转角度和旋转方向
    Ogre::Vector3 CurrentPos=m_pNode->_getDerivedPosition();
    m_pNode->_updateBounds();
    const Ogre::AxisAlignedBox& box=m_pNode->_getWorldAABB();
    
    float tem=box.getMaximum().x-box.getMinimum().x;
    tem*=0.5f;
    m_Rotate+=(hitPos.x-CurrentPos.x)/tem*Ogre::Math::PI*10;///如果击中最左边就旋转5周
    
    
    Ogre::Vector3 center=box.getCenter();
    Ogre::Vector3 dir=center-hitPos;
   
    
    dir.y*=10;
    dir.y+=2;
    
    

    m_Trans=m_Trans+dir;
    //m_Trans.z=0;
   // m_Trans.x=0;
    
    
    //sprintf(strtem,"m_Trans+dir  is x:%.2f y:%.2f z:%.2f",m_Trans.x,m_Trans.y,m_Trans.z);
   // Ogre::LogManager::getSingleton().logMessage(strtem);

    
    
    ///改变颜色
    if(m_pMaterial.isNull()==false)
    {
        if(m_LeftValue>60)
        {
            m_pMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0.0,1.0f, 0.0f);

            
        }else if(m_LeftValue>10)
        {
            m_pMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1.0f, 0.0f, 0.0f);

        }
    }

    
    
    
    
}

//------------------------------------------
void Enemy::destroy()
{
    if(m_pSceneMrg!=NULL)
    {
    
        
        if(m_pNode!=NULL)
        {
            m_pNode->detachAllObjects();
            m_pNode->getParentSceneNode()->removeAndDestroyChild(m_pNode->getName());

        }
        
        if(m_pEntity!=NULL)
        {
            m_pSceneMrg->destroyEntity(m_pEntity);
        }
    }
    
}

//------------------------------------------
void Enemy::setVisible(bool b)
{
    if(m_pNode!=NULL)
    {
        m_pNode->setVisible(b);
    }
}


//------------------------------------------
void Enemy::update(float time)
{
    
    if(m_State==ES_NORMAL)
    {
        updateNormal(time);
    }else if(m_State==ES_DODGE)
    {
        updateDodge(time);
    }else if(m_State==ES_DEATH)
    {
        updateDeath(time);
    }
    
    return ;
}

//------------------------------------------
const std::string& Enemy::getEntityName()const
{
    assert(m_pEntity);
    return m_pEntity->getName();
}

//------------------------------------------
void Enemy::death()
{
    
       
    
    m_State=ES_DEATH;
    m_pEntity->setVisible(false);
    
    
    BulletManager::getSingleton().hasEnemyDeath(this);

    
    return ;
}


//---------------------------------------------------
void Enemy::updateNormal(float time)
{
    
     

    return ;
}

//---------------------------------------------------
void Enemy::updateDodge(float time)
{
    
    if(m_pAniSate->getEnabled()==true)
    {
        m_pAniSate->addTime(time);
    }
    
    ///如果目标点低于-5那么游戏结速
    if(m_pNode->_getDerivedPosition().y<-5)
    {
        BulletManager::getSingleton().endWar();
        return ;
    }
    
    
 
    
    
    ///旋转速度为每秒
    float ra=m_Rotate*0.3f*time;
    m_pNode->rotate(Ogre::Vector3(0,0,1), Ogre::Radian(ra));
    m_Rotate-=ra;
    
    
    ////移动
    Ogre::Vector3 tr=m_Trans*0.3f*time;
    //m_pNode->translate(tr,Ogre::Node::TS_WORLD);
    m_Trans-=tr;
 
   
    
    
    float speed=1.0f;
    Ogre::Vector3 gravity(0,-1,0);
    gravity=gravity*speed*time;
    gravity+=tr;
    m_pNode->translate(gravity,Ogre::Node::TS_WORLD);
    
    
    Ogre::Vector3 pos=m_pNode->_getDerivedPosition();
    
       
    //sprintf(strtem,"head pos  is x:%.2f y:%.2f z:%.2f",pos.x,pos.y,pos.z);
    //Ogre::LogManager::getSingleton().logMessage(strtem);


    return ;
}

//---------------------------------------------------
void Enemy::updateDeath(float time)
{
    
    
    return ;
    
}

//-----------------------------------------------------
void Enemy::reset(const Ogre::Vector3& pos)
{
    
    
    m_pEntity->setVisible(true);
    m_pNode->resetOrientation();
    m_pNode->setPosition(pos);

    if(m_pMaterial.isNull()==false)
    {
        m_pMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0.0f, 0.0f, 0.0f);
    }
    
    
    ///重置动画
    if (m_pAniSate!=NULL)
    {
        m_pAniSate->setTimePosition(0);
    }
    
    
    m_LeftValue=100;
    m_State=ES_NORMAL;
    m_Rotate=0;
    m_Trans.x=m_Trans.y=m_Trans.z=0.0f;
    
    
    return  ;
}