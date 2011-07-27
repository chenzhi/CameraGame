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
   
	m_ActiveWarMode=new WarModeTwo(this);
   	m_ActiveWarMode->start();

    ///起用陀螺仪
    InputListen::getSingleton().beginGyroscope();

   
    
}


//------------------------------------
void WarGS::end()
{
    GameState::end();

	destroyUI();
    SafeDelete(m_pWarManager);   
	SafeDelete(m_ActiveWarMode);
    ///关闭陀螺仪
    InputListen::getSingleton().endGyroscope();

}

//------------------------------------
StateType WarGS::update(float time)
{
    
    
    m_pWarManager->update(time);
    
    
    ///如果游戏结束重新回到人物校正
    //if(m_pWarManager->isGameEnd())
   // {
    //    setNextStateType(ST_CAPTUREFACE);
   // }
    
         
    updateAccelerometer();
    

	if(m_ActiveWarMode)
	{
		m_ActiveWarMode->update(time);

		if(m_ActiveWarMode->isEnd())
		{
			m_ActiveWarMode->end();
			setNextStateType(ST_CAPTUREFACE);
		}


	}


    
    return GameState::update(time);
    
}

//------------------------------------
void WarGS::beginTouch(int x,int y)
{
    
	/*//
    Ogre::Matrix3 matrix= m_pCameraNode->getLocalAxes();
    
    Ogre::Vector3 dir(matrix[0][2],matrix[1][2],matrix[2][2]);
    ///子弹发送时稍稍向上发送一点
    dir.y-=0.15;
    dir.normalise();
    m_pWarManager->fire(m_pCameraNode->getPosition(),dir);
    //*/
    

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
