#include "pch.h"
#include  "EnemyQueue.h"
#include "Application.h"
#include "Config.h"
#include "Bullet.h"

//-----------------------------------------------------------------
EnemyQueue::EnemyQueue(const Ogre::Vector3& pos,const  PositionList&EnemyList,const PositionList& FriendList )
:m_pSceneMrg(NULL),m_pRootNode(NULL)
{

	m_pSceneMrg=Application::getSingleton().getMainSceneManager();
	m_pRootNode=m_pSceneMrg->getRootSceneNode()->createChildSceneNode();
    m_pRootNode->setPosition(pos);
	m_pRootNode->showBoundingBox(true);

	size_t size=EnemyList.size();
	for(size_t i=0;i<size;++i)
	{
		const Ogre::String& faceMesh=g_userInformation.getFaceMode();
		const Ogre::String& headMesh=g_userInformation.getHeadMode();
		m_ElemyCollect.push_back(new Enemy(faceMesh,headMesh,EnemyList[i],m_pRootNode));

	}

	size= FriendList.size();
	for(size_t i=0;i<size;++i)
	{

		Enemy* pEnemy=new Enemy("face_pang.mesh","hema.mesh",FriendList[i],m_pRootNode);
		m_FriendCollect.push_back(pEnemy);

	}




	



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
		if((*it)->intersectRay(ray,lenght))
		{
		  (*it)->onHit(ray.getPoint(lenght),pBullet);
		  
		   return ;
		}
	}



	it=m_FriendCollect.begin();
	endit=m_FriendCollect.end();
	for(;it!=endit;++it)
	{
		if((*it)->intersectRay(ray,lenght))
		{
			(*it)->onHit(ray.getPoint(lenght),pBullet);
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

