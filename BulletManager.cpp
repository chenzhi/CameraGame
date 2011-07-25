//
//  BulletManager.cpp
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011Äê __MyCompanyName__. All rights reserved.
//
#include "pch.h"
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
:m_pSceneMrg(NULL),m_GameBegan(false)
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
    
    if(m_GameBegan==false)
    {
        return ;
    }

    
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
bool  BulletManager::intersectEnemy(const Ogre::Ray& ray,float lenght)
{
	EnemyCollect::iterator it=m_EnemyCollect.begin();
	EnemyCollect::iterator itend=m_EnemyCollect.end();

	for(;it!=itend;++it)
	{
		if((*it)->intersectRay(ray,lenght))
			return true;
	}
	 
	return false;

}

//---------------------------------------------------
Enemy* BulletManager::createEnemy(const Ogre::Vector3& pos)
{
    
   // for(int i=-5;i<5;++i)
    {
      //  for(int j=-5;j<5;++j)
        {
            //Ogre::Vector3 temPos(i,j,0);
			Ogre::Vector3 temPos=pos;
            Enemy* pEnemy=  new Enemy("face_shou.mesh",temPos,m_pSceneMrg->getRootSceneNode());
            pEnemy->reset(temPos);
            
            m_EnemyCollect.push_back(pEnemy);

            
        }
    }
    
    
       
    return m_EnemyCollect[0];
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


//----------------------------------------------
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

//----------------------------------------------
void  BulletManager::hasEnemyDeath(Enemy* pEnemy)
{
    pEnemy->reset(Ogre::Vector3(0,0,0));
    return ;
}

//------------------------------------------------
bool BulletManager::isGameEnd()
{
    
    return !m_GameBegan;
    
}

//-------------------------------------------------
void BulletManager::startWar()
{
    m_GameBegan=true;

    BulletManager::getSingleton().createEnemy(Ogre::Vector3(0,0,0));

    return ;
}

//------------------------------------------------
void BulletManager::endWar()
{
    m_GameBegan=false;

    return ;
}

//---------------------------------------------------
Enemy* BulletManager::getDeathEnemy()
{
    
    EnemyCollect::iterator it=m_EnemyCollect.begin();
    EnemyCollect::iterator endit=m_EnemyCollect.end();
    for(;it!=endit;++it)
    {
        if((*it)->getState()==Enemy::ES_DEATH)
        {
            return *it;
        }
    }
    
    return NULL;
}