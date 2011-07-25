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
	



	UIBase::init();


	Ogre::OverlayElement* pElement=NULL;
	///创建脸部校正图片
	CaptureImage* pImage=new CaptureImage("CaptureBackGround");
	registerWidget(pImage);
	//pElement=pImage->getOverlayElement();
	//pElement->setMetricsMode(Ogre::GMM_RELATIVE);
	//pElement->setHorizontalAlignment(Ogre::GHA_LEFT);
	//pElement->setVerticalAlignment(Ogre::GVA_TOP);
	//pElement->setWidth(1.0f);
	//pElement->setHeight(1.0f);



	////回到用户选择按钮
	m_pToUserFace=new ImageButton("ToCaptureFace","paizhao_sanjiao_press.png","paizhao_sanjiao_release.png");
	registerWidget(m_pToUserFace);
	pElement=m_pToUserFace->getOverlayElement();
	pElement->setHorizontalAlignment(Ogre::GHA_RIGHT);
	pElement->setLeft(-pElement->getWidth()-100);
	m_pToUserFace->setTop(-64);


	///拍照铵钮
	m_pCaptureButton=new ImageButton("CaptureFaceButton","paizhao_paizhao_press.png","paizhao_paizhao_release.png");
	registerWidget(m_pCaptureButton);
	pElement=m_pCaptureButton->getOverlayElement();
	//pElement->setHorizontalAlignment(Ogre::GHA_RIGHT);
	//pElement->setVerticalAlignment(Ogre::GVA_BOTTOM);
	int width=160;
	int height=160;
    m_pCaptureButton->setWidth(width);
	m_pCaptureButton->setHeight(height);
	m_pCaptureButton->setLeft(-width*0.5f);
	m_pCaptureButton->setTop(150);


	///返回上一层按钮
	m_pGoBackButton=new ImageButton("CaptureFaceGoBackButton","moshi_fanhui_press.png","moshi_fanhui_release.png");
	registerWidget(m_pGoBackButton);
	m_pGoBackButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_pGoBackButton->setLeft(10);
	m_pGoBackButton->setVerticalAlignment(Ogre::GVA_BOTTOM);
	m_pGoBackButton->setTop(-128);
	m_pGoBackButton->setWidth(80);
	m_pGoBackButton->setHeight(80);


	
	return ;


}



///设置已经有多少个用户了
void UICaptureFace::setUserCount(unsigned int count)
{
	m_UserCount=count;
}


 void UICaptureFace::buttonHit(Button* button)
{
	Ogre::String name=	button->getName();
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
      
		 UIBase* pSelectHead=Application::getSingletonPtr()->getUIByName("UISelectHead");

	//	
#ifdef _arm_


#endif

		 pSelectHead->setVisible(true);
		 setVisible(false);
       // Application::getSingleton().getCurrentActive()->setNextStateType(ST_WAR);

	 }

	return ;

}