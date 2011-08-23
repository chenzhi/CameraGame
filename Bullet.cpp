//
//  Bullet.cpp
//  ogreApp
//
//  Created by thcz on 11-6-21.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "Bullet.h"
#include  "Application.h"
#include  "WarManager.h"



//-----------------------------------------------------------------------
Bullet::Bullet(Ogre::SceneManager* pSceneMrg)
:m_pEntity(NULL),m_pNode(NULL),m_Gravity(0.0f,-0.98f*0.5f,0.0f),m_OrigiPosition(0.0f,0.0f,0.0f),
m_Dir(0.0f,0.0f,-1.0f),m_Force(10),m_LiftTime(1.5f),m_CurrentTime(0),m_State(BS_NONE),m_Speed(0.1f),
m_pSceneMrg(pSceneMrg)
{
    //Ogre::SceneManager* pSceneMrg= Application::getSingleton().getMainSceneManager();
    assert(m_pSceneMrg);
    
    m_pEntity=m_pSceneMrg->createEntity("zidan.mesh");
    ///支除所有的查询标志。
    m_pEntity->setQueryFlags(0);
    m_pNode=m_pSceneMrg->getRootSceneNode()->createChildSceneNode();
    m_pNode->attachObject(m_pEntity);
    
    ///默认不显示
    m_pNode->setVisible(false);
  //  m_pNode->setScale(Ogre::Vector3(0.003f,0.003f,0.003f));
    
    
}


//-----------------------------------------------------------------------
Bullet::~Bullet()
{
    destroy();
}


/**设置击中标记,计算反射*/
void Bullet::hitTarget()
{

	//反射公式R r = R i - 2 N (R i . N)
	//                    2(n.l)n - l

	Ogre::Vector3 vn(0.0f,0.0f,1.0f);

	Ogre::Vector3 r;
	r=(2.0f*(-m_Dir).dotProduct(vn))*vn+m_Dir;
    r.normalise();
	m_Force*=0.65f;
	//m_Speed*=0.5f;
	//r*=0.001f;
	setBulletDir(r);
	return ;
}


/**返回上一帧时间度的射线和长度*/
bool Bullet::getFrameRay(Ogre::Ray& ray,float& lenght)
{
	if(m_State==BS_NONE)
		return false;

	ray=m_ray;
	lenght=m_raylenght;
	return true;
}


//-----------------------------------------------------------------------
bool  Bullet::update(float time)
{
    if(m_State==BS_NONE)
        return  false;
    
    m_CurrentTime+=time;
    
    ///重力加动力的向量是子弹发行的方向
    float temForce=m_Force*((m_LiftTime-m_CurrentTime)/m_LiftTime);
    Ogre::Vector3 power=m_Dir*temForce;
    power+=m_Gravity;
    
    power*=m_CurrentTime*m_Speed;
    
    
    Ogre::Vector3 dir=power.normalisedCopy();    
    
   // updateHit(m_pNode->getPosition(), dir, power.length());

	//Ogre::Ray ray(m_pNode->getPosition(),dir);


	///如果击中了目标，子弹就会向下掉
	//if(WarManager::getSingleton().intersectEnemy(ray,power.length()))
	//{
    //  return ;
		
	//}
    

	m_ray.setOrigin(m_pNode->getPosition());
	m_ray.setDirection(dir);
	m_raylenght=power.length();
    
    m_pNode->translate(power,Ogre::Node::TS_WORLD);

    
    
    
    ////如果超过生命周期就重置
    if(m_CurrentTime>m_LiftTime)
    {
        reset();
    }
    
    
	return true;
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
    
    //if(m_pRayQuery!=NULL)
    //{
    //    m_pSceneMrg->destroyQuery(m_pRayQuery);
    //    m_pRayQuery=NULL;
    //}
    //

}

//-----------------------------------------------------------------------
void Bullet::reset()
{
    m_State=BS_NONE;
    m_CurrentTime=0.0f;
    m_pNode->setVisible(false);
	m_Speed=0.1f;
	m_Force=10.0f;


}

//-----------------------------------------------
/*/
void Bullet::updateHit(const Ogre::Vector3& pos,const Ogre::Vector3& dir,float length)
{
  
    //Ogre::LogManager::getSingleton().logMessage("begin hit");
    
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

    
   // Ogre::LogManager::getSingleton().logMessage("end hit  1");
    if(result.empty())
    {
        //Ogre::LogManager::getSingleton().logMessage("can't hit can't pick any object");
        return ;
    }
    
    
    
    Ogre::RaySceneQueryResultEntry pickEnemy=result.at(0);
    if(result.size()>1)
    {
        Ogre::String name0=result.at(0).movable->getName();
        Ogre::String name1=result.at(1).movable->getName();
        name0+=name1;
        
    }
    
    //Ogre::LogManager::getSingleton().logMessage("end hit 2");
    if(pickEnemy.distance>length)
    {
        
       // char log[256];
       // sprintf(log,"it is to length,position is :x:%.3f y:%.3f z:%.3f  length is %f",pos.x,pos.y,pos.z,length);
        
        //Ogre::LogManager::getSingleton().logMessage(log);
        return ;
    }
    
    
    //Ogre::LogManager::getSingleton().logMessage("end hit 3");
    Enemy* pEnemy=WarManager::getSingleton().getEnemyByEntityName(pickEnemy.movable->getName());
    if(pEnemy==NULL)
    {
        Ogre::LogManager::getSingleton().logMessage("can not find ememy pick object name is "+pickEnemy.movable->getName());
        return ;
    }
    
   // Ogre::LogManager::getSingleton().logMessage("end hit 4");
    
    Ogre::Vector3 hitPos=pos+dir*pickEnemy.distance;
    
    pEnemy->onHit(hitPos, this);
    
    //Ogre::LogManager::getSingleton().logMessage("hit enemy");
    
    ///击中后重置子弹
    reset();
    
    return;
    
    

    
}
//*/