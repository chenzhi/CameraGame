//
//  Bullet.cpp
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Bullet.h"
#include  "Application.h"
#include  "BulletManager.h"



//-----------------------------------------------------------------------
Bullet::Bullet(Ogre::SceneManager* pSceneMrg)
:m_pEntity(NULL),m_pNode(NULL),m_Gravity(0.0f,-0.98f,0.0f),m_OrigiPosition(0.0f,0.0f,0.0f),
m_Dir(0.0f,0.0f,-1.0f),m_Force(10),m_LiftTime(1.5f),m_CurrentTime(0),m_State(BS_NONE),m_Speed(1.0f),
m_pSceneMrg(pSceneMrg),m_pRayQuery(NULL)
{
    //Ogre::SceneManager* pSceneMrg= Application::getSingleton().getMainSceneManager();
    assert(m_pSceneMrg);
    
    m_pEntity=m_pSceneMrg->createEntity("cube.mesh");
    m_pNode=m_pSceneMrg->getRootSceneNode()->createChildSceneNode();
    m_pNode->attachObject(m_pEntity);
    
    ///默认不显示
    m_pNode->setVisible(false);
    m_pNode->setScale(Ogre::Vector3(0.01f,0.01f,0.01f));
    
    
}


//-----------------------------------------------------------------------
Bullet::~Bullet()
{
    destroy();
}


//-----------------------------------------------------------------------
void Bullet::update(float time)
{
    if(m_State==BS_NONE)
        return ;
    
    m_CurrentTime+=time;
    
   // Ogre::Vector pos=m_pNode->getPosition();
    
    ///重力加动力的向量是子弹发行的方向
    float temForce=m_Force*((m_LiftTime-m_CurrentTime)/m_LiftTime);
    Ogre::Vector3 power=m_Dir*temForce;
    power+=m_Gravity;
    
    power*=m_CurrentTime*m_Speed;
    
    
    Ogre::Vector3 dir=power.normalisedCopy();    
    
    updateHit(m_pNode->_getDerivedPosition(), power, power.length());
    
    
    m_pNode->translate(power);

    
    
    
    
    ////如果超过生命周期就重置
    if(m_CurrentTime>m_LiftTime)
    {
        reset();
    }
    
    
}

//-----------------------------------------------------------------------
void Bullet::shoot(const Ogre::Vector3& position, const Ogre::Vector3& dir)
{
    ///如果是已经发射的子弹不再发射
    if (m_State==BS_SHOOT)
    {
        Ogre::LogManager::getSingleton().logMessage("Bullet had Shooted");
        return ;
    }
    
    m_State=BS_SHOOT;
    m_OrigiPosition=position;
    m_Dir=-dir;
    
    m_pNode->setVisible(true);
    m_pNode->setPosition(position);
    
       
    
    
    
    
}



//-----------------------------------------------------------------------
void Bullet::destroy()
{
   
    assert(m_pSceneMrg);
    m_pNode->detachAllObjects();
    m_pSceneMrg->destroyEntity(m_pEntity);
    m_pNode->getParentSceneNode()->removeAndDestroyChild(m_pNode->getName());
    
    if(m_pRayQuery!=NULL)
    {
        m_pSceneMrg->destroyQuery(m_pRayQuery);
        m_pRayQuery=NULL;
    }
    

}

//-----------------------------------------------------------------------
void Bullet::reset()
{
    m_State=BS_NONE;
    m_CurrentTime=0.0f;
    m_pNode->setVisible(false);

}

//-----------------------------------------------
void Bullet::updateHit(const Ogre::Vector3& pos,const Ogre::Vector3& dir,float length)
{
  
    Ogre::Ray ray(pos,dir);
    
    if(m_pRayQuery==NULL)
    {
        m_pRayQuery=m_pSceneMrg->createRayQuery(ray);
        m_pRayQuery->setQueryMask(EnemyMask);
        m_pRayQuery->setQueryTypeMask(Ogre::SceneManager::ENTITY_TYPE_MASK);
    }else
    {
        m_pRayQuery->setRay(ray);
    }
    
    m_pRayQuery->setSortByDistance(true);
    
    const Ogre::RaySceneQueryResult& result=m_pRayQuery->execute();

    
    if(result.empty())
    {
        return ;
    }
    
    
    Ogre::RaySceneQueryResultEntry pickEnemy=result.at(0);
    if(pickEnemy.distance>length)
    {
        return ;
    }
    
    
    Enemy* pEnemy=BulletManager::getSingleton().getEnemyByEntityName(pickEnemy.movable->getName());
    if(pEnemy==NULL)
    {
        return ;
    }
    
    
    pEnemy->onHit(Ogre::Vector3(0,0,0), this);
    return;
    
    

    
}