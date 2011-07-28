//
//  CaptureVideoGS.cpp
//  ogreApp
//
//  Created by thcz on 11-6-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "CaptureFaceGS.h"
#include "application.h"
#include  "ogreapp/ofxiPhoneVideoGrabber.h"
#include "UICaptureFace.h"
#include "UISelectUser.h"
#include "Config.h"
#include "Tool.h"
#include "UISelectHead.h"
#include "UISelectFaceMode.h"



CaptureFaceGS::CaptureFaceGS( )
:GameState(ST_CAPTUREFACE),m_BackGround(NULL),m_pCameraNode(NULL),m_pCaptureUI(NULL),
m_pSelectUserUI(NULL),m_pSelectHeadUI(NULL),m_pSelectFaceUI(NULL)

{
    
}


CaptureFaceGS::~CaptureFaceGS()
{
    
}


void  CaptureFaceGS::begin( )
{
    GameState::begin();
    
    m_pCameraNode=Application::getSingleton().getMainCameraNode();
	m_pCameraNode->setOrientation(Ogre::Quaternion::IDENTITY);
    
#if defined  __arm__
   // initVideo();
   // initBackGround(); 
#endif

	///创建ui
	initUI();


   
    
}



void  CaptureFaceGS::end( )
{
    GameState::end();
    
    
       
    
#if defined  __arm__
    
   // m_BackGround->setVisible(false);
 // destroyBackGround(); 
    
  ofxiPhoneVideoGrabber::getSingleton().stopCapture();
    
#endif    


	destroyUI();
    
}


/**更新函数*/
StateType CaptureFaceGS::update(float time)
{
    
    
    return GameState::update(time);
    
}


void  CaptureFaceGS::beginTouch(int x,int y)
{
   // setNextStateType(ST_WAR);
    
    return ;
}


void CaptureFaceGS::initBackGround()
{
    
    ///如果已经创建了直接返回
    if(m_BackGround!=NULL)
        return ;
    
    float distance=20.0f;
    float width=0,height=0;
    Ogre::Vector3 camPos=m_pCameraNode->getPosition();
    float fovy= Application::getSingleton().getMainCamera()->getFOVy().valueRadians()*0.5f;
    height=Ogre::Math::Tan(fovy)*distance*2.0f;
    width=Application::getSingleton().getMainCamera()->getAspectRatio()*height;
    
#if defined  __arm__
    float videowidth=ofxiPhoneVideoGrabber::getSingleton().getWidth();
    float videoheight=ofxiPhoneVideoGrabber::getSingleton().getHeight();
    float textWidth=m_pVideoTexture->getWidth();
    float texheight=m_pVideoTexture->getHeight();
#else
    float videowidth=480;
    float videoheight=360;
    float textWidth=512;
    float texheight=512;
    
#endif
    
    
    
    Ogre::Plane plane(Ogre::Vector3(0.0f,0.0f,1.0f),Ogre::Vector3(0.0f,0.0f,0.0f));
    Ogre::MeshPtr pMesh= Ogre::MeshManager::getSingleton().
    createPlane("backVideo", "General", plane,1,1,1,1,false,1,videowidth/textWidth,videoheight/texheight);
    
    
    m_BackGround=m_pSceneManager->createEntity("videoBackGround", pMesh->getName());
    Ogre::SceneNode* pBackNode=m_pCameraNode->createChildSceneNode();
    pBackNode->attachObject(m_BackGround);
    pBackNode->setPosition(0,0,-distance);
    pBackNode->setScale(Ogre::Vector3(width,height,1.0f));
    
    Ogre::MaterialPtr pBackGroundMaterial=Ogre::MaterialManager::getSingleton().create("BackGroundVideomat", "General");
    
    Ogre::Pass*pPass=pBackGroundMaterial->getTechnique(0)->getPass(0);
    
#if defined  __arm__
    Ogre::TexturePtr pVideoTexture=ofxiPhoneVideoGrabber::getSingleton().getOgreTexture();
    pPass->createTextureUnitState()->setTextureName(pVideoTexture->getName());
#else
    pPass->createTextureUnitState()->setTextureName("videoTexture_ofxiPhoneVideoGrabber");

#endif
    pPass->setAmbient(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
    
    m_BackGround->getSubEntity(0)->setMaterialName(pBackGroundMaterial->getName());
    
#ifndef __arm__
    m_BackGround->setVisible(false);
#endif
}
            



void CaptureFaceGS::destroyBackGround()
{
    //m_pSceneManager
    
    
    
    Ogre::SceneNode* pNode=m_BackGround->getParentSceneNode();
    pNode->detachAllObjects();
    pNode->getParentSceneNode()->removeAndDestroyChild(pNode->getName());
    m_pSceneManager->destroyEntity(m_BackGround);
    m_BackGround=NULL;

    
}

//------------------------------------------------------------
void CaptureFaceGS::initVideo()
{
    
#ifdef __arm__
    
    m_pVideoTexture=ofxiPhoneVideoGrabber::getSingleton().getOgreTexture();
    
#endif    
    return ;
    
}


/**更新摄像头*/
void CaptureFaceGS::updateVideo()
{
    
    return ;
    

}






void  CaptureFaceGS::initUI()
{


	///获取有多少个用户数据。
	Ogre::StringVectorPtr pFileList=Tools::getUserFaceFileList();





	///测试代码
	m_pCaptureUI=new UICaptureFace();
	m_pCaptureUI->init();
	m_pCaptureUI->setVisible(false);
	m_pCaptureUI->setUserCount(pFileList->size());
	Application::getSingleton().registerUI(m_pCaptureUI);


	m_pSelectUserUI=new UISelectUser();
	m_pSelectUserUI->init();
	m_pSelectUserUI->setVisible(false);
	Application::getSingleton().registerUI(m_pSelectUserUI);
	m_pSelectUserUI->setUserList(pFileList);///设置用户头像

	if(pFileList->empty())
	{
		m_pCaptureUI->setVisible(true);

	}
    else
	{
		m_pSelectUserUI->setVisible(true);
	}

	


///---------------------------选择头套
	m_pSelectHeadUI=new UISelectHead();
	m_pSelectHeadUI->init();
	m_pSelectHeadUI->setVisible(true);
	Application::getSingleton().registerUI(m_pSelectHeadUI);
	m_pSelectHeadUI->setVisible(false);


///-------------------选择模型
	m_pSelectFaceUI=new UISelectFaceMode();
	m_pSelectFaceUI->init();
	m_pSelectFaceUI->setVisible(false);
	Application::getSingletonPtr()->registerUI(m_pSelectFaceUI);
	




}


void  CaptureFaceGS::destroyUI()
{
	Application* pApp=Application::getSingletonPtr();

	pApp->destroyUI(m_pCaptureUI);
	m_pCaptureUI=NULL;

	pApp->destroyUI(m_pSelectUserUI);
	m_pSelectUserUI=NULL;

	pApp->destroyUI(m_pSelectHeadUI);
	m_pSelectHeadUI=NULL;

	pApp->destroyUI(m_pSelectFaceUI);
	m_pSelectFaceUI=NULL;
}
