//
//  CaptureVideoGS.cpp
//  ogreApp
//
//  Created by thcz on 11-6-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "CaptureFaceGS.h"
#include "application.h"
#include  "ofxiPhoneVideoGrabber.h"


CaptureFaceGS::CaptureFaceGS( )
:GameState(ST_CAPTUREFACE)
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
    
   
    
    
}



void  CaptureFaceGS::end( )
{
    GameState::end();
    
    
#if defined  __arm__
    m_pVideo->stopCapture();
    
#endif    
    
    
   // m_BackGround->setVisible(false);
}


/**更新函数*/
StateType CaptureFaceGS::update(float time)
{
    
    updateVideo();
    
    return GameState::update(time);
    
}


void  CaptureFaceGS::beginTouch()
{
    setNextStateType(ST_WAR);
    
    //m_pVideo->stopCapture();
    
    return ;
}


void CaptureFaceGS::initBackGround()
{
    /*
     MeshPtr createPlane(
     const String& name, const String& groupName, const Plane& plane,
     Real width, Real height,
     int xsegments = 1, int ysegments = 1,
     bool normals = true, unsigned short numTexCoordSets = 1,
     Real uTile = 1.0f, Real vTile = 1.0f, const Vector3& upVector = Vector3::UNIT_Y,
     HardwareBuffer::Usage vertexBufferUsage = HardwareBuffer::HBU_STATIC_WRITE_ONLY, 
     HardwareBuffer::Usage indexBufferUsage = HardwareBuffer::HBU_STATIC_WRITE_ONLY,
     bool vertexShadowBuffer = true, bool indexShadowBuffer = true);
     */
    
    float distance=1000.0f;
    float width=0,height=0;
    Ogre::Vector3 camPos=m_pCameraNode->getPosition();
    float fovy= Application::getSingleton().getMainCamera()->getFOVy().valueRadians()*0.5f;
    height=Ogre::Math::Tan(fovy)*distance*2.0f;
    width=Application::getSingleton().getMainCamera()->getAspectRatio()*height;
    
#if defined  __arm__
    float videowidth=m_pVideo->getWidth();
    float videoheight=m_pVideo->getHeight();
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
    pPass->createTextureUnitState()->setTextureName(m_pVideoTexture->getName());
    pPass->setAmbient(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
    
    
    m_BackGround->getSubEntity(0)->setMaterialName(pBackGroundMaterial->getName());
}



//------------------------------------------------------------
void CaptureFaceGS::initVideo()
{
    
#ifndef __arm__
    m_pVideoTexture=Ogre::TextureManager::getSingleton().createManual("videoTexture", "General", Ogre::TEX_TYPE_2D, 512, 512, 1, 1,Ogre::PF_R8G8B8); 
    
#else
    
    
    int width=512,height=512;
    
    m_pVideoTexture=Ogre::TextureManager::getSingleton().createManual("videoTexture", "General", Ogre::TEX_TYPE_2D, width, height, 1, 1,Ogre::PF_R8G8B8); 
    
    m_pVideo= ofxiPhoneVideoGrabber::getSingletonPtr();
    
    m_pVideo->initGrabber(width,height);
    //m_pVideo.stopCapture();
    
    width=m_pVideoTexture->getWidth();
    height=m_pVideoTexture->getHeight();
    
    //Ogre::MaterialPtr pMaterial=Ogre::MaterialManager::getSingleton().getByName("Ogre/Skin");
    //if(pMaterial.isNull()==false)
    ////{
    //  pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("videoTexture");
    //}
    
    return;
#endif

}


/**更新摄像头*/
void CaptureFaceGS::updateVideo()
{
    
    
    
#if defined  __arm__
    
    int width=m_pVideo->getWidth();
    int height=m_pVideo->getHeight();
    
    m_pVideo->draw(0,0);
    
    unsigned char* pPixel=m_pVideo->getPixels();
    
    Ogre::HardwarePixelBufferSharedPtr pPixelBuff= m_pVideoTexture->getBuffer(0,0);
    int yoffset=m_pVideoTexture->getHeight()-height;
	if(pPixelBuff.isNull()==false)
	{
        pPixelBuff->lock(Ogre::HardwareBuffer::HBL_DISCARD);
        const Ogre::PixelBox &pb = pPixelBuff->getCurrentLock();
        
        // size_t height = pb.getHeight();
        // size_t width = pb.getWidth();
        // size_t depth = pb.getDepth();
        size_t rowPitch = pb.rowPitch;
        // size_t slicePitch = pb.slicePitch;
        size_t pixelSize=Ogre::PixelUtil::getNumElemBits(pb.format);
        pixelSize/=8;
        
        rowPitch*=pixelSize;
        Ogre::uint8 *data = static_cast<Ogre::uint8*>(pb.data);
        
        for(int i=0;i<height ;++i)
        {
            unsigned char* pRow=pPixel+i*width*3;
            for(int j=0;j<width;++j)
            {
                data[(i+yoffset)*rowPitch+j*pixelSize]=pRow[j*3];
                data[(i+yoffset)*rowPitch+j*pixelSize+1]=pRow[j*3+1];
                data[(i+yoffset)*rowPitch+j*pixelSize+2]=pRow[j*3+2];
            }
        }
        
        pPixelBuff->unlock();
        
    }
    
#endif
    
    return ;
}



