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
:GameState(ST_WAR),m_pBulletManager(NULL),m_pCameraNode(NULL),m_pHeadEntity(NULL),m_pAniState(NULL)

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
    
    updateMode(time);
    
         
    updateAccelerometer();
    
    
    if(m_pAniState!=NULL)
    {
        m_pAniState->addTime(time);
    }
    return GameState::update(time);
    
}

//------------------------------------
void WarGS::beginTouch()
{
    
    Ogre::Matrix3 matrix= m_pCameraNode->getLocalAxes();
    
    Ogre::Vector3 dir(matrix[0][2],matrix[1][2],matrix[2][2]);
    ///子弹发送时稍稍向上发送一点
    dir.y-=0.3;
    dir.normalise();
    m_pBulletManager->fire(m_pCameraNode->getPosition(),dir);
    
    

}

//-------------------------------------------------------------------------
void WarGS::initMode()
{
    
   // Ogre::SceneNode* pNode= m_pSceneManager->getRootSceneNode()->createChildSceneNode();
   
    //m_pHeadEntity=m_pSceneManager->getEntity("Head");
    
   // m_pHeadEntity->setVisible(true);
    
   // pNode->attachObject(m_pHeadEntity);
    
#ifdef __arm__
    
    Ogre::TexturePtr pVideoTexture=ofxiPhoneVideoGrabber::getSingleton().getOgreTexture();
    Ogre::TexturePtr pTexture=Ogre::TextureManager::getSingleton().createManual("videoTexture_copy", "General", 
    Ogre::TEX_TYPE_2D, pVideoTexture->getWidth(), pVideoTexture->getHeight(), 1, 1,Ogre::PF_R8G8B8);
    
    

    pTexture->getBuffer()->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    const Ogre::PixelBox &pTextureBox = pTexture->getBuffer()->getCurrentLock();
    
    
    pVideoTexture->getBuffer()->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    const Ogre::PixelBox& pVideoBox=pVideoTexture->getBuffer()->getCurrentLock();
    
    memcpy(pTextureBox.data,pVideoBox.data,pVideoBox.rowPitch*Ogre::PixelUtil::getNumElemBits(pVideoBox.format)/8*pVideoTexture->getHeight());
    
    pVideoTexture->getBuffer()->unlock();
    pTexture->getBuffer()->unlock();
    
    Ogre::MaterialPtr pMaterial= Ogre::MaterialManager::getSingleton().getByName("03_-_Default_03_-_Default_A");
        
    if(pMaterial.isNull()==false)
    {
        Ogre::Pass* pPass= pMaterial->getTechnique(0)->getPass(0);
        pPass->getTextureUnitState(0)->setTextureName(pTexture->getName());
    }
    
    
#endif
    
    /*Enemy* pEnemy=*/BulletManager::getSingleton().createEnemy(Ogre::Vector3(0,0,0));
    
    
    
   //m_pAniState=m_pHeadEntity->getAnimationState("smile");
   // if(m_pAniState!=NULL)
   // {
   //     m_pAniState->setEnabled(true);
   //     m_pAniState->setLoop(true);
   // }
    
    
    
   // Ogre::SubMesh* psubmesh;
    
    
    
    
   // pNode->setPosition(Ogre::Vector3(0,0,-10));

    
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
    
    //return ;
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
    float x=orientation.z*90;
    
    //－1-- 1之间旋转180度
    static Ogre::Vector3 lastGyro(0.0f,0.0f,0.0f);
    Ogre::Vector3 temGyro=gyrco-lastGyro;
    
    
    ///记录绕Ｙ轴转了多少度
    static float yaw=0.0f;
    
    if(gyrco.x>0)
    {
        if(temGyro.x<0)
        {
            temGyro.x=0;
        }
    
    }else if(gyrco.x<0)
    {
        if(temGyro.x>0)
        {
            temGyro.x=0;
        }
    }
    
    yaw+=(temGyro.x*50.0f);//(180.0f/3.1415926f);
    
    lastGyro=gyrco;
    
   // Ogre::stringstream stream;
   // stream<<"acceler x:"<<orientation.x<<"  "<<"y:"<<orientation.y<<"z:"<<orientation.z;
   // Ogre::LogManager::getSingleton().logMessage(stream.str());
    
    
    //Ogre::stringstream sstream;
    //sstream<<"gyrco x:"<<yaw;//<<"  "<<"y:"<<gyrco.y<<"z:"<<gyrco.z;
    //Ogre::LogManager::getSingleton().logMessage(sstream.str());
    
    
    if(m_pCameraNode!=NULL )
    {
        m_pCameraNode->resetOrientation();
        m_pCameraNode->pitch(Ogre::Radian(Ogre::Degree(x)));
        m_pCameraNode->yaw(Ogre::Radian(Ogre::Degree(yaw)),Ogre::Node::TS_WORLD);

    }
    
   
    

    return ;
}
