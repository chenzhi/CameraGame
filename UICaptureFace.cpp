//
//  UICaptureFace.cpp
//  ogreApp
//
//  Created by thcz on 11-7-7.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "UICaptureFace.h"
#include "Widget.h"
#include "Application.h"


UICaptureFace::UICaptureFace()
:UIBase("CaptureFaceUI",""),m_pToUserFace(NULL),m_pGoBackButton(NULL),m_pCaptureButton(NULL)
{
    
}



UICaptureFace::~UICaptureFace()
{
    
}


/**初始化*/
void UICaptureFace::init()
{
	

	initUI();



	return ;
}



///设置已经有多少个用户了
void UICaptureFace::setUserCount(unsigned int count)
{
	m_UserCount=count;
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


//-----------------------------------------------
void  UICaptureFace::initUI()
{



	UIBase::init();


	Ogre::OverlayElement* pElement=NULL;
	///创建脸部校正图片
	StaticImage* pImage=new StaticImage("CaptureBackGround","CaptureFace.png");
	registerWidget(pImage);
	pElement=pImage->getOverlayElement();
	pElement->setMetricsMode(Ogre::GMM_RELATIVE);
	pElement->setHorizontalAlignment(Ogre::GHA_LEFT);
	pElement->setVerticalAlignment(Ogre::GVA_TOP);
	pElement->setWidth(1.0f);
	pElement->setHeight(1.0f);
	


  ////回到用户选择按钮
	m_pToUserFace=new ImageButton("ToCaptureFace","sdk_label.png","sdk_frame.png");
	registerWidget(m_pToUserFace);
	pElement=m_pToUserFace->getOverlayElement();
	pElement->setHorizontalAlignment(Ogre::GHA_RIGHT);
	pElement->setLeft(-pElement->getWidth()-100);


	///拍照铵钮
    m_pCaptureButton=new ImageButton("CaptureFaceButton","sdk_frame.png","sdk_label.png");
	registerWidget(m_pCaptureButton);
	pElement=m_pCaptureButton->getOverlayElement();
	pElement->setHorizontalAlignment(Ogre::GHA_RIGHT);
	pElement->setVerticalAlignment(Ogre::GVA_BOTTOM);
	int width=pElement->getWidth();
	int height=pElement->getHeight();
	pElement->setLeft(-width-100);
	pElement->setTop(-height-100);


	///返回上一层按钮
	 m_pGoBackButton=new ImageButton("CaptureFaceGoBackButton","sdk_button_down.png","sdk_button_over.png");
	 registerWidget(m_pGoBackButton);
     pElement=m_pGoBackButton->getOverlayElement();
	 pElement->setHorizontalAlignment(Ogre::GHA_LEFT);
	 pElement->setVerticalAlignment(Ogre::GVA_BOTTOM);
	 pElement->setLeft(200);
	 pElement->setTop(-height-100);


	return ;
}

 ///-------------------------------------------------------------
void  UICaptureFace::destroyUI()
{

	

	return ;
}


 ///-------------------------------------------------------------
void UICaptureFace::buttonHit(Widget* button)
{
     if(button==m_pToUserFace)
	 {

		 UIBase* pSelectUser=Application::getSingleton().getUIByName("UISelectUser");
		 assert(pSelectUser);
		 setVisible(false);
		 pSelectUser->setVisible(true);

	 }else if(button==m_pGoBackButton)//返回到模式选择
	 {
		 Application::getSingleton().getCurrentActive()->setNextStateType(ST_SELECTMODE);
		 return ;


	 }else if(button==m_pCaptureButton)///拍照并保存
	 {
      
       /// Application::getSingleton().getCurrentActive()->setNextStateType(ST_GAMEPLAY);

	 }

	return ;

}