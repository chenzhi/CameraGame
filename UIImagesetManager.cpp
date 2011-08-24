

#include "pch.h"
#include "UIImagesetManager.h"

namespace Ogre
{
template<>
UIImagesetManager* Ogre::Singleton<UIImagesetManager>::ms_Singleton=NULL;
}

//-------------------------------------------------------------
UIImagesetManager::UIImagesetManager()
{



}

//-------------------------------------------------------------	
UIImagesetManager::~UIImagesetManager()
{

	destroyAllImageset();

}


//-------------------------------------------------------------
bool UIImagesetManager::createImageset(const Ogre::String& fileName,const Ogre::String& resourceGroup)
{
	UIImageSet* pset=getImagesetByName(fileName);

	if(pset!=NULL)
		return false;

	UIImageSet* pImageset=NULL;
	try
	{
		pImageset=new UIImageSet(fileName,resourceGroup);
	}
	catch (...)
	{
         SafeDelete(pImageset);
		 return false;
	}
	

	m_ImagesetCollect.push_back(pImageset);

	return true;

}


//-------------------------------------------------------------
UIImageSet* UIImagesetManager::getImagesetByName(const Ogre::String& name) const 
{
	ImagesetCollect::const_iterator it=m_ImagesetCollect.begin();
	ImagesetCollect::const_iterator endit=m_ImagesetCollect.end();


	for(;it!=endit;++it)
	{
		if((*it)->getName()==name)
			return *it;
	}
	return NULL;

	return NULL;

}


//-------------------------------------------------------------
void  UIImagesetManager::destroyImagetset(const Ogre::String& name)
{


	ImagesetCollect::iterator it=m_ImagesetCollect.begin();
	ImagesetCollect::iterator endit=m_ImagesetCollect.end();


	for(;it!=endit;++it)
	{
		if((*it)->getName()==name)
		{
			delete (*it);
			m_ImagesetCollect.erase(it);
			return ;

		}
	}
	return ;
}


///-------------------------------------------------------------
void UIImagesetManager::destroyAllImageset()
{
	ImagesetCollect::const_iterator it=m_ImagesetCollect.begin();
	ImagesetCollect::const_iterator endit=m_ImagesetCollect.end();


	for(;it!=endit;++it)
	{
			delete (*it);
	}

	m_ImagesetCollect.clear();
	return ;
}

///-------------------------------------------------------------
Image* UIImagesetManager::getImageByName(const Ogre::String& name)const 
{
	char  imagesetName[128];
	memset(imagesetName,0,128);
	char  imageName[128];
	memset(imageName,0,128);

	int n= sscanf(name.c_str(),"set:%s image:%s",imagesetName,imageName);

	UIImageSet* pset=getImagesetByName(imagesetName);
	if(pset==NULL)
		return NULL;
	return 	pset->getImageByName(imageName);
}