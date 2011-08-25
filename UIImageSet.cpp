#include "pch.h"
#include "UIIMageSet.h"
#include "tool.h"


UIImageSet::UIImageSet(const Ogre::String& fileName,const Ogre::String& resourceGroup)
:m_FileName(fileName)
{

	rapidxml::xml_document<> XMLDoc;    // character type defaults to char

	rapidxml::xml_node<>* XMLRoot=NULL;

	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(fileName, resourceGroup);
	char* scene = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(scene);

	XMLRoot = XMLDoc.first_node("Imageset");
	// Validate the File
	if( XMLRoot==NULL)
	{
		Ogre::LogManager::getSingleton().logMessage( "Imagset load faild .can't find imaetset node" );
	    return ;
	}

	m_Name=Tools::getAttrib(XMLRoot,"Name",fileName);

	///解析imageset
	processImageset(XMLRoot,resourceGroup);

	return ;

}


//------------------------------------------------------------------------
UIImageSet::~UIImageSet()
{

	destroyAllImage();

	Ogre::TextureManager::getSingleton().remove(m_pOgreTexture->getHandle());

}


//------------------------------------------------------------------------
const Ogre::String& UIImageSet::getName()const
{

	return m_Name;

}


//------------------------------------------------------------------------
Image*  UIImageSet::getImageByName(const Ogre::String& name)const 
{

	UIImageCollect::const_iterator it= m_ImageCollect.begin();
	UIImageCollect::const_iterator itend= m_ImageCollect.end();
	for(;it!=itend;++it)
	{
	    if((*it)->getName()==name)
		{
			return *it;
		}
	}
	return NULL;

}

//------------------------------------------------------------------------
unsigned  int UIImageSet::getImageCount()const
{

	return m_ImageCollect.size();
}

//------------------------------------------------------------------------
Image*   UIImageSet::getImageByIndex(unsigned int index)const
{
	if(index>=m_ImageCollect.size())
		return NULL;
	return m_ImageCollect[index];

}

//------------------------------------------------------------------------
void UIImageSet::destroyAllImage()
{

	UIImageCollect::iterator it= m_ImageCollect.begin();
	UIImageCollect::iterator itend= m_ImageCollect.end();
	for(;it!=itend;++it)
	{
		delete(*it);
	}
	m_ImageCollect.clear();



}

bool   UIImageSet::addImage(Image* pImage)
{
	if(pImage==NULL)
		return false;

  m_ImageCollect.push_back(pImage);

	return true;

}


bool UIImageSet::processImageset(rapidxml::xml_node<>* XMLRoot,const Ogre::String& resourceGroup)
{
	Ogre::String version = getAttrib(XMLRoot, "Name", "unknown");
	if(version!="unknown")
	{

	}

	m_TextureName = getAttrib(XMLRoot, "Imagefile", "");
	if(m_TextureName.empty()==false)
	{

	}else
	{
		OGRE_EXCEPT(0,"UIImageSet::processImageset","can't find Texture :"+m_TextureName);
		return false;
	}
	m_pOgreTexture=	Ogre::TextureManager::getSingleton().getByName(m_TextureName);
	if(m_pOgreTexture.isNull())
	{
		m_pOgreTexture=Ogre::TextureManager::getSingleton().create(m_TextureName,resourceGroup);
		m_pOgreTexture->load();
	}
	//通过ogre来获取图片的大小
	//m_Rect.x=getAttribReal(XMLRoot,"NativeHorzRes",0.1f);
	//m_Rect.y=getAttribReal(XMLRoot,"NativeVertRes",0.1f);

	//if(m_pOgreTexture.isNull())
	//{
	//	OGRE_EXCEPT(0,"UIImageSet::processImageset","can't create Texture :"+m_TextureName);
	//	return false;
	//}

	
	m_Rect.x=m_pOgreTexture->getWidth();
	m_Rect.y=m_pOgreTexture->getHeight();

	rapidxml::xml_node<>* pImageNode = XMLRoot->first_node("Image");
	while(pImageNode)
	{
		processImage(pImageNode);
		pImageNode = pImageNode->next_sibling("Image");
	}


	return true;
}

/**处理image*/
bool UIImageSet::processImage(rapidxml::xml_node<>* XMLRoot)
{
	Ogre::String imageName=getAttrib(XMLRoot, "Name", "");
	if(imageName=="")
	{
          return false;
	}

	float x=getAttribReal(XMLRoot,"XPos",-1);
	float y=getAttribReal(XMLRoot,"YPos",-1);
	float width=getAttribReal(XMLRoot,"Width",0);
	float height=getAttribReal(XMLRoot,"Height",0);


	Image* pImage=new Image(imageName,this,x/m_Rect.x,y/m_Rect.y,(x+width)/m_Rect.x,(y+height)/m_Rect.y);
	if(addImage(pImage)==false)
	{
		delete pImage;
		return  false;
	}






	return true;
}



Ogre::String UIImageSet::getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, const Ogre::String &defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return XMLNode->first_attribute(attrib.c_str())->value();
	else
		return defaultValue;
}

Ogre::Real UIImageSet::getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, Ogre::Real defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return Ogre::StringConverter::parseReal(XMLNode->first_attribute(attrib.c_str())->value());
	else
		return defaultValue;
}

bool UIImageSet::getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, bool defaultValue)
{
	if(!XMLNode->first_attribute(attrib.c_str()))
		return defaultValue;

	if(Ogre::String(XMLNode->first_attribute(attrib.c_str())->value()) == "true")
		return true;

	return false;
}