#include "pch.h"
#include  "EnemyQueue.h"
#include "Application.h"



//-----------------------------------------------------------------
EnemyQueue::EnemyQueue(const  PositionList&EnemyList,const PositionList& FriendList )
:m_pSceneMrg(NULL),m_pRootNode(NULL)
{

	m_pSceneMrg=Application::getSingleton().getMainSceneManager();
	m_pRootNode=m_pSceneMrg->getRootSceneNode()->createChildSceneNode();


	size_t size=EnemyList.size();
	for(size_t i=0;i<size;++i)
	{
		m_ElemyCollect.push_back(new Enemy("face.mesh",EnemyList[i],m_pRootNode));

	}

	//size=FriendList.size();
	//for(size_t i=0;i<size;++i)
	//{
	//	Enemy* pEnemy=new Enemy()
	//}


	



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


//--------------------------------------------------------------------------
bool EnemyQueue::intersectRay(const Ogre::Ray& ray,float length)
{

	///先对最外面的外框盒做一个检查，如果有相应再对里面每一个对像再做检查
	const Ogre::AxisAlignedBox& box=m_pRootNode->_getWorldAABB();
	float nearPoint(0.0f),farPoint(0.0f);
	bool intersect=	Ogre::Math::intersects(ray,box,&nearPoint,&farPoint);
	if(intersect==false)
	{
		return false;
	}


	EnemyCollect::iterator it=m_ElemyCollect.begin();
	EnemyCollect::iterator endit=m_ElemyCollect.end();
	for(;it!=endit;++it)
	{
		if((*it)->intersectRay(ray,length))
		{
			return true;
		}
	}

	return false;


}

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

