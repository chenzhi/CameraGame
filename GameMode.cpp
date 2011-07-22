#include "pch.h"
#include "GameMode.h"
#include "Widget.h"
#include "UIWarTwo.h"
#include "Application.h"
#include "enemy.h"

//--------------------------------------------------------
GameModeTwo::GameModeTwo(GameState* pGameState)
:GameMode(pGameState),m_pEnemy(NULL),m_pSceneMrg(NULL)
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


	Ogre::Vector3 pos(0.0f,0.0f,0.0f);
	m_pEnemy=new Enemy("face.mesh",pos,m_pSceneMrg->getRootSceneNode());

	initUI();



}

//--------------------------------------------------------
void GameModeTwo::end()
{

}

//--------------------------------------------------------
void GameModeTwo::update(float time)
{

	static float stime=0;
	stime+=time;
	float y=Ogre::Math::Sin(stime);
	float x=Ogre::Math::Cos(stime);	
	Ogre::Vector3 pos(x,y,0.0f);
	pos*=3.50f;

	m_pEnemy->getSceneNode()->setPosition(pos);


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
	Ogre::Vector3 pos=m_pEnemy->getSceneNode()->getPosition();



	///如果这个点在屏幕上出现了就隐藏箭头
	Ogre::Camera* pCamera=Application::getSingleton().getMainCamera();
	//pCamera->is


	 if(pCamera->isVisible(m_pEnemy->getSceneNode()->_getWorldAABB()))
	 {
		 m_pUI->setVisible(false);
		 return ;
	 }else
	 {

		 m_pUI->setVisible(true);
	 }


	float  ang= (Ogre::Math::ATan(pos.y/pos.x)).valueDegrees();


	///第三像限
	if(pos.x<0&&pos.y>0)
	{

		ang=90.0f+(90+ang);

	}else if(pos.x<0&&pos.y<0)//第四像限
	{

		ang=180.0f+ang;
	}


	m_pUI->setEmemeyDir(Ogre::Radian(Ogre::Angle(ang)).valueRadians());
	

	


	return ;
}