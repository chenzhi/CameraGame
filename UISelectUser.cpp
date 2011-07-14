
#include "pch.h"
#include "UISelectUser.h"
#include  "Widget.h"







UISelectUser::UISelectUser()
:UIBase("UISelectUser","")
{


}


//----------------------------------------
UISelectUser::~UISelectUser()
{


}

//-----------------------------------------------
void  UISelectUser::init()
{

	m_pParentOverlay =Ogre::OverlayManager::getSingleton().create("UISelectUser");
	m_pParentOverlay->show();


	StaticImage* pImage=new StaticImage("SelectUserBackGround","sdk_button_up.png");
	registerWidget(pImage);
	Ogre::OverlayElement* pElment=pImage->getOverlayElement();
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>(pElment));
	pElment->setMetricsMode(Ogre::GMM_RELATIVE);
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	pElment->setVerticalAlignment(Ogre::GVA_TOP);
	pElment->setWidth(1.0f);
	pElment->setHeight(1.0f);















	return ;
}