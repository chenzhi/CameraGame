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
#include "UISelectUser.h"
#include "Config.h"




CaptureFaceGS::CaptureFaceGS( )
:GameState(ST_CAPTUREFACE),m_BackGround(NULL),m_pCameraNode(NULL),m_pCaptureUI(NULL),
m_pSelectUserUI(NULL)

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




	int userCount=this->getUserFaceCount();





    
    
    ///测试代码
    m_pCaptureUI=new UICaptureFace();
    m_pCaptureUI->init();
    m_pCaptureUI->setVisible(false);
	Application::getSingleton().registerUI(m_pCaptureUI);


	m_pSelectUserUI=new UISelectUser();
	m_pSelectUserUI->init();
	m_pSelectUserUI->setVisible(false);
	Application::getSingleton().registerUI(m_pSelectUserUI);


	if(userCount==0)
	{
        m_pCaptureUI->setVisible(true);

	}else
	{
		m_pSelectUserUI->setVisible(true);
	}
    
   
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

		Application::getSingleton().unregisterUI(m_pSelectUserUI);
		delete m_pSelectUserUI;
		m_pSelectUserUI=NULL;


    }
    
    
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


/**获取已经保存多少个用户的脸图片*/
int CaptureFaceGS::getUserFaceCount()
{
    
  
    std::string userFacePath;
    
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
    
     userFacePath= Ogre::iPhoneDocumentsDirectory();
     //userFacePath+=g_UserFacePath;
#else
    userFacePath=g_UserFacePath;

#endif
    
    
    
	Ogre::Archive* pArchive= Ogre::ArchiveManager::getSingleton().load(userFacePath,"FileSystem");
	
	///如果未打开表示没有用户信息
	if(pArchive==NULL)
	{
           return 0;
	}

	Ogre::StringVectorPtr pStringVector=pArchive->list(false,false);

	int userFaceCount=pStringVector->size();

	Ogre::TexturePtr pTexture=Ogre::TextureManager::getSingleton().getByName("sdk_logo.png");
	Ogre::Image image;
	ConverTextureToImage(pTexture,image);
   
    std::string imagefileName=userFacePath+"/cc.tga";
    Ogre::LogManager::getSingleton().logMessage(imagefileName);
	image.save(imagefileName);


	Ogre::ArchiveManager::getSingleton().unload(pArchive);

	return userFaceCount;
}



/**把一个texture转到image里*/
void CaptureFaceGS::ConverTextureToImage(Ogre::TexturePtr pTexture,Ogre::Image& image)
{
	Ogre::PixelFormat pixelFormat=  pTexture->getFormat();
	
	Ogre::HardwarePixelBufferSharedPtr pBuffer=pTexture->getBuffer();
	pBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
	
    
	const Ogre::PixelBox& pixelBox=pBuffer->getCurrentLock();
	size_t rowPitch=pixelBox.rowPitch;
	size_t height=pTexture->getHeight();
    size_t width=pTexture->getWidth();
    
	size_t size=rowPitch*height*Ogre::PixelUtil::getNumElemBytes(pixelFormat);
    
	Ogre::uchar* pImageBuffer= OGRE_ALLOC_T(Ogre::uchar,size , Ogre::MEMCATEGORY_GENERAL);
	memcpy(pImageBuffer,pixelBox.data,size);
    
	image.loadDynamicImage(pImageBuffer,pTexture->getWidth(),height,1,pixelFormat,true);
    
	pBuffer->unlock();
    
	return ;
    
    
}



