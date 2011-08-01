#include "pch.h"
#include "WarModeThree.h"
#include "UIWarModeThree.h"
#include "Application.h"
#include "WarManager.h"
#include "WarItem.h"
#include "WarItemManager.h"


//----------------------------------------------------------------
WarModeThree::WarModeThree(GameState* pGameState)
:WarMode(pGameState),m_pUIWar(NULL),m_CurrentPower(0.0f),m_MaxPower(15.0f),
m_StopFireTime(0),m_pWarItemManager(NULL),m_pTargetEnemy(NULL)
{

}


//----------------------------------------------------------------
WarModeThree::~WarModeThree()
{

}


//----------------------------------------------------------------
void WarModeThree::start()
{

	initUI();


	m_pWarItemManager=new WarItemManager();
	///创建一个模型
	WarManager::getSingleton().startWar();
	m_pTargetEnemy=WarManager::getSingleton().createEnemy(Ogre::Vector3(0,0,1));


}


//----------------------------------------------------------------
void WarModeThree::end()
{

	destroyUI();
	WarManager::getSingleton().endWar();
	SafeDelete(m_pWarItemManager);

	

}

//----------------------------------------------------------------
void WarModeThree::update(float time)
{

	m_pWarItemManager->update(time);
}



//-----------------------------------------------------------------
void WarModeThree::beginTouch(int x,int y)
{
	WarItem* pItem= m_pWarItemManager->createWarItem(WIT_EGG);
	pItem->setTarget(m_pTargetEnemy);
	

	return ;
}


//----------------------------------------------------------------
void WarModeThree::initUI()
{
	m_pUIWar=new UIWarModeThree(this);
	m_pUIWar->init();
	Application::getSingleton().registerUI(m_pUIWar);

}


//----------------------------------------------------------------
void WarModeThree::destroyUI()
{
	Application::getSingleton().destroyUI(m_pUIWar);
	m_pUIWar=NULL;

	
}

//--------------------------------------------------------------------
void WarModeThree::updatePower(float time)
{
	m_StopFireTime+=time;
	if(m_StopFireTime>3.0)
	{
		m_CurrentPower-=time*3;////每秒减三格
		std::max(m_CurrentPower,0.0f);//不能小于0

	}else
	{

	}



	///设置能量槽的长度
	m_pUIWar->setPowerPercent(m_CurrentPower/m_MaxPower);





}