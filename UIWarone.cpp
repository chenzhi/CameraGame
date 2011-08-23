#include "pch.h"
#include "UIWarone.h"
#include "Widget.h"
#include "UIWarPause.h"
#include  "Application.h"



//-----------------------------------------------------------------
UIWarone::UIWarone()
:UIBase("UIWarone",""),m_PauseButton(NULL),m_FirePoint(NULL)
{


}


//-----------------------------------------------------------------
UIWarone::~UIWarone()
{


}

//-----------------------------------------------------------------
void UIWarone::init()
{
	UIBase::init();

	///暂停按钮
	m_PauseButton=new ImageButton("WarModeone_PauseButton","youxi_zhanting_release.png","youxi_zhanting_press.png");
	registerWidget(m_PauseButton);
	m_PauseButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_PauseButton->setVerticalAlignment(Ogre::GVA_TOP);
	m_PauseButton->setLeft(32);
	m_PauseButton->setTop(32);
	m_PauseButton->setWidth(80);
	m_PauseButton->setHeight(80);



	///中间准心
	///准心
	m_FirePoint=new StaticImage("WarModeone_FirePoint","youxi_zhunxin.png");
	registerWidget(m_FirePoint);
	m_FirePoint->setLeft(m_FirePoint->getWidth()*(-0.5f));
	m_FirePoint->setTop(m_FirePoint->getHeight()*(-0.5f));










}


//-----------------------------------------------------------------
void UIWarone::buttonHit(Widget* button)
{
	///如果点击暂停按钮
	if(button==m_PauseButton)
	{
		UIWarPause* pPauseUI= static_cast<UIWarPause*>(Application::getSingleton().getUIByName("UIWarPause"));

		std::vector<UIBase*>showList;
		showList.push_back(this);
		pPauseUI->setEndShowUI(showList);
		pPauseUI->setVisible(true);
		setVisible(false);

	}

}