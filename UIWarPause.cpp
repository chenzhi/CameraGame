#include "pch.h"
#include "UIWarPause.h"
#include "Application.h"
#include "Widget.h"


//-----------------------------------------------------------------
UIWarPause::UIWarPause()
:UILayout("zantingjiemian"),m_pReturn(NULL),m_pContinue(NULL)
{


}

//-----------------------------------------------------------------
UIWarPause::~UIWarPause()
{


}

//-----------------------------------------------------------------
/*
void UIWarPause::init()
{
	UIBase::init();

	int width=450;
	///按钮背景就
	StaticImage* pStateImage=new StaticImage("UIWarPause_background","jieshu_wenzikuang_1.png");
	registerWidget(pStateImage);
	int width=400;
	pStateImage->setWidth(width);
	pStateImage->setHeight(width);
	pStateImage->setLeft(width*-0.5f);
	pStateImage->setTop(width*-0.5f);
  

	///续继按钮
     m_pContinue=new ImageButton("UIWarPause_continueButton","suspend_continue.png","suspend_continue.png");
	registerWidget(m_pContinue);
	width*=0.8f;
	int height=(width*64)/512.0f;
	m_pContinue->setWidth(width);
	m_pContinue->setLeft(-width*0.5f);
    m_pContinue->setHeight(height);
	m_pContinue->setTop(-height*2.0f);
	m_pContinue->setWidth(450);
	m_pContinue->setHeight(100);

	//返回按钮
	m_pReturn=new ImageButton("UIWarPause_returnButton","suspend_RETURN.png","suspend_RETURN.png");
	registerWidget(m_pReturn);
	m_pReturn->setWidth(width);
	m_pReturn->setLeft(-width*0.5f);
	m_pReturn->setHeight(height);
	m_pReturn->setTop(height*2.0f);
	m_pReturn->setWidth(450);
	m_pReturn->setHeight(100);

}
//*/


//-----------------------------------------------------------------
void UIWarPause::buttonHit(Widget* button)
{
	if(button==NULL)
		return ;

	if(button->getName()=="zantingjiemian/zantingcontinue")
	{
		//UIBase* pUI=Application::getSingleton().getUIByName("UIWarModeTwo");
	//	pUI->setVisible(true);
		setVisible(false);

	}else if(button->getName()=="zantingjiemian/zantingreturn")
	{
		setVisible(false);
		Application::getSingleton().getCurrentActive()->setNextStateType(ST_SELECTMODE);
	}




}

//-----------------------------------------------------------------
void UIWarPause::setVisible(bool b)
{
	UIBase::setVisible(b);

	if(b)
	{
		Application::getSingleton().pauseApp();
	}else
	{
		Application::getSingleton().continueApp();


		std::vector<UIBase*>::iterator it=m_ContinueShowUI.begin();
		std::vector<UIBase*>::iterator endit=m_ContinueShowUI.end();
		for(;it!=endit;++it)
		{
			(*it)->setVisible(true);
		}

	}


}