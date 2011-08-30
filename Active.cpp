#include "pch.h"
#include "Active.h"



/***************************************************
动作队列
*******************************************************/

ActiveQueue::~ActiveQueue()
{
	destroyAllActive();
}

//------------------------------------------------------------
void  ActiveQueue::addActive(Active* pActive)
{
	if(pActive!=NULL)
	{
		m_ActiveVector.push_back(pActive);
	}

}


//------------------------------------------------------------
void  ActiveQueue::begin()
{

	Active::begin();
	///动作队列不能为空
	assert(m_ActiveVector.empty());
	m_CurrentIterator=m_ActiveVector.begin();
	(*m_CurrentIterator)->begin();
 
}


//------------------------------------------------------------
bool   ActiveQueue::update(float time)
{
	//Active::update(time);
	bool isend=(*m_CurrentIterator)->update(time);
	if(isend==false)
	{
		///如果完成直接调用end
		(*m_CurrentIterator)->end();

		//如果是最后一个就直接返回
		m_CurrentIterator++;
		if(m_CurrentIterator==m_ActiveVector.end())
		{
			return false;
		}

		(*m_CurrentIterator)->begin();

	}

	return true;
}

//------------------------------------------------------------
void  ActiveQueue::end()
{
	Active::end();
}

//------------------------------------------------------------
void  ActiveQueue::destroyAllActive()
{

	ActitveVector::iterator it=m_ActiveVector.begin();
	ActitveVector::iterator endit=m_ActiveVector.end();
	for(;it!=endit;++it)
	{

		SafeDelete(*it);
	}
	m_ActiveVector.clear();
    
}




/**********************************************************
///从当前朝向旋转到哪个朝向
***********************************************************/
RotateToActive::RotateToActive(Ogre::SceneNode* pTarget,const Ogre::Quaternion& quat,float time)
:m_pTarget(pTarget),m_pTargetQuater(quat),m_LeftTime(time),m_CurrentTime(0.0f)
{

	assert(pTarget);
	//m_OrignQuater=m_pTarget->getOrientation();


}


RotateToActive::~RotateToActive()
{

}


void  RotateToActive::begin()
{

	Active::begin();
  m_OrignQuater=m_pTarget->getOrientation();
  m_CurrentTime=0.0f;

	return ;

}


bool   RotateToActive::update(float time)
{
	m_CurrentTime+=time;

	float precent=m_CurrentTime/m_LeftTime;
	precent= std::min(1.0f,precent);
	Ogre::Quaternion quater=Ogre::Quaternion::Slerp(precent,m_OrignQuater,m_pTargetQuater);
	m_pTarget->setOrientation(quater);
	///如果超过生命周期
	if(m_CurrentTime>=m_LeftTime)
	{
		return false;
	}
	return true;

}


void  RotateToActive::end()
{
	m_pTarget->setOrientation(m_pTargetQuater);
	Active::end();
	return ;

}





/**********************************************************
///从当前位置移动到指定个朝向
***********************************************************/
MoveToActive::MoveToActive(Ogre::SceneNode* pTarget,const Ogre::Vector3& TargetPosition,float time)
:m_pTarget(pTarget),m_TargetPosition(TargetPosition),m_LeftTime(time),m_CurrentTime(0.0f)
{
	assert(m_pTarget);
 
}



//--------------------------------------------------------------
void  MoveToActive::begin()
{
	Active::begin();
	m_CurrentTime=0.0f;
	m_OrignPosition=m_pTarget->getPosition();

}


//--------------------------------------------------------------
bool   MoveToActive::update(float time)
{
	m_CurrentTime+=time;
	float precent=m_CurrentTime/m_LeftTime;
	precent=std::min(1.0f,precent);
	Ogre::Vector3 pos=m_OrignPosition+(m_TargetPosition-m_OrignPosition)*precent;
	m_pTarget->setPosition(pos);

	if(m_CurrentTime>=m_LeftTime)
	{
		return false;
	}

	return true;
}


//--------------------------------------------------------------
void  MoveToActive::end()
{
	Active::end();
	m_pTarget->setPosition(m_TargetPosition);

}