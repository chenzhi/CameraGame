
#include "pch.h"
#include "GS_GamePlay.h"
#include "UI_GamePlay.h"
#include "Application.h"
#include "UIImagesetManager.h"


//-------------------------------------------------------------
GSGamePlay::GSGamePlay()
:GameState(ST_GAMEPLAY)
{


}


//-------------------------------------------------------------
GSGamePlay::~GSGamePlay()
{


}

  
//-------------------------------------------------------------
void  GSGamePlay::begin( )
{
	GameState::begin();
	
	UIImagesetManager::getSingleton().createImageset("gongyong_0.imageset","UI");

	UIImagesetManager::getSingleton().createImageset("play_0.imageset","UI");

	UIImagesetManager::getSingleton().createImageset("jifengqiepian_0.imageset","UI");

	UIImagesetManager::getSingleton().createImageset("moshixuanze_0.imageset","UI");

	UIImagesetManager::getSingleton().createImageset("xiaoliankuang_0.imageset","UI");


                                                    
	initUI();

}
	

//-------------------------------------------------------------
void  GSGamePlay::end( )
{
	GameState::end();
	destroyUI();

	UIImagesetManager::getSingleton().destroyImagetset("play0_21");

}

    
    
//-------------------------------------------------------------
StateType  GSGamePlay::update(float time)
{


	return 	GameState::update(time);


}


//-------------------------------------------------------------
void GSGamePlay::initUI()
{

	UIBase* pUI=new UIGamePlay();
	pUI->init();
	Application::getSingleton().registerUI(pUI);
	m_UICollect.push_back(pUI);





}


//-------------------------------------------------------------
void GSGamePlay::destroyUI()
{

	size_t size=m_UICollect.size();
	for(size_t i=0;i<size;++i)
	{
      Application::getSingleton().destroyUI(m_UICollect[i]);
 
	}
	
	m_UICollect.clear();

}
