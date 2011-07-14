#include "pch.h"
#include "UISelectMode.h"
#include "Widget.h"
#include "Config.h"
#include "Application.h"


UISelectMode::UISelectMode()
:UIBase("UISelectMode","")
{



}



UISelectMode::~UISelectMode()
{


}



/**³õÊ¼»¯*/
void UISelectMode::init()
{
	m_pParentOverlay =Ogre::OverlayManager::getSingleton().create("UISelectMode");
	m_pParentOverlay->show();


	StaticImage* pImage=new StaticImage("SelectModeBackGround","sdk_mini_text_box_over.png");
	registerWidget(pImage);
	Ogre::OverlayElement* pElment=pImage->getOverlayElement();
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>(pElment));
	pElment->setMetricsMode(Ogre::GMM_RELATIVE);
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	pElment->setVerticalAlignment(Ogre::GVA_TOP);
	pElment->setWidth(1.0f);
	pElment->setHeight(1.0f);




	ImageButton* pPlayButton=new ImageButton("SelectMode_1","sdk_logo.png","sdk_button_down.png");
	registerWidget(pPlayButton);
	pElment=pPlayButton->getOverlayElement();
	pPlayButton->_assignListener(this);
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	float width=pElment->getWidth();
	float height=pElment->getHeight();
	pElment->setLeft(100);
	pElment->setTop(height*(-0.5f));
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>(pElment));



	pPlayButton=new ImageButton("SelectMode_2","sdk_logo.png","sdk_button_down.png");
	registerWidget(pPlayButton);
	pElment=pPlayButton->getOverlayElement();
	pPlayButton->_assignListener(this);
	pElment->setHorizontalAlignment(Ogre::GHA_CENTER);
	width=pElment->getWidth();
	height=pElment->getHeight();
	pElment->setLeft(width*(-0.5f));
	pElment->setTop(height*(-0.5f));
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>(pElment));



	pPlayButton=new ImageButton("SelectMode_3","sdk_logo.png","sdk_button_down.png");
	registerWidget(pPlayButton);
	pElment=pPlayButton->getOverlayElement();
	pPlayButton->_assignListener(this);
	pElment->setHorizontalAlignment(Ogre::GHA_RIGHT);
	width=pElment->getWidth();
	height=pElment->getHeight();
	pElment->setLeft(-width-100.0f);
	pElment->setTop(height*(-0.5f));
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>(pElment));











	return ;
}

void UISelectMode::buttonHit(Widget* button)
{
	const  Ogre::String&  name=button->getName();
	if(name=="SelectMode_1")
	{
     g_UserMode=1;

	}else if(name=="SelectMode_2")
	{

		g_UserMode=2;

	}else if(name=="SelectMode_3")
	{

		g_UserMode=3;

	}



	Application::getSingleton().getCurrentActive()->setNextStateType(ST_CAPTUREFACE);

	return ;


}