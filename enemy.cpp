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
#include "Bullet.h"
#include "Application.h"

int Enemy::m_EntityIndex=0;

//------------------------------------------
Enemy::Enemy(const Ogre::String& meshName,const Ogre::String& headMesh,const Ogre::Vector3& pos, Ogre::SceneNode* pParent)
:m_pEntity(NULL),m_pNode(NULL),m_pSceneMrg(pParent->getCreator()),m_pAniSate(NULL),m_LifeValue(30),m_State(ES_NORMAL),m_Rotate(0),
m_pHeadEnity(NULL),m_HurtTime(0.0f),m_Trans(0.0f,0.0f,0.0f),m_AniFade(0.0f),m_pMouthEntity(NULL),m_pSwallow(NULL)
{

	m_pEntity=m_pSceneMrg->createEntity("Enemy"+Ogre::StringConverter::toString(m_EntityIndex++),meshName);
	m_pNode=pParent->createChildSceneNode();
	m_pNode->attachObject(m_pEntity);
	m_pNode->setPosition(pos);

	bool b=m_pEntity->hasSkeleton();

	if(headMesh.empty()==false)
	{
		m_pHeadEnity=m_pSceneMrg->createEntity(headMesh);
        assert(m_pHeadEnity);
		m_pNode->attachObject(m_pHeadEnity);
		m_pHeadEnity->shareSkeletonInstanceWith(m_pEntity);


		///加载嘴部模形，用于检查是否击中嘴部

		m_pMouthEntity=m_pSceneMrg->createEntity("mouth.mesh");
		m_pMouthEntity->shareSkeletonInstanceWith(m_pEntity);
		m_pNode->attachObject(m_pMouthEntity);
		m_pMouthEntity->setVisible(false);
		


	}

	m_pEntity->setQueryFlags(EnemyMask);
	m_pAniSate=NULL;
	m_pMaterial=m_pEntity->getSubEntity(0)->getMaterial();



	//m_pMouthEntity=m




	///播放休闲动作
   playAnimation(g_idleAni,true,0);

  



}

//------------------------------------------
Enemy::~Enemy()
{
	destroy();

}

//------------------------------------------
void Enemy::onHit(const Ogre::Vector3& hitPos,Bullet* pBullet,bool hitMouth )
{

	///如果是死亡或变打中的状态直接返回
	if(m_State>ES_NORMAL)
		return ;


	if(hitMouth)
	{
		m_State=ES_SWALLOWBALL;

	}else
	{
       m_State=ES_DODGE;
	}

	///如果是没有头套就是河豚打中后会进入放黑烟的效果
	if(m_pHeadEnity==NULL)
	{
		m_State=ES_SMOKE;
		onHitFriend();
	}

	
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


	///如果有动作状态就直接去掉
	if(hasActive())
	{
		stopAndRemoveActive();
	}

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

	   if(m_pSwallow!=NULL)
	   {
		   m_pSwallow->detachObjectFromBone(m_pEntity);
		   m_pSceneMrg->destroyEntity(m_pSwallow);
		   m_pSwallow=NULL;
	   }

		if(m_pEntity!=NULL)
		{
			m_pSceneMrg->destroyEntity(m_pEntity);
			m_pEntity=NULL;
		}

		if(m_pHeadEnity!=NULL)
		{
			m_pSceneMrg->destroyEntity(m_pHeadEnity);
			m_pHeadEnity=NULL;
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
void   Enemy::update(float time)
{
	


	updateAnimation(time);

	if(m_State==ES_NORMAL)
	{
		updateNormal(time);
		//updateOrientation();

	}else if(m_State==ES_DODGE)
	{
		updateDodge(time);
	}else if(m_State==ES_DEATH)
	{
		updateDeath(time);
	}else if(m_State==ES_SWALLOWBALL)
	{
		updateSwallowBall(time);
	}else if(m_State==ES_SMOKE)
	{
		updateSmoke(time);
	}

	return  ;
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
	float ra=m_Rotate*time;
	m_pNode->rotate(Ogre::Vector3(0.0f,1.0f,0.0f), Ogre::Radian(ra),Ogre::Node::TS_WORLD);
	m_pNode->rotate(Ogre::Vector3(0.0f,0.0f,1.0f), Ogre::Radian(ra*0.5f),Ogre::Node::TS_WORLD);
	m_Rotate-=ra;


	////移动
	Ogre::Vector3 tr=m_Trans*0.3f*time;
	//m_pNode->translate(tr,Ogre::Node::TS_WORLD);
	m_Trans-=tr;

	float speed=1.0f;
	Ogre::Vector3 gravity(0,-3,0);
	gravity=gravity*speed*time*(m_HurtTime+1);
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


//------------------------------------------------------------
void  Enemy::onHitFriend()
{

	playAnimation("aida",false,0.5f);

}



//------------------------------------------------------------
void  Enemy::updateSmoke(float time)
{
	m_HurtTime+=time;
	///如果受作超过三秒就死亡
	if(m_HurtTime>=3.0f)
	{
		death();
	}

}


//------------------------------------------------------------
void Enemy::updateOrientation()
{
	Ogre::Vector3 camPosition=Application::getSingleton().getMainCameraNode()->getPosition();
	Ogre::Vector3 dir=camPosition-m_pNode->getPosition();
	dir.normalise();
	m_pNode->lookAt(camPosition,Ogre::Node::TS_WORLD,Ogre::Vector3::UNIT_Z);
	return  ;
}

//------------------------------------------------------------
void Enemy::onHitMouth(Bullet* pBullet)
{


	
	playAnimation("hanqiu",true,0.5f);
	pBullet->setVisible(false);

	///把子弹挂到嘴上
	if(m_pSwallow==NULL)
	{
       m_pSwallow=m_pSceneMrg->createEntity("zidan.mesh");
	}
	m_pEntity->attachObjectToBone("Bone10",m_pSwallow,Ogre::Quaternion::IDENTITY,Ogre::Vector3(0.02f,0.0f,0.0f));
	

	///把播放粒子爆炸效果



}


void Enemy::updateSwallowBall(float time)
{

	m_HurtTime+=time;
	///如果受作超过三秒就死亡
	if(m_HurtTime>=3.0f)
	{
		death();
	}


	


	//


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

	if(m_pSwallow!=NULL)
	{
		m_pSwallow->detachObjectFromBone(m_pEntity);
	}

	m_LifeValue=100;
	m_State=ES_NORMAL;
	m_Rotate=0;
	m_Trans.x=m_Trans.y=m_Trans.z=0.0f;


	return  ;
}


//--------------------------------------------------------------
bool Enemy::intersectRay(const Ogre::Ray& ray,float length,bool& hitMouth,Bullet* pBullet)
{
	
	hitMouth=false;

	///先对最外面的外框盒做一个检查，如果有相应再对里面每一个对像再做检查
	const Ogre::AxisAlignedBox& box=m_pNode->_getWorldAABB();
	float nearPoint(0.0f),farPoint(0.0f);
	bool intersect=	Ogre::Math::intersects(ray,box,&nearPoint,&farPoint);
	if(intersect==false)
	{
		return false;
	}

	///如果最外层击中，再判断是否击中嘴部
	if(nearPoint<length || farPoint<length)
	{
		if(m_pMouthEntity!=NULL)
		{

			const Ogre::AxisAlignedBox& MouthBox=m_pMouthEntity->getWorldBoundingBox();
			float mouthNear(0.0f),mouthFar(0.0f);
			bool intersect=	Ogre::Math::intersects(ray,MouthBox,&mouthNear,&mouthFar);
			if(intersect&&(nearPoint<length || farPoint<length))
			{
				///表示击中嘴部播放张嘴动作。并把子弹隐藏，在嘴上放一个子弹。
				hitMouth=true;
				return true;

			}


		}

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

	m_AniFade=fadetime;
	return true;
}

/**更新动画*/
void Enemy::updateAnimation(float time)
{

	m_AniFade-=time;
	m_AniFade=std::max(m_AniFade,0.0f);

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


//-------------------------------------------------------------------------------
bool Enemy::setHitEffectTextureName(const Ogre::String& textureName)
{

	Ogre::TextureUnitState* pTextureState=m_pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(1);
	if(pTextureState==NULL)
		return false;
	pTextureState->setTextureName(textureName);
	return true;
}

//--------------------------------------------------------------------------------
void Enemy::startRunAway(float time,bool leftRotate)
{

	///选旋转y轴180度。再移动到目标点
	ActiveQueue* pActiveQueue= new ActiveQueue();
	pActiveQueue->addActive(new RotateActive(m_pNode,Ogre::Vector3::UNIT_Y,leftRotate?Ogre::Radian(Ogre::Math::PI):-Ogre::Radian(Ogre::Math::PI),0.5f));

	pActiveQueue->addActive(new MoveActive(m_pNode,Ogre::Vector3::UNIT_Z,Ogre::Node::TS_LOCAL,10.0f,1.0f));

	this->runActive(pActiveQueue);

}