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
:m_Name(name),m_TemplateName(templateName),m_pParentOverlay(NULL),m_Flag(0)
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


	m_pParentOverlay =Ogre::OverlayManager::getSingleton().create(m_Name);
	m_pParentOverlay->show();

     return ;
    
}

//---------------------------------------------------------------------------------------------
void UIBase::destroy()
{

	destroyAllWidget();

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
	if(b)
	{
		setFlag(F_SHOW);
	}else
	{
		setFlag(F_HIDE);
	}
   // if(m_pParentOverlay==NULL)
    //{
    //    return ;
   // }

	
  /*  if(b)
    {
      m_pParentOverlay->show();
    }else
    {
        m_pParentOverlay->hide();
    }*/



}


//---------------------------------------------------------------------------------------------
bool UIBase::isVisible()const
{
    if(m_pParentOverlay==NULL||hasFlag(F_HIDE))
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
        if (parent) 
		{
			parent->removeChild(pOverlayElement->getName());
		}

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


/**开始触摸,*/
void  UIBase::onBeginTouch(int x,int y)
{ 
	
	Ogre::Vector2 pos(x,y);
	WidgetCollect::iterator it=m_WidgetCollect.begin();
	WidgetCollect::iterator endit=m_WidgetCollect.end();

	for(;it!=endit;++it)
	{
		(*it)->_cursorPressed(pos);
	}

	return ;


}


/**滑动手指*/
void  UIBase::onMoveTouch(int x,int y)
{


	Ogre::Vector2 pos(x,y);
	WidgetCollect::iterator it=m_WidgetCollect.begin();
	WidgetCollect::iterator endit=m_WidgetCollect.end();

	for(;it!=endit;++it)
	{
		(*it)->_cursorMoved(pos);
	}

	return ;

}


/**手指离开*/
void  UIBase::onEndTouch(int x,int y)
{


	Ogre::Vector2 pos(x,y);
	WidgetCollect::iterator it=m_WidgetCollect.begin();
	WidgetCollect::iterator endit=m_WidgetCollect.end();

	for(;it!=endit;++it)
	{
		if((*it)->isVisible())
		{
           (*it)->_cursorReleased(pos);
		}
		
	}

	return ;

}



/**加入一个控件*/
bool UIBase::registerWidget(Widget* pWidget)
{
	if(pWidget==NULL)
		return false;



	if(getWidgetByName(pWidget->getName())!=NULL)
	{
		Ogre::LogManager::getSingleton().logMessage("UIBase::registerWidget Faild has same name widget ."+pWidget->getName());
		return false;
	}


	Ogre::OverlayContainer*pElement=static_cast<Ogre::OverlayContainer*>(pWidget->getOverlayElement());
	if(pElement!=NULL&&pElement->getParent()==NULL)
	{
		m_pParentOverlay->add2D(pElement );
	}
	m_WidgetCollect.push_back(pWidget);
	pWidget->_assignListener(this);
	return true;
}

//------------------------------------------------------------
bool UIBase::unregisterWidget(Widget* pWidget)
{
	if(pWidget==NULL)
		return false;
	WidgetCollect::iterator it=m_WidgetCollect.begin();
	WidgetCollect::iterator endit=m_WidgetCollect.end();
	for(;it!=endit;++it)
	{

		if((*it)==pWidget)
		{
			m_WidgetCollect.erase(it);
			return true;
		}
	}

	pWidget->_assignListener(NULL);
	m_pParentOverlay->remove2D(static_cast<Ogre::OverlayContainer*>(pWidget->getOverlayElement()));

	return false;
}

/**根据名字获取控件*/
Widget* UIBase::getWidgetByName(const Ogre::String& name)
{
	WidgetCollect::iterator it=m_WidgetCollect.begin();
	WidgetCollect::iterator endit=m_WidgetCollect.end();
	for(;it!=endit;++it)
	{

		if((*it)->getName()==name)
		{
			return *it;
		}
	}

	return NULL;

}

//-----------------------------------------------------------------
void UIBase::destroyAllWidget()
{
	WidgetCollect::iterator it=m_WidgetCollect.begin();
	WidgetCollect::iterator itend=m_WidgetCollect.end();
	for(;it!=itend;++it)
	{

		delete (*it);
	}

	m_WidgetCollect.clear();
	return;


}

void UIBase::destroyWidget(Widget* pWidget)
{

	if(pWidget==NULL)
		return ;

	WidgetCollect::iterator it=m_WidgetCollect.begin();
	WidgetCollect::iterator itend=m_WidgetCollect.end();
	for(;it!=itend;++it)
	{
          if((*it)==pWidget)
		  {
			  delete (*it);
			  m_WidgetCollect.erase(it);
			  return ;
		  }
	}

	return;

}

//--------------------------------------------------------------
void  UIBase::update(float time)
{
	WidgetCollect::iterator it=m_WidgetCollect.begin();
	WidgetCollect::iterator itend=m_WidgetCollect.end();
	for(;it!=itend;++it)
	{
		(*it)->update(time);
	}

	if(hasFlag(F_SHOW)&&m_pParentOverlay!=NULL)
	{
	  m_pParentOverlay->show();
	  removeFlag(F_SHOW);
	}else if(hasFlag(F_HIDE)&&m_pParentOverlay!=NULL)
	{
		m_pParentOverlay->hide();
		removeFlag(F_HIDE);

	}

}