//
//  enemy.cpp
//  ogreApp
//
//  Created by thcz on 11-6-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//







#include "enemy.h"

int Enemy::m_EntityIndex=0;

//------------------------------------------
Enemy::Enemy(const Ogre::String& meshName,const Ogre::Vector3& pos, Ogre::SceneManager* pSceneMrg)
:m_pEntity(NULL),m_pNode(NULL),m_pSceneMrg(pSceneMrg),m_pAniSate(NULL)
{
    
    m_pEntity=m_pSceneMrg->createEntity("Enemy"+Ogre::StringConverter::toString(m_EntityIndex++),meshName);
    m_pNode=pSceneMrg->getRootSceneNode()->createChildSceneNode();
    m_pNode->attachObject(m_pEntity);
    m_pNode->setPosition(pos);
    
    m_pEntity->setQueryFlags(EnemyMask);
    
    
    m_pAniSate=m_pEntity->getAnimationState("smile");
    m_pAniSate->setLoop(false);
    
    
}

//------------------------------------------
Enemy::~Enemy()
{
    
}

//------------------------------------------
void Enemy::onHit(const Ogre::Vector3& hitPos,Bullet* pBullet )
{
    m_pAniSate->setEnabled(true);
    m_pAniSate->setTimePosition(0);
    
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
    if(m_pAniSate->getEnabled()==true)
    {
        
        m_pAniSate->addTime(time);
        
    }
    
    return ;
}

//------------------------------------------
const std::string& Enemy::getEntityName()const
{
    assert(m_pEntity);
    return m_pEntity->getName();
}