#include "pch.h"
#include "UILLayout.h"
#include "Tool.h"
#include "Widget.h"




UILayout::UILayout(const Ogre::String& fileName)
:UIBase(fileName,"")
{


}

UILayout::~UILayout()
{

}


void  UILayout::init()
{

	loadLayoutFile(m_Name+".layout");

	return ;
}




//----------------------------------------------------------------------------------
bool  UILayout::loadLayoutFile(const Ogre::String& fileName)
{
	Ogre::DataStreamPtr stream ;
	try
	{

		stream = Ogre::ResourceGroupManager::getSingleton().openResource(fileName, "UI");
	}
	catch(...)
	{

		Ogre::LogManager::getSingleton().logMessage("UIBase::loadLayoutFile error,file name is "+fileName);
		return false;
	}


	rapidxml::xml_document<> XMLDoc;    // character type defaults to char
	rapidxml::xml_node<>* XMLRoot=NULL;

	char* scene = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(scene);


	XMLRoot=XMLDoc.first_node("GUILayout");
	if(XMLRoot==NULL)
	{
		Ogre::LogManager::getSingleton().logMessage( "UIBase::loadLayoutFile error,is not layout format" );
		return false;

	}




	XMLRoot = XMLRoot->first_node("Window");
	if( XMLRoot==NULL)
	{
		Ogre::LogManager::getSingleton().logMessage( "UIBase::loadLayoutFile error,can't find Window node" );
		return false;
	}

	return 	processRootWindow(XMLRoot);

}

//----------------------------------------------------------------------------------
bool UILayout::processRootWindow(rapidxml::xml_node<>* pNode)
{
	Ogre::String Name=Tools::getAttrib(pNode, "Name", "");
	m_pParentOverlay =Ogre::OverlayManager::getSingleton().create(Name);
	m_pParentOverlay->show();


	rapidxml::xml_node<>* pImageNode = pNode->first_node("Window");
	while(pImageNode)
	{
		processWindow(pImageNode);
		pImageNode = pImageNode->next_sibling("Window");
	}

	



	return true;
}

//----------------------------------------------------------------------------------
bool  UILayout::processWindow(rapidxml::xml_node<>* pNode)
{

	Ogre::String typeName=Tools::getAttrib(pNode, "Type", "");
	if(typeName=="")
	{
		return false;
	}

	Ogre::String Name=Tools::getAttrib(pNode, "Name", "");

	if(Name=="")
	{
		return false;
	}

	Ogre::String ImageName=Tools::getAttrib(pNode,"OrzImageNormal","");


	if(typeName=="AdvanceLook/StaticImage")///¾²Ì¬Í¼Æ¬
	{
		Ogre::String ImageName;
		Ogre::String ImageSize;
		getChildProperty(pNode,"OrzImageNormal",ImageName);
		getChildProperty(pNode,"UnifiedAreaRect",ImageSize);
	
		StaticImage* pStaticImage=new StaticImage(Name,ImageName,true);
		Ogre::Vector4 rect;
		ConvertCEGUIRectToOgre(ImageSize,rect);

		pStaticImage->setMetricsMode(Ogre::GMM_RELATIVE);
		pStaticImage->setHorizontalAlignment(Ogre::GHA_LEFT);
		pStaticImage->setVerticalAlignment(Ogre::GVA_TOP);

		pStaticImage->setLeft(rect.x);
		pStaticImage->setTop(rect.y);
		pStaticImage->setWidth(rect.z-rect.x);
		pStaticImage->setHeight(rect.w-rect.y);
		this->registerWidget(pStaticImage);

	}else  if(typeName=="AdvanceLook/Button")///°´Å¥
	{
		//*
		Ogre::String ReleaseImageName;
		Ogre::String pressImageName;
        Ogre::String ImageSize;
		getChildProperty(pNode,"OrzImageNormal",ReleaseImageName);
		getChildProperty(pNode,"OrzImagePushed",pressImageName);
		getChildProperty(pNode,"UnifiedAreaRect",ImageSize);
		

		ImageButton* pbutton=new ImageButton(Name,ReleaseImageName,pressImageName.empty()?ReleaseImageName:pressImageName,true);
		Ogre::Vector4 rect;
		ConvertCEGUIRectToOgre(ImageSize,rect);

		pbutton->setMetricsMode(Ogre::GMM_RELATIVE);
		pbutton->setHorizontalAlignment(Ogre::GHA_LEFT);
		pbutton->setVerticalAlignment(Ogre::GVA_TOP);

		pbutton->setLeft(rect.x);
		pbutton->setTop(rect.y);
		pbutton->setWidth(rect.z-rect.x);
		pbutton->setHeight(rect.w-rect.y);
		this->registerWidget(pbutton);
   //*/

	}


	rapidxml::xml_node<>* pImageNode = pNode->first_node("Property");
	while(pImageNode)
	{
		processProperty(pImageNode);
		pImageNode = pImageNode->next_sibling("Property");
	}


	return true;

}

//----------------------------------------------------------------------------------
bool UILayout::processProperty(rapidxml::xml_node<>* pNode)
{

	Ogre::String propetyName=Tools::getAttrib(pNode, "Name", "");
	Ogre::String ValueName=Tools::getAttrib(pNode, "Value", "");

	return true;

}


//----------------------------------------------------------------------------------
bool  UILayout::getChildProperty(rapidxml::xml_node<>* pNode,const Ogre::String& propertyName, Ogre::String& Value)
{
	if(pNode==NULL)
		return false;

	rapidxml::xml_node<>* pChildNode=pNode->first_node("Property");

	while(pChildNode!=NULL)
	{
		Ogre::String CurrentProperty=Tools::getAttrib(pChildNode,"Name","");
		if(CurrentProperty==propertyName)
		{
			Value  =Tools::getAttrib(pChildNode,"Value","");
			return true;
		}

		pChildNode=pChildNode->next_sibling("Property");

	}

	return false;
}

//----------------------------------------------------------------------------------
bool  UILayout::ConvertCEGUIRectToOgre(const Ogre::String& CEGUICoord,Ogre::Vector4& rect)
{
	using namespace std;
	Ogre::Vector4 temVect;


	int n= sscanf(
		CEGUICoord.c_str(),
		" {{%g,%g},{%g,%g},{%g,%g},{%g,%g}}",
		&rect.x, &temVect.x,
		&rect.y, &temVect.y,
		&rect.z, &temVect.z,
		&rect.w, &temVect.w
		);

	if(n==8)
		return true;
	return false;

}