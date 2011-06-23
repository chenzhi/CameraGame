//
//  WarGS.cpp
//  ogreApp
//
//  Created by thcz on 11-6-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//



#include "WarGS.h"
#include  "BulletManager.h"
#include "Application.h"


//------------------------------------
WarGS::WarGS()
:GameState(ST_WAR),m_pBulletManager(NULL),m_pCameraNode(NULL),m_pHeadEntity(NULL)

{
    
}


//------------------------------------
WarGS::~WarGS()
{
    
}




//------------------------------------
void WarGS::begin()
{
    
    m_pBulletManager=new BulletManager();
    
    m_pCameraNode=Application::getSingleton().getMainCameraNode();
    
    initMode();
    
}


//------------------------------------
void WarGS::end()
{
    delete m_pBulletManager;
    
    destroyMode();
}

//------------------------------------
StateType WarGS::update(float time)
{
    
    
    m_pBulletManager->update(time);
    
   // updateMode(time);
    
       
    updateAccelerometer();
    
    
    return GameState::update(time);
    
}

//------------------------------------
void WarGS::beginTouch()
{
    
    Ogre::Matrix3 matrix= m_pCameraNode->getLocalAxes();
        
    m_pBulletManager->fire(m_pCameraNode->getPosition(),Ogre::Vector3(matrix[0][2],matrix[1][2],matrix[2][2]));
    
    

}

//-------------------------------------------------------------------------
void WarGS::initMode()
{
    
    Ogre::SceneNode* pNode= m_pSceneManager->getRootSceneNode()->createChildSceneNode();
   
    m_pHeadEntity=m_pSceneManager->getEntity("Head");
    
    m_pHeadEntity->setVisible(true);
    
    pNode->attachObject(m_pHeadEntity);

    
}


//-------------------------------------------------------------------------
void WarGS::destroyMode()
{

    Ogre::SceneNode* pNode= m_pHeadEntity->getParentSceneNode();
     pNode->detachObject(m_pHeadEntity);
    m_pSceneManager->destroyEntity(m_pHeadEntity);
    m_pSceneManager->getRootSceneNode()->removeAndDestroyChild(pNode->getName());    
    
    
}

//-------------------------------------------------------------------------
void WarGS::updateMode(float time)
{
    
    if(m_pHeadEntity!=NULL&&m_pHeadEntity->getParentSceneNode()!=NULL)
    {
        m_pHeadEntity->getParentSceneNode()->yaw(Ogre::Radian(time));
    }

}


//-------------------------------------------------------------------------
void WarGS::updateAccelerometer()
{
    
    
    //const ofPoint& orientation=ofxAccelerometerHandler::getSingleton().getSmoothOrientation();
    
    Ogre::Vector3 orientation=InputListen::getSingleton().getSmoothAccelerometer();
    
    Ogre::Vector3 gyrco=InputListen::getSingleton().getSmoothGyroscope();
    
    
    //const ofPoint& force=ofxAccelerometerHandler::getSingleton().getForce();
    
    //float x=orientation.z*90;
    
    //－1-- 1之间旋转180度
    
    
    
    Ogre::stringstream stream;
    stream<<"acceler x:"<<orientation.x<<"  "<<"y:"<<orientation.y<<"z:"<<orientation.z;
    Ogre::LogManager::getSingleton().logMessage(stream.str());
    
    
    Ogre::stringstream sstream;
    sstream<<"gyrco x:"<<gyrco.x<<"  "<<"y:"<<gyrco.y<<"z:"<<gyrco.z;
    Ogre::LogManager::getSingleton().logMessage(sstream.str());
    
    
    if(m_pCameraNode!=NULL )
    {
        //m_pCameraNode->resetOrientation();
        
        
        m_pCameraNode->yaw(Ogre::Radian(Ogre::Degree(gyrco.x*3.0f)));
        
        m_pCameraNode->pitch(Ogre::Radian(Ogre::Degree(-gyrco.y*3.0f)));
        
    }
    
    
    ///y轴的移动
    static float st_Y=0.0f;
    
    st_Y+=orientation.y;
    
    //if(m_pCameraNode!=NULL)
    // {
    
    //m_pCameraNode->translate(Ogre::Vector3(-orientation.y*30,0,0));
    // }
    
    
    
    return ;
}
