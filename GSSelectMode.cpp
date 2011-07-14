#include "pch.h"
#include "GSSelectMode.h"
#include "UISelectMode.h"
#include "Application.h"

//---------------------------------------------------------------
GSSelectMode::GSSelectMode()
:GameState(ST_SELECTMODE),m_pUI(NULL)
{


}


//---------------------------------------------------------------
GSSelectMode::~GSSelectMode()
{

}



//---------------------------------------------------------------
void  GSSelectMode::begin( )
{
	GameState::begin();

	initUI();
}

//---------------------------------------------------------------
void  GSSelectMode::end( )
{
	GameState::end();
	DestroyUI();

}
    
    
//---------------------------------------------------------------
StateType GSSelectMode::update(float time)
{

	return GameState::update(time);

}


//---------------------------------------------------------------
void GSSelectMode::initUI()
{
	m_pUI=new UISelectMode();
	m_pUI->init();
	Application::getSingleton().registerUI(m_pUI);


	return ;

}


//---------------------------------------------------------------
void GSSelectMode::DestroyUI()
{

	Application::getSingleton().destroyUI(m_pUI);
	m_pUI=NULL;

	return ;
}
