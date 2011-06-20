//
//  Application.cpp
//  ogreApp
//
//  Created by iMac on 11-6-15.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "Application.h"
#include "OgreGLESPlugin.h"
#include "OgreParticleFXPlugin.h"

Application::Application()
:m_pRoot(NULL ),m_pRenderWindow(NULL),m_pViewPort(NULL),m_pCamera(NULL),
m_pSceneManager(NULL),m_pFileSystem(NULL),m_pEntity(NULL),m_BackGround(NULL)
{
   
   
}

//----------------------------------------------
Application::~Application()
{
    
    
}


//----------------------------------------------
void Application::init()
{
     initOgreRender();
}

bool initOgrePlugs()
{
    return true;

}

//----------------------------------------------
bool Application::initOgreRender()
{

    m_pRoot=OGRE_NEW Ogre::Root(/*"plugins.cfg","ogre.cfg"*/);
    
    Ogre::Plugin* pPlugin = OGRE_NEW Ogre::GLESPlugin();
    m_pRoot->installPlugin(pPlugin);
    
    
    pPlugin = OGRE_NEW Ogre::ParticleFXPlugin();
    m_pRoot->installPlugin(pPlugin);

    
   if (!m_pRoot->restoreConfig())
   {
       m_pRoot->showConfigDialog();
   }

   // mStaticPluginLoader.load();
    m_pRenderWindow=m_pRoot->initialise(true);
    m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "DummyScene");
    m_pCamera = m_pSceneManager->createCamera("MainCamera");
    m_pCamera->setFarClipDistance(5000);
    m_pRenderWindow->addViewport(m_pCamera);
    m_pViewPort=m_pRenderWindow->getViewport(0);
    
    
    m_pCameraNode=m_pSceneManager->getRootSceneNode()->createChildSceneNode();
    m_pCameraNode->attachObject(m_pCamera);
    m_pCameraNode->setPosition(0.0f,0.0f,200.0f);
    
    if(m_pViewPort!=NULL)
    {
      m_pViewPort->setBackgroundColour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));
    }
    
    m_pFileSystem =new OgreBites::FileSystemLayerImpl(OGRE_VERSION_NAME);
    
    initInputDevice();
    
    initResource();
    
    initScene();
    

    return true;
}

//----------------------------------------------
void Application::initScene()
{
    
   

   
    Ogre::SceneNode* pNode=m_pSceneManager->getRootSceneNode()->createChildSceneNode();

    m_pEntity=m_pSceneManager->createEntity("Head", "ogrehead.mesh");
    pNode->attachObject(m_pEntity);
    
    initVideo();
    
    initBackGround();
    
}

//----------------------------------------------
/**初始化输入设备*/
void Application::initInputDevice()
{
    InputListen::setupInput();
    
    m_Accelerometer =[[Accelerometer alloc] init];
    
}

//-------------------------------------------------
void Application::destroyInputDevice()
{
    [m_Accelerometer release];
}


//----------------------------------------------
void Application::destroyOgreRender()
{
    delete m_pFileSystem;
   // mStaticPluginLoader.unload();
    OGRE_DELETE m_pRoot;
}

//----------------------------------------------
void Application::update(float time)
{
    
    
    if(m_pEntity!=NULL&&m_pEntity->getParentSceneNode()!=NULL)
    {
        m_pEntity->getParentSceneNode()->yaw(Ogre::Radian(time));
    }
    
    updateVideo();
    //InputListen::Captuer();
    
    updateAccelerometer();
    
    m_pRoot->renderOneFrame(time);
}

//----------------------------------------------
void Application::destory()
{
    return ;
}
//--------------------------------------------------------------------
void Application::initResource()
{
    
    // load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(m_pFileSystem->getConfigFilePath("resources.cfg"));
    
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String sec, type, arch;
    
    // go through all specified resource groups
    while (seci.hasMoreElements())
    {
        sec = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        
        // go through all resource paths
        for (i = settings->begin(); i != settings->end(); i++)
        {
            type = i->first;
            arch = i->second;
            
#if /*OGRE_PLATFORM == OGRE_PLATFORM_APPLE ||*/ OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
                arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
#endif
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
        }
    }

    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    
    return ;
}

//----------------------------------------------------------------------
/**初始化摄像头*/
void Application::initVideo()
{
   
#ifndef __arm__
    m_pVideoTexture=Ogre::TextureManager::getSingleton().createManual("videoTexture", "General", Ogre::TEX_TYPE_2D, 512, 512, 1, 1,Ogre::PF_R8G8B8); 

#else
    int width=512,height=512;
    
    m_pVideo.initGrabber(width,height);
    
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

//----------------------------------------------------------------------
/**更新摄像头*/
void Application::updateVideo()
{
    
    
#if defined  __arm__

    int width=m_pVideo.getWidth();
    int height=m_pVideo.getHeight();
    
    m_pVideo.draw(0,0);
    
    unsigned char* pPixel=m_pVideo.getPixels();
    
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
       
}


//-------------------------------------------------------------------------
/**更新重车计数据，控制摄像头运动*/
void Application::updateAccelerometer()
{

    
    const ofPoint& orientation=ofxAccelerometerHandler::getSingleton().getSmoothOrientation();
    
    float x=orientation.z*90;
    
    //－1-- 1之间旋转180度
    
    
    if(m_pCameraNode!=NULL )
    {
        m_pCameraNode->resetOrientation();
        m_pCameraNode->pitch(Ogre::Radian(Ogre::Degree(x)));
    }
    
    
    
    return ;
}

/**初始背影板*/
void Application::initBackGround()
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
    float fovy= m_pCamera->getFOVy().valueRadians()*0.5f;
    height=Ogre::Math::Tan(fovy)*distance*2.0f;
    width=m_pCamera->getAspectRatio()*height;
 
#if defined  __arm__
    float videowidth=m_pVideo.getWidth();
    float videoheight=m_pVideo.getHeight();
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
    pBackNode->setScale(Ogre::Vector3(width*0.9f,height*0.9f,1.0f));
    
    Ogre::MaterialPtr pBackGroundMaterial=Ogre::MaterialManager::getSingleton().create("BackGroundVideomat", "General");
    pBackGroundMaterial->getTechnique(0)->getPass(0)->createTextureUnitState()->setTextureName(m_pVideoTexture->getName());
    m_BackGround->getSubEntity(0)->setMaterialName(pBackGroundMaterial->getName());
    
}