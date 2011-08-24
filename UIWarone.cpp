#include "pch.h"
#include "UIWarone.h"
#include "Widget.h"
#include "UIWarPause.h"
#include  "Application.h"
#include "Tool.h"


//-----------------------------------------------------------------
UIWarone::UIWarone()
:UIBase("UIWarone",""),m_PauseButton(NULL),m_FirePoint(NULL),m_HundredTime(NULL),
m_TenTime(NULL),m_DigitTime(NULL)
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


    ///创建记时图标
	m_HundredTime=new StaticImage("WarModeone_Hundred","jieshu_shuzi_0.png");
	m_HundredTime->setVerticalAlignment(Ogre::GVA_TOP);
	m_HundredTime->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_HundredTime->setWidth(64);
	m_HundredTime->setHeight(64);
	m_HundredTime->setLeft(-64*3);
	registerWidget(m_HundredTime);
	//m_TenTime;

	m_TenTime=new StaticImage("WarModeone_Ten","jieshu_shuzi_0.png");
	m_TenTime->setVerticalAlignment(Ogre::GVA_TOP);
	m_TenTime->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_TenTime->setWidth(64);
	m_TenTime->setHeight(64);
	m_TenTime->setLeft(-64*2);
	registerWidget(m_TenTime);
	//m_DigitTime;
	m_DigitTime=new StaticImage("WarModeone_Digit","jieshu_shuzi_0.png");
	m_DigitTime->setVerticalAlignment(Ogre::GVA_TOP);
	m_DigitTime->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_DigitTime->setWidth(64);
	m_DigitTime->setHeight(64);
	m_DigitTime->setLeft(-64);
	registerWidget(m_DigitTime);

	









}

//-----------------------------------------------------------------
void UIWarone::setTime(int time)
{
	unsigned int second=0;
	unsigned int minute=0;
	unsigned int hource=0;

	second=Tools::getValueByBit(time,1);
	minute=Tools::getValueByBit(time,2);
	hource=Tools::getValueByBit(time,3);


	//Tools::parseTime(time*1000,hource,minute,second);

	Ogre::String textureName="jieshu_shuzi_";


	m_HundredTime->setImage(textureName+Ogre::StringConverter::toString(hource)+".png");
	m_TenTime->setImage(textureName+Ogre::StringConverter::toString(minute)+".png");
	m_DigitTime->setImage(textureName+Ogre::StringConverter::toString(second)+".png");




	return;

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