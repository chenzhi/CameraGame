//
//  UIManager.cpp
//  ogreApp
//
//  Created by thcz on 11-7-7.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "UIManager.h"
#include "UIBase.h" 


//-----------------------------------------------------------------------
UIManager::UIManager()
{
    
}

//-----------------------------------------------------------------------
UIManager::~UIManager()
{
    destroyAllUI();
}


//-----------------------------------------------------------------------
bool UIManager::registerUI(UIBase* pUI)
{
    if(pUI==NULL)
        return false;
    
    
    ///如果没有注册过可以加入队列
    if (getUIByName(pUI->getName())!=NULL)
    {
       // m_UICollect.push_back(pUI);
        return true;
    }
    
	Ogre::LogManager::getSingleton().logMessage
		("UIManger::registerUI failed, has same name ui register .name is "+pUI->getName());

   return false;
    
}


//-----------------------------------------------------------------------
bool  UIManager::unregisterUI(UIBase* pUI)
{
	if(pUI==NULL)
		return false;

	UICollect::iterator it=m_UICollect.begin();
	UICollect::iterator endit=m_UICollect.end();

	for(;it!=endit;++it)
	{

		if((*it)==pUI)
		{
			m_UICollect.erase(it);
			return true;
		}
	}


	return true;
    
}


//-----------------------------------------------------------------------
UIBase* UIManager::getUIByName(const std::string& name)const 
{
	UICollect::const_iterator it=m_UICollect.begin();
	UICollect::const_iterator endit=m_UICollect.end();

	for(;it!=endit;++it)
	{

		if((*it)->getName()==name)
		{
           	return *it;
		}
	}


    return NULL;
}


//-----------------------------------------------------------------------
void UIManager::update(float time)
{
    
	UICollect::iterator it=m_UICollect.begin();
	UICollect::iterator endit=m_UICollect.end();

	for(;it!=endit;++it)
	{
		///可见的才更新
		if((*it)->isVisible())
		{
			(*it)->update(time);
		}
	}

	return ;
}


//-----------------------------------------------------------------------
void UIManager::destroyUI(UIBase* pUI)
{
	if(pUI==NULL)
		return ;

	UICollect::iterator it=m_UICollect.begin();
	UICollect::iterator endit=m_UICollect.end();

	for(;it!=endit;++it)
	{
           if((*it)==pUI)
		   {
			   delete *it;
			   m_UICollect.erase(it);
			   return ;
		   }
	}


  return ;

    
}


//-----------------------------------------------------------------------
void UIManager::destroyUI(const std::string& name)
{
    

	UICollect::iterator it=m_UICollect.begin();
	UICollect::iterator endit=m_UICollect.end();

	for(;it!=endit;++it)
	{
		if((*it)->getName()==name)
		{
			delete *it;
			m_UICollect.erase(it);
			return ;
		}
	}
	return ;

}


//-----------------------------------------------------------------------
void UIManager::destroyAllUI()
{
	UICollect::iterator it=m_UICollect.begin();
	UICollect::iterator endit=m_UICollect.end();

	for(;it!=endit;++it)
	{

		delete (*it);
	}

	m_UICollect.clear();
	return ;
    
}
