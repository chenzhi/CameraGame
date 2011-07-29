//
//  WarGS.cpp
//  ogreApp
//
//  Created by thcz on 11-6-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#include "pch.h"
#include "WarGS.h"
#include  "WarManager.h"
#include "Application.h"
#include "ogreapp/inputListen.h"
#include "WarMode.h"
#include "UIWarPause.h"
#include "Config.h"
#include "WarModeThree.h"





//------------------------------------
WarGS::WarGS()
:GameState(ST_WAR),m_pWarManager(NULL),m_pCameraNode(NULL),
m_ActiveWarMode(NULL),m_pUIPause(NULL)
{
    
}


//------------------------------------
WarGS::~WarGS()
{
    
}




//------------------------------------
void WarGS::begin()
{
    
    GameState::begin();

	intiUI();

    
    initVideoTeture();
    
    m_pWarManager=new WarManager();
    
    m_pCameraNode=Application::getSingleton().getMainCameraNode();
 
    ///起用陀螺仪
    InputListen::getSingleton().beginGyroscope();

   ///初始化所有的模式
	initWarMode();
    
}


//------------------------------------
void WarGS::end()
{
    GameState::end();

	destroyWarMode();

	destroyUI();
    SafeDelete(m_pWarManager);   
    ///关闭陀螺仪
    InputListen::getSingleton().endGyroscope();

}

//------------------------------------
StateType WarGS::update(float time)
{
    
    
    m_pWarManager->update(time);
    
            
    updateAccelerometer();
    

	if(m_ActiveWarMode)
	{
		m_ActiveWarMode->update(time);

	}


    
    return GameState::update(time);
    
}

//------------------------------------
void WarGS::beginTouch(int x,int y)
{
   
	if(m_ActiveWarMode)
	{
		m_ActiveWarMode->beginTouch(x,y);
	}

}

//-------------------------------------------------------------------------
void WarGS::initVideoTeture()
{
    
   // Ogre::SceneNode* pNode= m_pSceneManager->getRootSceneNode()->createChildSceneNode();
   
    //m_pHeadEntity=m_pSceneManager->getEntity("Head");
    
   // m_pHeadEntity->setVisible(true);
    
   // pNode->attachObject(m_pHeadEntity);
    
#ifdef __arm__
    
    Ogre::TexturePtr pVideoTexture=ofxiPhoneVideoGrabber::getSingleton().getOgreTexture();
    
    
    Ogre::TexturePtr pTexture=Ogre::TextureManager::getSingleton().getByName("videoTexture_copy");
    if(pTexture.isNull())
    {
       pTexture= Ogre::TextureManager::getSingleton().createManual("videoTexture_copy", "General", 
       Ogre::TEX_TYPE_2D, pVideoTexture->getWidth(), pVideoTexture->getHeight(), 1, 1,pVideoTexture->getFormat());
    }
       
    
    bool b= ofxiPhoneVideoGrabber::getSingleton().getOgreTexture(pTexture);
    if(b)
    {
        Ogre::MaterialPtr pMaterial= Ogre::MaterialManager::getSingleton().getByName("Material_#30_Material_#0_B");
        
        if(pMaterial.isNull()==false)
        {
            Ogre::Pass* pPass= pMaterial->getTechnique(0)->getPass(0);
            pPass->getTextureUnitState(0)->setTextureName(pTexture->getName());
        }

        
    }
  
      
    ofxiPhoneVideoGrabber::getSingleton().startCapture();
    
#endif
    
    
}






//-------------------------------------------------------------------------
void WarGS::updateAccelerometer()
{
    
    Ogre::Vector3 gyrco=InputListen::getSingleton().getGyroscopeData();
    float yawtem=gyrco.y;
   float pitch=gyrco.z;
    
    pitch+=Ogre::Math::PI*0.5f;

    if(m_pCameraNode!=NULL )
    {
        m_pCameraNode->resetOrientation();
        m_pCameraNode->pitch(Ogre::Radian(-pitch));
        m_pCameraNode->yaw(Ogre::Radian(yawtem),Ogre::Node::TS_WORLD);
        
    }

    return ;
 
}


void WarGS::intiUI()
{
	m_pUIPause=new UIWarPause();
	m_pUIPause->init();
	m_pUIPause->setVisible(false);
	Application::getSingleton().registerUI(m_pUIPause);
}

///销毁ui
void WarGS::destroyUI()
{
	Application::getSingleton().destroyUI(m_pUIPause);
	m_pUIPause=NULL;

}


//------------------------------------------------------------------
void WarGS::initWarMode()
{

	WarMode* pMode=new WarModeTwo(this);
	m_WarModeCollect.push_back(pMode);

	pMode=new WarModeThree(this);
	m_WarModeCollect.push_back(pMode);

	unsigned int selectMode=g_userInformation.getWarMode();

	if(selectMode>=m_WarModeCollect.size())
	{
		selectMode=m_WarModeCollect.size()-1;
	}

	m_ActiveWarMode=m_WarModeCollect[selectMode];
	m_ActiveWarMode->start();

	return ;
}

//------------------------------------------------------------------
void WarGS::destroyWarMode()
{
	if(m_ActiveWarMode!=NULL)
	{
		m_ActiveWarMode->end();
	}

	WarModeCollect::iterator it=   m_WarModeCollect.begin();
	WarModeCollect::iterator itend=m_WarModeCollect.end();

	for(;it!=itend;++it)
	{
	   SafeDelete(*it);
	}
	
	m_ActiveWarMode=NULL;
	m_WarModeCollect.clear();
	return ;

}