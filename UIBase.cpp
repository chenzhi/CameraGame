//
//  UIBase.cpp
//  ogreApp
//
//  Created by thcz on 11-7-6.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "UIBase.h"
#include  "FileSystemLayer.h"
#include  "Config.h"



//---------------------------------------------------------------------------------------------
UIBase::UIBase(const std::string& name, const std::string& templateName)
:m_Name(name),m_TemplateName(templateName),m_pParentOverlay(NULL)
{
    
    
}

//---------------------------------------------------------------------------------------------
UIBase::~UIBase()
{
    destroy();   
}


//---------------------------------------------------------------------------------------------
void UIBase::init()
{
 
    m_pParentOverlay=Ogre::OverlayManager::getSingleton().getByName(m_Name);
    
	Ogre::String temPath;


    ///如果没有找到直接读相应文件
    if(m_pParentOverlay==NULL)
    {

#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE
        
        temPath=Ogre::macBundlePath();
        Ogre::LogManager::getSingleton().logMessage(macPath);
        temPath+="/";
        temPath+=g_UIPath;
#else if  OGRE_PLATFORM ==OGRE_PLATFORM_WIN32

		temPath=g_UIPath;

#endif
        //Ogre::DataStreamPtr  pDataStream=Ogre::Root::getSingleton().createFileStream(macPath);
        ///先把文件加入资源组后才能打开
        Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(temPath,"FileSystem",m_Name);
        
        temPath+=m_Name;
        temPath+=".overlay";
        Ogre::DataStreamPtr  pDataStream=Ogre::ResourceGroupManager::getSingletonPtr()->openResource(temPath,m_Name);
        Ogre::OverlayManager::getSingleton().parseScript(pDataStream,"General");
        
        m_pParentOverlay=Ogre::OverlayManager::getSingleton().getByName(m_Name);
        
        if(m_pParentOverlay==NULL)
        {
            Ogre::String error="UIBase::init Failed , can not find overlay file ";
            Ogre::LogManager::getSingleton().logMessage(error);
            //throw(error.c_str());
            //OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, error, "UIBase::init");
        }
        
        
        /*
        Ogre::OverlayManager::OverlayMapIterator it=Ogre::OverlayManager::getSingleton().getOverlayIterator();    
        while (it.hasMoreElements())
        {
            Ogre::Overlay* pOverlay= it.getNext();
            Ogre::String name=pOverlay->getName();
            Ogre::LogManager::getSingleton().logMessage(name);
        }
        
        //*/
        
    }
    
      
    return ;
    
}

//---------------------------------------------------------------------------------------------
void UIBase::destroy()
{
    destroyOverlayAndChiled(m_pParentOverlay);
    m_pParentOverlay=NULL;
    
}


//---------------------------------------------------------------------------------------------
void UIBase::setZorder(unsigned short z)
{
    if(m_pParentOverlay!=NULL)
    {
        m_pParentOverlay->setZOrder(z);
    }
    
    return ;
    
}

//---------------------------------------------------------------------------------------------
unsigned short UIBase::getZorder()const
{
    if(m_pParentOverlay==NULL)
        return 0;
    return m_pParentOverlay->getZOrder();
}

//---------------------------------------------------------------------------------------------
void  UIBase::setVisible(bool b)
{
    if(m_pParentOverlay==NULL)
    {
        return ;
    }
    
    if(b)
    {
      m_pParentOverlay->show();
    }else
    {
        m_pParentOverlay->hide();
    }
}


//---------------------------------------------------------------------------------------------
bool UIBase::isVisible()const
{
    if(m_pParentOverlay==NULL)
    {
        return false;
    }
    return m_pParentOverlay->isVisible();
}


//---------------------------------------------------------------------------------------------
bool UIBase::destroyOverlayElementAndChild(Ogre::OverlayElement* pOverlayElement)
{
    if(pOverlayElement==NULL)
        return false;
    
    Ogre::OverlayContainer* container = dynamic_cast<Ogre::OverlayContainer*>(pOverlayElement);
    if (container)
    {
        std::vector<Ogre::OverlayElement*> toDelete;
        
        Ogre::OverlayContainer::ChildIterator children = container->getChildIterator();
        while (children.hasMoreElements())
        {
            toDelete.push_back(children.getNext());
        }
        
        for (unsigned int i = 0; i < toDelete.size(); i++)
        {
            UIBase::destroyOverlayElementAndChild(toDelete[i]);
        }
    }
    if (pOverlayElement)
    {
        Ogre::OverlayContainer* parent = pOverlayElement->getParent();
        if (parent) parent->removeChild(pOverlayElement->getName());
        Ogre::OverlayManager::getSingleton().destroyOverlayElement(pOverlayElement);
    }

    pOverlayElement=NULL;
    return true;
        
}


//---------------------------------------------------------------------------------------------
bool UIBase::destroyOverlayAndChiled(Ogre::Overlay* pOverlay)
{
    if(pOverlay==NULL)
        return false;
    
    Ogre::OverlayManager* pOverlayManager=Ogre::OverlayManager::getSingletonPtr();
    
    Ogre::Overlay::Overlay2DElementsIterator it=pOverlay->get2DElementsIterator();
    std::vector<Ogre::OverlayContainer*> removeList;
    while (it.hasMoreElements()) 
    {
        Ogre::OverlayContainer* pContainer=it.getNext();
        removeList.push_back(pContainer);
    }
    
    pOverlay->clear();
    
    int removeSize=removeList.size();
    for(int i=0;i<removeSize;++i)
    {
        UIBase::destroyOverlayElementAndChild(removeList[i]);
    }
    
    
    pOverlayManager->destroy(pOverlay);
    return true;
    
}