//
//  UIBase.cpp
//  ogreApp
//
//  Created by thcz on 11-7-6.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "UIBase.h"



UIBase::UIBase(const std::string& name, const std::string& templateName)
:m_Name(name),m_TemplateName(templateName),m_pParentOverlay(NULL)
{
    
    
}



UIBase::~UIBase()
{
    
    if(m_pParentOverlay!=NULL)
    {
         
    }
   
    
}

void UIBase::setZorder(unsigned short z)
{
    if(m_pParentOverlay!=NULL)
    {
        m_pParentOverlay->setZOrder(z);
    }
    
    return ;
    
}

/**获取界面z,如果界面未初始返回0*/
unsigned short UIBase::getZorder()const
{
    if(m_pParentOverlay==NULL)
        return 0;
    return m_pParentOverlay->getZOrder();
}




bool UIBase::destroyOverlayAndChild(Ogre::OverlayElement* pOverlayElement)
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
            UIBase::destroyOverlayAndChild(toDelete[i]);
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