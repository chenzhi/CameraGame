//
//  enemy.cpp
//  ogreApp
//
//  Created by thcz on 11-6-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//






#include "pch.h"
#include "enemy.h"
#include  "WarManager.h"
#include "Config.h"

int Enemy::m_EntityIndex=0;

//------------------------------------------
Enemy::Enemy(const Ogre::String& meshName,const Ogre::String& headMesh,const Ogre::Vector3& pos, Ogre::SceneNode* pParent)
:m_pEntity(NULL),m_pNode(NULL),m_pSceneMrg(pParent->getCreator()),m_pAniSate(NULL),m_LifeValue(30),m_State(ES_NORMAL),m_Rotate(0),
m_pHeadEnity(NULL),m_HurtTime(0.0f),m_Trans(0.0f,0.0f,0.0f),m_AniFade(0.0f)
{

	m_pEntity=m_pSceneMrg->createEntity("Enemy"+Ogre::StringConverter::toString(m_EntityIndex++),meshName);
	m_pNode=pParent->createChildSceneNode();
	m_pNode->attachObject(m_pEntity);
	m_pNode->setPosition(pos);
	m_pHeadEnity=m_pSceneMrg->createEntity(headMesh);

	m_pNode->attachObject(m_pHeadEnity);
	m_pHeadEnity->shareSkeletonInstanceWith(m_pEntity);

	//m_pNode->showBoundingBox(true);

	m_pEntity->setQueryFlags(EnemyMask);
	m_pAniSate=NULL;
	m_pMaterial=m_pEntity->getSubEntity(0)->getMaterial();




}

//------------------------------------------
Enemy::~Enemy()
{
	destroy();

}

//------------------------------------------
void Enemy::onHit(const Ogre::Vector3& hitPos,Bullet* pBullet )
{

	///如果是死亡或变打中的状态直接返回
	if(m_State==ES_DODGE||m_State==ES_DEATH)
		return ;

	

	

	m_State=ES_DODGE;
	m_HurtTime=0.0f;

	///被击中了播放被击中动画
	//playAnimation("onHit",true,1.0f);


	///计算旋转角度和旋转方向
	Ogre::Vector3 CurrentPos=m_pNode->_getDerivedPosition();
	m_pNode->_updateBounds();
	const Ogre::AxisAlignedBox& box=m_pNode->_getWorldAABB();

	float tem=box.getMaximum().x-box.getMinimum().x;
	tem*=0.5f;
	m_Rotate+=(hitPos.x-CurrentPos.x)/tem*Ogre::Math::PI*10;///如果击中最左边就旋转5周


	Ogre::Vector3 center=box.getCenter();
	Ogre::Vector3 dir=center-hitPos;

	dir.y*=10;
	dir.y+=2;

	m_Trans=m_Trans+dir;


	///如果被击中未成亡进入躲避状态
	fireMessage(EE_Hit,this);///广播被击中



}

//------------------------------------------
void Enemy::destroy()
{
	if(m_pSceneMrg!=NULL)
	{

	if(m_pNode!=NULL)
		{
			m_pNode->detachAllObjects();
			m_pNode->getParentSceneNode()->removeAndDestroyChild(m_pNode->getName());

		}

		if(m_pEntity!=NULL)
		{
			m_pSceneMrg->destroyEntity(m_pEntity);
		}
	}

}

//------------------------------------------
void Enemy::setVisible(bool b)
{
	if(m_pNode!=NULL)
	{
		m_pNode->setVisible(b);
	}
}


//------------------------------------------
void Enemy::update(float time)
{


	updateAnimation(time);

	if(m_State==ES_NORMAL)
	{
		updateNormal(time);
	}else if(m_State==ES_DODGE)
	{
		updateDodge(time);
	}else if(m_State==ES_DEATH)
	{
		updateDeath(time);
	}



	return ;
}

//------------------------------------------
const std::string& Enemy::getEntityName()const
{
	assert(m_pEntity);
	return m_pEntity->getName();
}

//------------------------------------------
void Enemy::death()
{ 
	m_State=ES_DEATH;
	// m_pEntity->setVisible(false);
	///广播自已死
	m_pNode->setVisible(false);
	//被击中就是死亡
	fireMessage(EE_Die,this);
	
	return ;
}


//---------------------------------------------------
void Enemy::updateNormal(float time)
{
	return ;
}

//---------------------------------------------------
void Enemy::updateDodge(float time)
{

	m_HurtTime+=time;

	///旋转速度为每秒
	float ra=m_Rotate*0.3f*time;
	m_pNode->rotate(Ogre::Vector3(0,0,1), Ogre::Radian(ra));
	m_Rotate-=ra;


	////移动
	Ogre::Vector3 tr=m_Trans*0.3f*time;
	//m_pNode->translate(tr,Ogre::Node::TS_WORLD);
	m_Trans-=tr;


	float speed=1.0f;
	Ogre::Vector3 gravity(0,-1,0);
	gravity=gravity*speed*time;
	gravity+=tr;
	m_pNode->translate(gravity,Ogre::Node::TS_WORLD);
	Ogre::Vector3 pos=m_pNode->_getDerivedPosition();


	///如果受作超过三秒就死亡
	if(m_HurtTime>=3.0f)
	{
		death();
	}


	return ;
}

//---------------------------------------------------
void Enemy::updateDeath(float time)
{

	return ;
}

//-----------------------------------------------------
void Enemy::reset(const Ogre::Vector3& pos)
{


	m_pNode->setVisible(true);
	m_pNode->resetOrientation();
	m_pNode->setPosition(pos);

	if(m_pMaterial.isNull()==false)
	{
		m_pMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0.0f, 0.0f, 0.0f);
	}
	///重置动画
	if (m_pAniSate!=NULL)
	{
		m_pAniSate->setTimePosition(0);
	}

	m_LifeValue=100;
	m_State=ES_NORMAL;
	m_Rotate=0;
	m_Trans.x=m_Trans.y=m_Trans.z=0.0f;


	return  ;
}


//--------------------------------------------------------------
bool Enemy::intersectRay(const Ogre::Ray& ray,float length)
{

	///先对最外面的外框盒做一个检查，如果有相应再对里面每一个对像再做检查
	const Ogre::AxisAlignedBox& box=m_pNode->_getWorldAABB();
	float nearPoint(0.0f),farPoint(0.0f);
	bool intersect=	Ogre::Math::intersects(ray,box,&nearPoint,&farPoint);
	if(intersect==false)
	{
		return false;
	}
	if(nearPoint<length || farPoint<length)
	{
		return true;
	}

	return false;

}

bool Enemy::playAnimation(const Ogre::String& aniName,bool loop,float fadetime)
{
	if(m_pEntity==NULL)
		return false;

	Ogre::AnimationState* pAni= m_pEntity->getAnimationState(aniName);
	if(pAni==NULL)
		return false;

	m_pAniSate=pAni;
	m_pAniSate->setEnabled(true);
	m_pAniSate->setTimePosition(0.0f);
	m_pAniSate->setLoop(loop);

	if(fadetime>0.0f)
	{
		m_pAniSate->setWeight(0.0f);
	}else
	{
		m_pAniSate->setWeight(1.0f);
	}
	return true;
}

/**更新动画*/
void Enemy::updateAnimation(float time)
{

	m_AniFade-=time;

	if (m_pEntity)
	{
		Ogre::AnimationStateSet* animStateSet = m_pEntity->getAllAnimationStates();
		// 更新自身动画
		if (animStateSet)
		{
			Ogre::ConstEnabledAnimationStateIterator animStateItor = animStateSet->getEnabledAnimationStateIterator();
			while (animStateItor.hasMoreElements())
			{
				Ogre::AnimationState* animState = animStateItor.getNext();
				animState->addTime(time);
				// 当前动画逐渐递增权重
				if (animState== m_pAniSate)
				{
					if (animState->getWeight() < 1.0f)
					{
						animState->setWeight(1.0f - m_AniFade);
					}
				}
				// 其余动画逐渐递减权重，直到关闭动画
				else
				{
					if (Ogre::Math::RealEqual(animState->getWeight(), 0.0f))
					{
						animState->setWeight(1.0f);
						animState->setEnabled(false);
					}
					else
					{
						animState->setWeight(m_AniFade);
					}
				}
			}
		}

	}
}