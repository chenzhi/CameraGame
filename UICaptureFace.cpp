//
//  UICaptureFace.cpp
//  ogreApp
//
//  Created by thcz on 11-7-7.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "UICaptureFace.h"


UICaptureFace::UICaptureFace()
:UIBase("CaptureFaceUI","")
{
    
}



UICaptureFace::~UICaptureFace()
{
    
}


/**初始化*/
void UICaptureFace::init()
{
	UIBase::init();


	//Button* pButton=SdkTrayManager::getSingleton().createButton(TL_CENTER,"buttontest","434534");


	Button* pButton=new Button("testButton","cilck1",100);
	pButton->getOverlayElement()->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>( pButton->getOverlayElement()));
	pButton->_assignListener(this);
	registerWidget(pButton);



	pButton=new Button("testButton1","cilck2",20);
	pButton->getOverlayElement()->setHorizontalAlignment(Ogre::GHA_CENTER);
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>( pButton->getOverlayElement()));
	pButton->_assignListener(this);
	registerWidget(pButton);



	pButton=new Button("testButton2","cilck3",300);
	pButton->getOverlayElement()->setHorizontalAlignment(Ogre::GHA_LEFT);
	
	if(pButton->getOverlayElement()->getMetricsMode()==Ogre::GMM_RELATIVE)
	{
      	pButton->getOverlayElement()->setLeft(0.7f);
	}else
	{
      	pButton->getOverlayElement()->setLeft(300);
	}
	pButton->show();

	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>( pButton->getOverlayElement()));
	pButton->_assignListener(this);
    registerWidget(pButton);


	



	return ;
}


/**开始触摸,*/
void UICaptureFace::onBeginTouch(int x,int y)
{
	UIBase::onBeginTouch(x,y);

	return ;
}


/**滑动手指*/
void UICaptureFace::onMoveTouch(int x,int y)
{
	UIBase::onMoveTouch(x,y);
  return ;
}


/**手指离开*/
void UICaptureFace::onEndTouch(int x,int y)
{
	UIBase::onEndTouch(x,y);
	return ;
}

 void UICaptureFace::buttonHit(Button* button)
{
	Ogre::String name=	button->getName();
	return ;
}