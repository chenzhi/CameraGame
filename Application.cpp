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
#include  "CaptureFaceGS.h"
#include "GameState.h"
#include  "WarGS.h"

namespace Ogre
{
  template<> Application* Ogre::Singleton<Application>::ms_Singleton=0;  
}


Application::Application()
:m_pRoot(NULL ),m_pRenderWindow(NULL),m_pViewPort(NULL),m_pCamera(NULL),
m_pSceneManager(NULL),m_pFileSystem(NULL)
{
   
   
}

//----------------------------------------------
Application::~Application()
{
    
    
}




void  Application::initState()
{
    State* pState=new WarGS();
    registerState(pState);
    
    pState= new CaptureFaceGS();
    registerState(pState);
    
    
    
    setBeginState(ST_CAPTUREFACE);
    return;
}




//----------------------------------------------
void Application::init()
{
     initOgreRender();
    
     initState();
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
    
    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
    Ogre::Root::getSingleton().clearEventTimes();
    
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
    
    
#ifdef __arm__
    new ofxiPhoneVideoGrabber();
#endif
    

    return true;
}

//----------------------------------------------
void Application::initScene()
{

    Ogre::Entity* pEntity= m_pSceneManager->createEntity("Head", "ogrehead.mesh");
    pEntity->setVisible(false);
    
}

//----------------------------------------------
/**初始化输入设备*/
void Application::initInputDevice()
{
    m_pInputListen=new InputListen();
    m_pInputListen->setupInput();
    
   // m_Accelerometer =[[Accelerometer alloc] init];
    
    
}

//-------------------------------------------------
void Application::destroyInputDevice()
{
    delete m_pInputListen;
    m_pInputListen=NULL;
   // [m_Accelerometer release];
}


//----------------------------------------------
void Application::destroyOgreRender()
{
    delete m_pFileSystem;
   // mStaticPluginLoader.unload();
    OGRE_DELETE m_pRoot;
    
    
#ifdef __arm__
    delete ofxiPhoneVideoGrabber::getSingletonPtr();
#endif    
}

//----------------------------------------------
void Application::update(float time)
{
    
    StateMachine::update(time);
    
    //updateVideo();
    m_pInputListen->Captuer();

      
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



//-------------------------------------------------------
void Application::TouchBegan()
{
    GameState* pState=static_cast<GameState*>(getCurrentActive());
    if(pState!=NULL)
    {
        pState->beginTouch();
    }
}