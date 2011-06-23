//
//  BulletManager.cpp
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "BulletManager.h"
#include  "Bullet.h"
namespace Ogre 
{
template<> BulletManager* Ogre::Singleton<BulletManager>::ms_Singleton=NULL;
}



//---------------------------------------------------
BulletManager::BulletManager()
{
    init();
}

//---------------------------------------------------
BulletManager::~BulletManager()
{
    destroy();
}


//---------------------------------------------------
void BulletManager::init()
{
    for(int i=0; i<10; ++i)
    {
        m_BulletCollect.push_back(new Bullet());
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