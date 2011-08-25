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
#include  "Tool.h"
#include   "config.h"
#include "ogreapp/ofxiPhoneVideoGrabber.h"


UICaptureFace::UICaptureFace()
:UILayout("zhaoxiang")/*,m_pToUserFace(NULL),m_pGoBackButton(NULL),m_pCaptureButton(NULL)*/
,m_UserCount(0),m_pCaptureButton(NULL),m_pFullWidget(NULL)
{
    
}



UICaptureFace::~UICaptureFace()
{
    
}


/**初始化*/
void UICaptureFace::init()
{
	



	UILayout::init();

#ifdef	__arm__
	//const Ogre::String& CameraImage=ofxiPhoneVideoGrabber::getSingleton().getOgreTexture()->getName();
	CameraVideoImage* pCameraImage=new CameraVideoImage("CameraCapterImage");
	registerWidget(pCameraImage);
    /*
	pCameraImage->setHorizontalAlignment(Ogre::GHA_LEFT);
	pCameraImage->setVerticalAlignment(Ogre::GVA_TOP);
	pCameraImage->setMetricsMode(Ogre::GMM_RELATIVE);
	pCameraImage->setLeft(0);
	pCameraImage->setTop(0);
	pCameraImage->setWidth(1.0f);
	pCameraImage->setHeight(1.0f);
    //*/

#endif


	m_pCaptureButton=getWidgetByName("zhaoxiang/zhaoxiangpaizhaojian");
	m_pFullWidget=getWidgetByName("zhaoxiang/zhaoxiangjifull");

	return ;

	
/*


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
	m_pToUserFace=new ImageButton("ToCaptureFace","paizhao_sanjiao_release.png","paizhao_sanjiao_press.png");
	registerWidget(m_pToUserFace);
	m_pToUserFace->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_pToUserFace->setLeft(-95);
	m_pToUserFace->setTop(-40);
	m_pToUserFace->setWidth(60);
	m_pToUserFace->setHeight(60);
	///拍照铵钮
	m_pCaptureButton=new ImageButton("CaptureFaceButton","paizhao_paizhao_release.png","paizhao_paizhao_press.png");
	registerWidget(m_pCaptureButton);
	int width=160;
	int height=160;
    m_pCaptureButton->setWidth(width);
	m_pCaptureButton->setHeight(height);
	m_pCaptureButton->setLeft(-width*0.5f);
	m_pCaptureButton->setTop(150);


	///返回上一层按钮
	m_pGoBackButton=new ImageButton("CaptureFaceGoBackButton,","moshi_fanhui_release.png","moshi_fanhui_press.png");
	registerWidget(m_pGoBackButton);
	m_pGoBackButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_pGoBackButton->setLeft(10);
	m_pGoBackButton->setVerticalAlignment(Ogre::GVA_BOTTOM);
	m_pGoBackButton->setTop(-100);
	m_pGoBackButton->setWidth(80);
	m_pGoBackButton->setHeight(80);
    
    
//*/
	
	return ;


}

//--------------------------------------------------
void  UICaptureFace::setVisible(bool b)
{
    UIBase::setVisible(b);

#ifdef __arm__
    if(b)
    {
        ofxiPhoneVideoGrabber::getSingleton().startCapture();
    }else
    {
        ofxiPhoneVideoGrabber::getSingleton().stopCapture();
    }

#endif


	if(m_UserCount>6)
	{
		m_pFullWidget->show();
		m_pCaptureButton->hide();

	}else
	{

		m_pCaptureButton->show();
		m_pFullWidget->hide();
	}




}


///-------------------------------------------------------------
void UICaptureFace::setUserCount(unsigned int count)
{ 
	m_UserCount=count;
}

///-------------------------------------------------------------
void UICaptureFace::buttonHit(Widget* button)
{
	const Ogre::String WidgetName=button->getName();

     if(WidgetName=="zhaoxiang/")
	 {

		 UIBase* pSelectUser=Application::getSingleton().getUIByName("tukumoshi");
		 assert(pSelectUser);
		 setVisible(false);
		 pSelectUser->setVisible(true);

	 }else if(WidgetName=="zhaoxiang/zhaoxiangfanhui")//返回到模式选择
	 {
		 Application::getSingleton().getCurrentActive()->setNextStateType(ST_SELECTMODE);
		 return ;


	 }else if(WidgetName=="zhaoxiang/zhaoxiangpaizhaojian")///拍照并保存
	 {
      
		 UIBase* pSelectHead=Application::getSingletonPtr()->getUIByName("toutaoxuanzejiemian");

	//	
#ifdef __arm__
         ///根据系统时间创建贴图名
         
         time_t tp;
         char* str=NULL;
         time(&tp);
         str=ctime(&tp);

         Ogre::String userName="userName";
         userName+=str;
            
        Ogre::TexturePtr pVideoTexture=ofxiPhoneVideoGrabber::getSingleton().getOgreTexture();
               
        Ogre::TexturePtr pTexture= Ogre::TextureManager::getSingleton().createManual
         (userName, "General", Ogre::TEX_TYPE_2D, pVideoTexture->getWidth(), pVideoTexture->getHeight(),
          1, 1,pVideoTexture->getFormat()/*,Ogre::TU_DYNAMIC_WRITE_ONLY*/);
         
         bool b= ofxiPhoneVideoGrabber::getSingleton().getOgreTexture(pTexture);
      
#else        
        Ogre::TexturePtr pTexture=Ogre::TextureManager::getSingleton().getByName("face_front_1.png");
        //Ogre::TexturePtr pTexture= Ogre::TextureManager::getSingleton().createManual("testFace", "General", 
                   // Ogre::TEX_TYPE_2D, 512, 512, 1, 1,Ogre::PF_R8G8B8A8);

#endif  
         Ogre::String userFacepath= Tools::getUserFacePath();
         userFacepath+="/";
       
         
#ifdef __arm__
         
         Ogre::String fileName=userFacepath+pTexture->getName()+".png";
         ofxiPhoneVideoGrabber::getSingleton().saveTexture(fileName.c_str());
         //Tools::saveOgreTexture(fileName.c_str(), pTexture);
         g_userInformation.setUserImage(pTexture->getName());
         Ogre::LogManager::getSingleton().logMessage("set user image is "+pTexture->getName());
         
#else
         //Ogre::String fileName=userFacepath+pTexture->getName();
       //  g_userInformation.setUserImage(pTexture->getName());
       
                
#endif
		 pSelectHead->setVisible(true);
		 setVisible(false);

	 }

	return ;

}