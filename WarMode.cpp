#include "pch.h"
#include "WarMode.h"
#include "Widget.h"
#include "UIWarTwo.h"
#include "Application.h"
#include "enemy.h"
#include "Config.h"
#include "WarManager.h"



//--------------------------------------------------------
GameModeTwo::GameModeTwo(GameState* pGameState)
:GameMode(pGameState),m_pSceneMrg(NULL)
{
	m_pSceneMrg=Application::getSingleton().getMainSceneManager();
}


//--------------------------------------------------------
GameModeTwo::~GameModeTwo()
{

}


//--------------------------------------------------------
void GameModeTwo::start()
{



	//m_pEnemeyNode=m_pSceneMrg->getRootSceneNode()->createChildSceneNode();


	//Ogre::Vector3 pos(0.0f,0.0f,0.0f);
	//const Ogre::String& faceMesh=g_userInformation.getFaceMode();
	//const Ogre::String& headMesh=g_userInformation.getHeadMode();
	//m_pEnemy=new Enemy(faceMesh,headMesh,pos,m_pSceneMrg->getRootSceneNode());



	initUI();

	EnemyQueue* pQueue=WarManager::getSingleton().createEnemyQueue(20,30);
	m_pUI->notityEmeny(pQueue);

}

//--------------------------------------------------------
void GameModeTwo::end()
{

}

//--------------------------------------------------------
void GameModeTwo::update(float time)
{

	//static float stime=0;
	//stime+=time;
	//float y=Ogre::Math::Sin(stime);
	//float x=Ogre::Math::Cos(stime);	
	//Ogre::Vector3 pos(x,y,0.0f);
	//pos*=1.50f;

	//m_pEnemy->getSceneNode()->setPosition(pos);


	updateUIDir();

}


//--------------------------------------------------------
void GameModeTwo::beginTouch(int x,int y)
{

	


}

//--------------------------------------------------------
void  GameModeTwo::endTouch(int x,int y)
{

}

///--------------------------------------------------------
void  GameModeTwo::moveTouch(int x,int y)
{

}

//---------------------------------------------------------
void GameModeTwo::initUI()
{

	m_pUI=new UIWarModeTwo();
	m_pUI->init();
	
	Application::getSingleton().registerUI(m_pUI);



}


//---------------------------------------------------------
void GameModeTwo::destroyUI()
{

	Application::getSingleton().destroyUI(m_pUI);
	m_pUI=NULL;

}


//---------------------------------------------------------
void GameModeTwo::updateUIDir()
{
	//Ogre::Vector3 pos=m_pEnemy->getSceneNode()->getPosition();

	
	

	


	return ;
}


/**内部调用函数，杀死目标后的回调函数*/
void GameModeTwo::notityKillEmemy()
{
	return ;
}