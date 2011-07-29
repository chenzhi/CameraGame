#include "pch.h"
#include "WarItem.h"
#include "Application.h"
#include "enemy.h"


//-----------------------------------------------------------------------
EggItem::EggItem(const Ogre::Vector3& startPos,Enemy* pEnemy)
:Item("EggItem"),m_StartPos(startPos),m_pParentNode(NULL),m_pEntity(NULL),m_liftTime(0.0f)
{

	assert(pEnemy);
	setTarget(pEnemy);

	initEtity();

}

//-----------------------------------------------------------------------
EggItem::~EggItem()
{


}


//-----------------------------------------------------------------------
void  EggItem::begin()
{

	///随机出一个谢转方向

	//m_pParentNode.rotate()

	m_pRotateDir.x=Ogre::Math::RangeRandom(0.0f,1.0f);
	m_pRotateDir.y=Ogre::Math::RangeRandom(0.0f,1.0f);
	m_pRotateDir.z=Ogre::Math::RangeRandom(0.0f,1.0f);
	m_pRotateDir.normalise();

	m_liftTime=0.0f;

}


//-----------------------------------------------------------------------
bool   EggItem::update(float time)
{

	m_liftTime+=time;
	if(m_liftTime>5.0f)
	{
		end();
		return false;
	}

	///如果发生碰撞，给目标物点上贴图
	if(hitTarget())
	{
        end(); ///道具使用完成
		return false ;
	}

	m_pParentNode->rotate(m_pRotateDir,Ogre::Radian(time));

	float spped=0.3f;
	Ogre::Vector3 pos=m_pParentNode->getPosition();
	Ogre::Vector3 targetPos=m_pTarget->getSceneNode()->getPosition();

	Ogre::Vector3 dir=targetPos-pos;
	dir.normalise();
	m_pParentNode->translate(dir*spped*time,Ogre::Node::TS_WORLD);
	return true;

}

//-----------------------------------------------------------------------
void EggItem::end()
{
	m_pTarget->setHitEffectTextureName("danqin.png");

	destroyEntiy();

}

//-----------------------------------------------------------------------
void EggItem::initEtity()
{

	///创建模型。设置位置。
	Ogre::SceneManager* pSceneMrg=Application::getSingleton().getMainSceneManager();
	m_pParentNode=pSceneMrg->getRootSceneNode()->createChildSceneNode();
	m_pEntity=pSceneMrg->createEntity("jidan.mesh");
	m_pParentNode->attachObject(m_pEntity);
	m_pParentNode->setPosition(m_StartPos);


}

//-----------------------------------------------------------------------
void EggItem::destroyEntiy()
{
	m_pParentNode->detachAllObjects();
	m_pParentNode->getParentSceneNode()->removeAndDestroyChild(m_pParentNode->getName());

	Ogre::SceneManager* pSceneMrg=Application::getSingleton().getMainSceneManager();
	pSceneMrg->destroyEntity(m_pEntity);
	m_pEntity=NULL;

}


//-----------------------------------------------------------------------
bool EggItem::hitTarget()
{
	const Ogre::Vector3& pos=m_pParentNode->getPosition();
    const Ogre::AxisAlignedBox& box=m_pTarget->getSceneNode()->_getWorldAABB();
	return 	box.contains(pos);
}