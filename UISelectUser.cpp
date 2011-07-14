
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
    
    
    
    
    ///创建左边按钮用来跳到捕获脸的界面。
    ImageButton* pButton=new ImageButton("UISelectUser_GoCapture","sdk_button_up.png","sdk_button_down.png");
    registerWidget(pButton);
    pButton->_assignListener(this);
    pElment=pButton->getOverlayElement();
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>(pElment));
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	//pElment->setWidth(1.0f);
	//pElment->setHeight(1.0f);

    
    
    
    
    
    ///创建五个按钮用来选择已拍照的人物。
    
    //ImageButton* pButton =new ImageButton("SelectUser_1",















	return ;
}