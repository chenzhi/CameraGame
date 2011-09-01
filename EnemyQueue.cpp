#include "pch.h"
#include  "EnemyQueue.h"
#include "Application.h"
#include "Config.h"
#include "Bullet.h"
#include "enemy.h"
#include "WarManager.h"


//-----------------------------------------------------------------
EnemyQueue::EnemyQueue(const Ogre::Vector3& pos,const  PositionList&EnemyList,const PositionList& FriendList )
:m_pSceneMrg(NULL),m_pRootNode(NULL),m_State(EQ_NORMAl),m_currentLeftTime(0.0f),m_leftTime(3.0f)
{

	m_pSceneMrg=Application::getSingleton().getMainSceneManager();
	m_pRootNode=m_pSceneMrg->getRootSceneNode()->createChildSceneNode();
    m_pRootNode->setPosition(pos);
	//m_pRootNode->showBoundingBox(true);

	size_t size=EnemyList.size();
	for(size_t i=0;i<size;++i)
	{
		const Ogre::String& faceMesh=g_userInformation.getFaceMode();
		const Ogre::String& headMesh=g_userInformation.getHeadMode();
		Enemy* pEnemy=new Enemy(faceMesh,headMesh,EnemyList[i],m_pRootNode);
		pEnemy->registerEvent(EE_Hit,&EnemyQueue::notifyEnemyHit,this);

		m_ElemyCollect.push_back(pEnemy);

	}

	size= FriendList.size();
	for(size_t i=0;i<size;++i)
	{

		Enemy* pEnemy=new Enemy("puffer.mesh","",FriendList[i],m_pRootNode);

		pEnemy->registerEvent(EE_Hit,&EnemyQueue::notifyEnemyHit,this);
		m_FriendCollect.push_back(pEnemy);

	}


    ///面向摄像机
    

    
	Ogre::Camera* pCamera=Application::getSingleton().getMainCamera();
	Ogre::Vector3 camPos= pCamera->getParentNode()->getPosition();
	m_pRootNode->lookAt(camPos,Ogre::Node::TS_WORLD,Ogre::Vector3::UNIT_Z);
    

	



}



//-----------------------------------------------------------------
EnemyQueue::~EnemyQueue()
{

	destroy();
	

}



//-----------------------------------------------------------------
void EnemyQueue::update(float time)
{
	
	EnemyCollect::iterator it=m_ElemyCollect.begin();
	EnemyCollect::iterator endit=m_ElemyCollect.end();
	for(;it!=endit;++it)
	{
		(*it)->update(time);
	}

	it=m_FriendCollect.begin();
	endit=m_FriendCollect.end();
	for(;it!=endit;++it)
	{
		(*it)->update(time);
	}

    if(m_State==EQ_NORMAl)
    {
        updateNormal(time);
        return ;
    }

	
   ///如果有队员变打死飞到背景外层
     if(m_State==EQ_KILLFRIEND)
	 {
		 updateLevelState(time);

	 }

	///如果所有敌人被打死，队友示爱后消息
	 if(m_State==EQ_KILLALLENEMY)
	 {
		 updateThankState(time);
	 }


}
//---------------------------------------------------------------------------
void  EnemyQueue::updateCollision(Bullet* pBullet)
{


	Ogre::Ray ray;
	float lenght=0.0f;
	if(pBullet->getFrameRay(ray,lenght)==false)
	{
        return ;
	}

	EnemyCollect::iterator it=m_ElemyCollect.begin();
	EnemyCollect::iterator endit=m_ElemyCollect.end();
	for(;it!=endit;++it)
	{
		bool hitMouth=false;
		if((*it)->getState()==Enemy::ES_NORMAL&& (*it)->intersectRay(ray,lenght,hitMouth,pBullet))
		{
		  (*it)->onHit(ray.getPoint(lenght),pBullet,hitMouth);
		  pBullet->hitTarget();
		  ///广播打中一个目标
		  WarManager::getSingleton().notifyKillEnemy(*it,hitMouth,pBullet);
		  
		   return ;
		}
	}



	it=m_FriendCollect.begin();
	endit=m_FriendCollect.end();
	for(;it!=endit;++it)
	{
		bool hitMouth=false;
		if((*it)->getState()==Enemy::ES_NORMAL&&(*it)->intersectRay(ray,lenght,hitMouth,pBullet))
		{
			(*it)->onHit(ray.getPoint(lenght),pBullet,hitMouth);
			 pBullet->hitTarget();
              
			 ///通中打中一个队友
			 WarManager::getSingleton().notifyHitFriend(*it);
			 return ;
		}
	}





	return ;

}


//-----------------------------------------------------------------
Ogre::AxisAlignedBox  EnemyQueue::getWordBox()
{

	Ogre::AxisAlignedBox box;


	EnemyCollect::iterator it=m_ElemyCollect.begin();
	EnemyCollect::iterator endit=m_ElemyCollect.end();
	for(;it!=endit;++it)
	{
		const Ogre::AxisAlignedBox temBox=(*it)->getSceneNode()->_getWorldAABB();
        box.merge(temBox);
	}

	it=m_FriendCollect.begin();
	endit=m_FriendCollect.end();
	for(;it!=endit;++it)
	{
		const Ogre::AxisAlignedBox temBox=(*it)->getSceneNode()->_getWorldAABB();
		box.merge(temBox);
	}




	return box;



}



//--------------------------------------------------------------------------
//bool EnemyQueue::intersectRay(const Ogre::Ray& ray,float length)
//{

	///先对最外面的外框盒做一个检查，如果有相应再对里面每一个对像再做检查
	/*const Ogre::AxisAlignedBox& box=m_pRootNode->_getWorldAABB();
	float nearPoint(0.0f),farPoint(0.0f);
	bool intersect=	Ogre::Math::intersects(ray,box,&nearPoint,&farPoint);
	if(intersect==false)
	{
		return false;
	}*/


//	EnemyCollect::iterator it=m_ElemyCollect.begin();
//	EnemyCollect::iterator endit=m_ElemyCollect.end();
//	for(;it!=endit;++it)
//	{
//		if((*it)->intersectRay(ray,length))
//		{
//			(*it)->onHit()
//			return true;
//		}
//	}
//
//
//	it=m_FriendCollect.begin();
//	endit=m_FriendCollect.end();
//	for(;it!=endit;++it)
//	{
//		if((*it)->intersectRay(ray,length))
//		{
//			return true;
//		}
//	}
//
//
//	return false;
//
//
//}

//--------------------------------------------------------------------------
void EnemyQueue::destroy()
{

	EnemyCollect::iterator it=m_ElemyCollect.begin();
	EnemyCollect::iterator endit=m_ElemyCollect.end();
	for(;it!=endit;++it)
	{
		delete (*it);
	}
     m_ElemyCollect.clear();


	it=m_FriendCollect.begin();
	endit=m_FriendCollect.end();
	for(;it!=endit;++it)
	{
		delete (*it);
	}
	m_FriendCollect.clear();


	m_pRootNode->removeAndDestroyAllChildren();
	m_pSceneMrg->getRootSceneNode()->removeAndDestroyChild(m_pRootNode->getName());

}

//--------------------------------------------------------------------------
void EnemyQueue::notifyEnemyHit(Enemy* pEnemy)
{
	
	if(hasFriendKilled())
	{
		m_State=EQ_KILLFRIEND;

		///确定逃离的方向
		m_LevelPoint.x=Ogre::Math::RangeRandom(-3.0f,3.0f);
		m_LevelPoint.y=Ogre::Math::RangeRandom(-3.0f,3.0f);
		m_LevelPoint.z=Ogre::Math::RangeRandom(-10.0f,0.0f);
        m_LevelPoint.normalise();
		m_currentLeftTime=0.0f;
		return ;


	}else if(isEnemyAllKilled())
	{

		///播放示爱动作 
		EnemyCollect::iterator it=m_FriendCollect.begin();
		EnemyCollect::iterator endit=m_FriendCollect.end();
		for(;it!=endit;++it)
		{
			(*it)->playAnimation(g_idleAni,true,1.0f);
			
		}

		m_State=EQ_KILLALLENEMY;
		m_currentLeftTime=0.0f;

	}


	return ;

}


//--------------------------------------------------------------------------
bool  EnemyQueue::hasFriendKilled()
{
	///如果生命周期到了。或者
	EnemyCollect::iterator it=m_FriendCollect.begin();
	EnemyCollect::iterator endit=m_FriendCollect.end();
	for(;it!=endit;++it)
	{
		if((*it)->getState()>Enemy::ES_NORMAL)
		{
			return true;
		}
	}

	return false;

}


//--------------------------------------------------------------------------
bool  EnemyQueue::isEnemyAllKilled()
{

///如果敌人队列里的对像全死了。表示整队被打死
	EnemyCollect::iterator it=m_ElemyCollect.begin();
	EnemyCollect::iterator endit=m_ElemyCollect.end();
	for(;it!=endit;++it)
	{
		if((*it)->getState()==Enemy::ES_NORMAL)
		{
			return false;
		}
	}

	return true;

}


//--------------------------------------------------------------------------
void EnemyQueue::updateThankState(float time)
{

	///示爱后三秒原地消失眠
    m_currentLeftTime+=time;
	if(m_currentLeftTime>m_leftTime)
	{

	m_State=EQ_DISACTIVE;
	WarManager::getSingleton().notifyEnemyQueuDeath(this);
	///通知杀死一队敌人
	}


	return ;
}



//--------------------------------------------------------------------------
void EnemyQueue::updateLevelState(float time)
{


	///逃离屏幕飞到实影后面,先旋转再逃跑.
	Ogre::Vector3 trans=m_LevelPoint*time*10.0f;
	//m_pRootNode->translate(trans,Ogre::Node::TS_WORLD);

	///三秒之后通知

	/*EnemyCollect::iterator it=m_ElemyCollect.begin();
	EnemyCollect::iterator itend=m_ElemyCollect.end();
	for(;it!=itend;++it)
	{
		(*it)->getSceneNode()->translate(trans,Ogre::Node::TS_WORLD);
	}*/


	///三秒后消失
	m_currentLeftTime+=time;
	if(m_currentLeftTime>3.0f)
	{
		m_State=EQ_DISACTIVE;
		///通知杀敌失败
    	WarManager::getSingleton().notifyEnemyQueuLost(this);
	}


	return ;

}

//------------------------------------------------------------------
void EnemyQueue::updateNormal(float time)
{
    m_currentLeftTime+=time;
    if(m_currentLeftTime>=m_leftTime)
    {
        m_State=EQ_KILLFRIEND;
        
		///确定逃离的方向
		m_LevelPoint.x=Ogre::Math::RangeRandom(-3.0f,3.0f);
		m_LevelPoint.y=Ogre::Math::RangeRandom(-3.0f,3.0f);
		m_LevelPoint.z=Ogre::Math::RangeRandom(-10.0f,0.0f);
        m_LevelPoint.normalise();
		m_currentLeftTime=0.0f;


		///给每一个敌人加入一个动作
		size_t size=m_ElemyCollect.size();
		for(size_t i=0;i<size;++i)
		{
			m_ElemyCollect[i]->startRunAway(m_LevelPoint,1.5f);
		}



		return ;
    }
    
}