
#include "pch.h"
#include "Widget.h"




ImageButton::ImageButton(const Ogre::String& name,const Ogre::String& normalTexture,const Ogre::String& pressTexture)
:m_NormalTexture(normalTexture),m_PressTexture(pressTexture),m_State(BS_UP)
{

	mElement = Ogre::OverlayManager::getSingleton().createOverlayElementFromTemplate("cz/ImageButton", "Panel", name);
	
	m_pMaterial=mElement->getMaterial()->clone(name);
	mElement->setMaterialName(name);

	updateState();

}


ImageButton::~ImageButton()
{


}




void ImageButton::_cursorPressed(const Ogre::Vector2& cursorPos)
{

	if (isCursorOver(mElement, cursorPos, 4))
	{
		m_State=BS_DOWN;
		updateState();
	}


}

void ImageButton:: _cursorReleased(const Ogre::Vector2& cursorPos)
{
	if (isCursorOver(mElement, cursorPos, 4))
	{
		m_State=BS_UP;
		updateState();

	}

    

}

void ImageButton::_focusLost()
{

	m_State=BS_UP;
	updateState();

}

void ImageButton::updateState()
{
	if(m_pMaterial.isNull())
	{
		return ;
	}

	if(m_State==BS_UP)
	{

		m_pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(m_NormalTexture);
	
	}else
    {
		m_pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(m_PressTexture);

	}

}



/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

StaticImage::StaticImage(const Ogre::String& name,const Ogre::String& textureName)
{

	mElement = Ogre::OverlayManager::getSingleton().createOverlayElementFromTemplate("cz/ImageButton", "Panel", name);

	m_pMaterial=mElement->getMaterial()->clone(name);
	mElement->setMaterialName(name);
	setImage(textureName);

}


StaticImage::~StaticImage()
{


}


void StaticImage::setImage(const Ogre::String& textureName)
{

	if(m_pMaterial.isNull()==false)
	{
		m_pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(textureName);
	}


}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////