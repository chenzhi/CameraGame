
#include "pch.h"
#include "GS_GamePlay.h"
#include "UI_GamePlay.h"
#include "Application.h"



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

	initUI();

}
	

//-------------------------------------------------------------
void  GSGamePlay::end( )
{
	GameState::end();
	destroyUI();

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
