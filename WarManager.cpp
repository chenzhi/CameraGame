//
//  WarManager.cpp
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "WarManager.h"
#include  "Bullet.h"
#include  "Application.h"
#include  "enemy.h"
#include "Config.h"
#include "EnemyQueue.h"
#include "Application.h"

namespace Ogre 
{
template<> WarManager* Ogre::Singleton<WarManager>::ms_Singleton=NULL;
}



//---------------------------------------------------
WarManager::WarManager()
:m_pSceneMrg(NULL),m_GameBegan(false)
{
    
    m_pSceneMrg=Application::getSingleton().getMainSceneManager();
    init();
}

//---------------------------------------------------
WarManager::~WarManager()
{
    destroyAllBullet();
    destroyAllEnemy();

	destroyAllEnemyQueue();


}


//---------------------------------------------------
void WarManager::init()
{
    for(int i=0; i<10; ++i)
    {
        m_BulletCollect.push_back(new Bullet(m_pSceneMrg));
    }
    
       
}

//---------------------------------------------------
void WarManager::fire()
{
	Bullet* pBullet=getBullet();
	if(pBullet==NULL)
		return ;
	Ogre::SceneNode* pCameraNode=Application::getSingleton().getMainCamera()->getParentSceneNode();
	Ogre::Matrix3 matrix= pCameraNode->getLocalAxes();
	Ogre::Vector3  pos=pCameraNode->getPosition();


	Ogre::Vector3 dir(matrix[0][2],matrix[1][2],matrix[2][2]);
	dir.normalise();
	pos-=dir*2;
	pos.y-=0.5f;

	dir.y-=0.15f;
	dir.normalise();

	///子弹发送时稍稍向上发送一点
	//dir.y-=0.15;
	//dir.normalise();
	fire(pos,dir);

}


//---------------------------------------------------
void WarManager::fire(const Ogre::Vector3& pos,const Ogre::Vector3& dir)
{
    Bullet* pBullet=getBullet();
    if(pBullet!=NULL)
    {
        pBullet->shoot(pos, dir);
    }
    
    return ;
    
}

//---------------------------------------------------
void WarManager::update(float time)
{
    
    if(m_GameBegan==false)
    {
        return ;
    }

    ///更新所有的子弹
    size_t size=m_BulletCollect.size();
	Ogre::Ray ray;
	float rayLenght=0.0f;
    for(size_t i=0;i<size;++i)
    {
		///如果子弹是发射状态就做碰撞检测
        if(m_BulletCollect[i]->update(time))
		{
			intersectEnemyQueue(m_BulletCollect[i]);

		}


    }
    
    
    updateEnemy(time);
	updateEnemyQueue(time);
    
    return ;
}


//---------------------------------------------------
void WarManager::destroyAllBullet()
{
    size_t size=m_BulletCollect.size();
    for(size_t i=0;i<size;++i)
    {
        delete m_BulletCollect[i];
    }
    
    m_BulletCollect.clear();
}

//--------------------------------------------------
void WarManager::destroyAllEnemyQueue()
{

	size_t size=m_EnemyQueueCollect.size();
	for(size_t i=0;i<size;++i)
	{
      delete m_EnemyQueueCollect[i];
	}
	m_EnemyQueueCollect.clear();







}

//---------------------------------------------------
Bullet* WarManager::getBullet()
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
bool  WarManager::intersectEnemy(Bullet* pBullet)
{
	EnemyCollect::iterator it=m_EnemyCollect.begin();
	EnemyCollect::iterator itend=m_EnemyCollect.end();

	for(;it!=itend;++it)
	{
	//	//if((*it)->intersectRay(ray,lenght))
		//	return true;
	}
	 
	return false;

}

void  WarManager::intersectEnemyQueue(Bullet* pBullet)
{

	EnemyQueueCollect::iterator it=m_EnemyQueueCollect.begin();
	EnemyQueueCollect::iterator itend=m_EnemyQueueCollect.end();

	for(;it!=itend;++it)
	{
		(*it)->updateCollision(pBullet);
	}

	return ;

}

//---------------------------------------------------
Enemy* WarManager::createEnemy(const Ogre::Vector3& pos)
{
    
   // for(int i=-5;i<5;++i)
  
      //  for(int j=-5;j<5;++j)
     
            //Ogre::Vector3 temPos(i,j,0);
			Ogre::Vector3 temPos=pos;
			const Ogre::String& faceMesh=g_userInformation.getFaceMode();
			const Ogre::String& headMesh=g_userInformation.getHeadMode();
            Enemy* pEnemy=  new Enemy(faceMesh,headMesh,temPos,m_pSceneMrg->getRootSceneNode());
            pEnemy->reset(temPos);
            
            m_EnemyCollect.push_back(pEnemy);

 
    
    return pEnemy;
}


//---------------------------------------------------
Enemy* WarManager::getEnemyByEntityName(const std::string& name) const 
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
void  WarManager::destroyAllEnemy()
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
void  WarManager::updateEnemy(float time)
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
void  WarManager::hasEnemyDeath(Enemy* pEnemy)
{
   // pEnemy->reset(Ogre::Vector3(0,0,0));
    return ;
}

//------------------------------------------------
bool WarManager::isGameEnd()
{
    
    return !m_GameBegan;
    
}

//-------------------------------------------------
void WarManager::startWar()
{
    m_GameBegan=true;

    return ;
}

//------------------------------------------------
void WarManager::endWar()
{
    m_GameBegan=false;

    return ;
}

//---------------------------------------------------
Enemy* WarManager::getDeathEnemy()
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


//---------------------------------------------------------
void WarManager::notifyEnemyQueuDeath(EnemyQueue* pEnemyQueue)
{
	fireKillEnemyQueue(pEnemyQueue);
	///创建一个新的队列

	m_DeleteEnemyQueueCollect.push_back(pEnemyQueue);

	return ;

}

//---------------------------------------------------------
void WarManager::notifyEnemyQueuLost(EnemyQueue* pEnemyQueue)
{
	fireLostEnemyQueue(pEnemyQueue);
	
	///如果有三个以上的敌人
	m_DeleteEnemyQueueCollect.push_back(pEnemyQueue);

	return ;

}

//---------------------------------------------------------
EnemyQueue* WarManager::createEnemyQueue(float xangle,float yangle,const std::vector<Ogre::Vector3>& enemyList,
										 const std::vector<Ogre::Vector3>& friendList)
{
	Ogre::Camera* pCamera=Application::getSingleton().getMainCamera();

	 xangle=Ogre::Math::RangeRandom(-xangle,xangle);
	 yangle=Ogre::Math::RangeRandom(-yangle,yangle);


	 Ogre::Radian xRadian=Ogre::Degree(xangle);
	 Ogre::Radian yRadian=Ogre::Degree(yangle);

	 float x=Ogre::Math::Sin(xRadian.valueRadians());
	 float z=Ogre::Math::Cos(xRadian.valueRadians());
	 float y=Ogre::Math::Sin(yRadian.valueRadians());


	 Ogre::Vector3 pos(x,y,z);
	 pos.normalise();
	 pos.x*=5.0f;
	 pos.y*=5.0f;
	 pos.z=Ogre::Math::RangeRandom(0.0f,-8.0f);
    

	 //PositionList Enemylist;
  //   Enemylist.push_back(Ogre::Vector3(2.0f,0.0f,0.0f));
	 //Enemylist.push_back(Ogre::Vector3(-2.0f,0.0f,0.0f));

	 //PositionList FriendList;
	 //FriendList.push_back(Ogre::Vector3(0.0f,0.0f,0.0f));


	 EnemyQueue* pQueue=new EnemyQueue(pos,enemyList,friendList);
     m_EnemyQueueCollect.push_back(pQueue);

	 fireCreateEnemyQueue(pQueue);

	 return pQueue;

}

//---------------------------------------------------------
void  WarManager::updateEnemyQueue(float time)
{

	///先把需要删除的都删除
	if(m_DeleteEnemyQueueCollect.empty()==false)
	{
		EnemyQueueCollect::iterator deleteIt=m_DeleteEnemyQueueCollect.begin();
		EnemyQueueCollect::iterator deleteEndIt=m_DeleteEnemyQueueCollect.end();
		for(;deleteIt!=deleteEndIt;++deleteIt)
		{
			EnemyQueueCollect::iterator temIt=std::find(m_EnemyQueueCollect.begin(),m_EnemyQueueCollect.end(),(*deleteIt));
			if(temIt!=m_EnemyQueueCollect.end())
			{
				delete (*temIt);
				m_EnemyQueueCollect.erase(temIt);
				
			}

		}
		m_DeleteEnemyQueueCollect.clear();

	}



	EnemyQueueCollect::iterator it=m_EnemyQueueCollect.begin();
	EnemyQueueCollect::iterator endit=m_EnemyQueueCollect.end();
	for(;it!=endit;++it)
	{
		(*it)->update(time);
	}

	return ;

}

//---------------------------------------------------------
void WarManager::addListener(WarListener* pwarListen)
{
	if(pwarListen==NULL)
		return ;
	///如果已经加入了就不再加入
	WarListenerCollect::iterator it=m_listenerCollect.begin();
	WarListenerCollect::iterator itend=m_listenerCollect.end();

	for(;it!=itend;++it)
	{
		if((*it)==pwarListen)
		{
			return ;
		}
	}

	m_listenerCollect.push_back(pwarListen);
	return ;

}


//----------------------------------------------------------------
void WarManager::removeListener(WarListener* pWarListen)
{
	if(pWarListen==NULL)
		return ;
	
	WarListenerCollect::iterator it=m_listenerCollect.begin();
	WarListenerCollect::iterator itend=m_listenerCollect.end();

	for(;it!=itend;++it)
	{
		if((*it)==pWarListen)
		{
			m_listenerCollect.erase(it);
			return ;
		}
	}

	return ;
}

//----------------------------------------------------------------
void WarManager::fireKillEnemyQueue(EnemyQueue* pQueue)
{

	WarListenerCollect::iterator it=m_listenerCollect.begin();
	WarListenerCollect::iterator itend=m_listenerCollect.end();

	for(;it!=itend;++it)
	{
	  (*it)->onKillEnemyQueue(pQueue);
	}


	return ;

}



//----------------------------------------------------------------
void WarManager::fireLostEnemyQueue(EnemyQueue* pQueue)
{
	WarListenerCollect::iterator it=m_listenerCollect.begin();
	WarListenerCollect::iterator itend=m_listenerCollect.end();

	for(;it!=itend;++it)
	{
		(*it)->onLostEnemyQueue(pQueue);
	}
	return ;

}

//----------------------------------------------------------------
void  WarManager::fireCreateEnemyQueue(EnemyQueue* pQueue)
{

	WarListenerCollect::iterator it=m_listenerCollect.begin();
	WarListenerCollect::iterator itend=m_listenerCollect.end();

	for(;it!=itend;++it)
	{
		(*it)->onCrateEnemyQueue(pQueue);
	}
	return ;



}