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
#include  "ofxiPhoneVideoGrabber.h"
#include "UICaptureFace.h"



CaptureFaceGS::CaptureFaceGS( )
:GameState(ST_CAPTUREFACE),m_BackGround(NULL),m_pCameraNode(NULL),m_pCaptureUI(NULL)

{
    
}


CaptureFaceGS::~CaptureFaceGS()
{
    
}


void  CaptureFaceGS::begin( )
{
    GameState::begin();
    
    m_pCameraNode=Application::getSingleton().getMainCameraNode();
    initVideo();
    initBackGround(); 
    
    
    ///测试代码
    m_pCaptureUI=new UICaptureFace();
    m_pCaptureUI->init();
    m_pCaptureUI->setVisible(true);
	Application::getSingleton().registerUI(m_pCaptureUI);
    
   
    //m_pCaptureOverlay=Ogre::OverlayManager::getSingleton().getByName("CaptureFace");
    //if(m_pCaptureOverlay!=NULL)
    //{
    //    m_pCaptureOverlay->show();
   // }
    
    
   
    
}



void  CaptureFaceGS::end( )
{
    GameState::end();
    
    if(m_BackGround!=NULL)
    {
        //m_BackGround->setVisible(false);
    }
    
    
#if defined  __arm__
  //ofxiPhoneVideoGrabber::getSingleton().stopCapture();
    
#endif    
    
    if(m_pCaptureUI!=NULL)
    {
		Application::getSingleton().unregisterUI(m_pCaptureUI);
        delete m_pCaptureUI;
        m_pCaptureUI=NULL;
    }
    
    
}


/**更新函数*/
StateType CaptureFaceGS::update(float time)
{
    
    
    return GameState::update(time);
    
}


void  CaptureFaceGS::beginTouch(int x,int y)
{
    setNextStateType(ST_WAR);
    
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



