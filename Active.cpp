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
	assert(m_ActiveVector.empty()==false);
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
RotateActive::RotateActive(Ogre::Node* pNode,const Ogre::Vector3& axis,Ogre::Radian radian,float time)
:m_pNode(pNode),m_Axis(axis),m_radian(radian),m_leftTime(time),m_currentTime(0.0f)
{

	assert(m_pNode);
}


//-----------------------------------------------------------------
RotateActive::~RotateActive()
{

}


//-----------------------------------------------------------------
void  RotateActive::begin()
{
	m_orginQuaternion=m_pNode->getOrientation();
	m_currentTime=0.0f;

}

//-----------------------------------------------------------------
bool   RotateActive::update(float time)
{
	m_currentTime+=time;
	float temPre=m_currentTime/m_leftTime;
	m_pNode->setOrientation(m_orginQuaternion);
	m_pNode->rotate(m_Axis,m_radian*temPre);

	if(m_currentTime>=m_leftTime)
	{
		return false;
	}

	return true;
}

//-----------------------------------------------------------------
void  RotateActive::end()
{
	m_pNode->setOrientation(m_orginQuaternion);
	m_pNode->rotate(m_Axis,m_radian);

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



/***************************************************************
从当前的位置向指定的方向移动指定的距离
****************************************************************/
MoveActive::MoveActive(Ogre::Node* pNode,const Ogre::Vector3& dir,Ogre::Node::TransformSpace Space, float length,float time)
:m_pNode(pNode),m_Dir(dir),m_Space(Space),m_length(length),m_lefttime(time),m_currentTime(0.0f)
{

	assert(m_pNode);
 


}

//--------------------------------------------------------------
MoveActive::~MoveActive()
{

}

//--------------------------------------------------------------
void  MoveActive::begin()
{

	 m_OrginPos=m_pNode->getPosition();
	 m_currentTime=0.0f;

}

//--------------------------------------------------------------
bool   MoveActive::update(float time)
{
	m_currentTime+=time;

	float temPer=m_currentTime/m_lefttime;
	m_pNode->setPosition(m_OrginPos);
	m_pNode->translate(m_Dir*m_length*temPer,m_Space);

	if(m_currentTime>=m_length)
	{
		return false;
	}

	 return true;

}


//--------------------------------------------------------------
void  MoveActive::end()
{
	m_pNode->setPosition(m_OrginPos);
	m_pNode->translate(m_Dir*m_length,m_Space);

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