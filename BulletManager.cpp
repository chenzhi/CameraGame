//
//  BulletManager.cpp
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "BulletManager.h"
#include  "Bullet.h"
#include  "Application.h"
#include  "enemy.h"


namespace Ogre 
{
template<> BulletManager* Ogre::Singleton<BulletManager>::ms_Singleton=NULL;
}



//---------------------------------------------------
BulletManager::BulletManager()
:m_pSceneMrg(NULL)
{
    
    m_pSceneMrg=Application::getSingleton().getMainSceneManager();
    init();
}

//---------------------------------------------------
BulletManager::~BulletManager()
{
    destroy();
    destroyAllEnemy();
}


//---------------------------------------------------
void BulletManager::init()
{
    for(int i=0; i<10; ++i)
    {
        m_BulletCollect.push_back(new Bullet(m_pSceneMrg));
    }
    
}


//---------------------------------------------------
void BulletManager::fire(const Ogre::Vector3& pos,const Ogre::Vector3& dir)
{
    Bullet* pBullet=getBullet();
    if(pBullet!=NULL)
    {
        pBullet->shoot(pos, dir);
    }
    
    return ;
    
}

//---------------------------------------------------
void BulletManager::update(float time)
{
    size_t size=m_BulletCollect.size();
    for(size_t i=0;i<size;++i)
    {
        m_BulletCollect[i]->update(time);
    }
    
    
    updateEnemy(time);
    
    return ;
}


//---------------------------------------------------
void BulletManager::destroy()
{
    size_t size=m_BulletCollect.size();
    for(size_t i=0;i<size;++i)
    {
        delete m_BulletCollect[i];
    }
    
    m_BulletCollect.clear();
}

//---------------------------------------------------
Bullet* BulletManager::getBullet()
{
    size_t size=m_BulletCollect.size();
    for(size_t i=0;i<size;++i)
    {
        if(m_BulletCollect[i]->getState()==Bullet::BS_NONE)
        {
            return m_BulletCollect[i];
        }
    }
    
    return NULL;

}

//---------------------------------------------------
Enemy* BulletManager::createEnemy(const Ogre::Vector3& pos)
{
    Enemy* pEnemy=  new Enemy("CameraHead.mesh",pos,m_pSceneMrg);
    
    m_EnemyCollect.push_back(pEnemy);
    
    return pEnemy;
}


//---------------------------------------------------
Enemy* BulletManager::getEnemyByEntityName(const std::string& name) const 
{
    EnemyCollect::const_iterator it=m_EnemyCollect.begin();
    EnemyCollect::const_iterator endit=m_EnemyCollect.end();
    
    for(;it!=endit;++it)
    {
        if( (*it)->getEntityName()==name)
        {
            return *it;
        }
    }
    
    return NULL;
}

//---------------------------------------------------
void  BulletManager::destroyAllEnemy()
{
    EnemyCollect::const_iterator it=m_EnemyCollect.begin();
    EnemyCollect::const_iterator endit=m_EnemyCollect.end();
    
    for(;it!=endit;++it)
    {
        delete (*it);
    }
    m_EnemyCollect.clear();
    return ;
}


///每帧更新敌人
void  BulletManager::updateEnemy(float time)
{
    EnemyCollect::const_iterator it=m_EnemyCollect.begin();
    EnemyCollect::const_iterator endit=m_EnemyCollect.end();
    
    for(;it!=endit;++it)
    {
        (*it)->update(time);
    }
    return ;
}
