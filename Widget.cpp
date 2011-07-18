
#include "pch.h"
#include "Widget.h"



//-------------------------------------------------------------------------------------------
ImageButton::ImageButton(const Ogre::String& name,const Ogre::String& normalTexture,const Ogre::String& pressTexture)
:m_NormalTexture(normalTexture),m_PressTexture(pressTexture),m_State(BS_UP)
{

	mElement = Ogre::OverlayManager::getSingleton().createOverlayElementFromTemplate("cz/ImageButton", "Panel", name);
	
	m_pMaterial=Ogre::MaterialManager::getSingleton().getByName(name);
	if(m_pMaterial.isNull())
	{
    	m_pMaterial=mElement->getMaterial()->clone(name);
	}
	mElement->setMaterialName(m_pMaterial->getName());

	updateState();

}

//-------------------------------------------------------------------------------------------
ImageButton::~ImageButton()
{

	Ogre::MaterialManager::getSingleton().remove(m_pMaterial->getHandle());


}



//-------------------------------------------------------------------------------------------
void ImageButton::_cursorPressed(const Ogre::Vector2& cursorPos)
{

	if (isCursorOver(mElement, cursorPos, 4))
	{
		m_State=BS_DOWN;
		updateState();
	}


}


//-------------------------------------------------------------------------------------------
void ImageButton:: _cursorReleased(const Ogre::Vector2& cursorPos)
{
	
	m_State=BS_UP;
	updateState();

	if (isCursorOver(mElement, cursorPos, 4))
	{
		if(mListener!=NULL)
		{
			mListener->buttonHit(this);
		}

	}

    

}

//-------------------------------------------------------------------------------------------
void ImageButton::_focusLost()
{

	m_State=BS_UP;
	updateState();

}


//-------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------
StaticImage::StaticImage(const Ogre::String& name,const Ogre::String& textureName)
{

	mElement = Ogre::OverlayManager::getSingleton().createOverlayElementFromTemplate("cz/ImageButton", "Panel", name);

	m_pMaterial=Ogre::MaterialManager::getSingleton().getByName(name);
	if(m_pMaterial.isNull())
	{
		m_pMaterial=mElement->getMaterial()->clone(name);
	}

	mElement->setMaterialName(m_pMaterial->getName());
	setImage(textureName);

}

//-------------------------------------------------------------------------------------------
StaticImage::~StaticImage()
{
 
		Ogre::MaterialManager::getSingleton().remove(m_pMaterial->getHandle());

}

//-------------------------------------------------------------------------------------------
void StaticImage::setImage(const Ogre::String& textureName)
{

	if(m_pMaterial.isNull()==false)
	{
		m_pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(textureName);
	}


}


////////////////////////////////////////////////////////////////////////////////
//长按图片按钮,按下时间超过指定时间会发出事件
////////////////////////////////////////////////////////////////////////////////

TimeImageButton::TimeImageButton(const Ogre::String&name,const Ogre::String& imageName)
:Widget(),m_Time(1.0f),m_CurrentTime(0.0f),m_isPress(false),m_State(NORMAL)
{


	mElement = Ogre::OverlayManager::getSingleton().createOverlayElementFromTemplate("cz/TimeImageButton", "Panel", name);

	m_pBackgroundMaterial=Ogre::MaterialManager::getSingleton().getByName(name);
	if(m_pBackgroundMaterial.isNull())
	{
		m_pBackgroundMaterial=mElement->getMaterial()->clone(name);
	}

	mElement->setMaterialName(m_pBackgroundMaterial->getName());
	m_pBackgroundMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(imageName);


	Ogre::PanelOverlayElement* pBackground=static_cast<Ogre::PanelOverlayElement*>(mElement);
	m_pDeleteElement=pBackground->getChild(getName()+"/DeleteImage");
	m_pDeleteElement->hide();

	//Ogre::String deleteMaterial=name+"deleate";
	//m_pDeleteMaterial=Ogre::MaterialManager::getSingleton().getByName(deleteMaterial);
	//if(m_pDeleteMaterial.isNull())
	//{
	//	m_pDeleteMaterial=mElement->getMaterial()->clone(deleteMaterial);
	//}

	//m_pDeleteMaterial


}


//-------------------------------------------------------------------------------------------
TimeImageButton::~TimeImageButton()
{

	Ogre::MaterialManager::getSingleton().remove(m_pBackgroundMaterial->getHandle());


}

//-------------------------------------------------------------------------------------------
void TimeImageButton::update(float time)
{
	if(m_State==NORMAL&&m_isPress==true)
	{
        m_CurrentTime+=time;

		if(m_CurrentTime>=m_Time)
		{
			m_State=Press;
			//m_CurrentTime=0.0f;
		}
	}

	
	updateState();


}

//-------------------------------------------------------------------------------------------
void TimeImageButton::_cursorPressed(const Ogre::Vector2& cursorPos)
{

	if (isCursorOver(mElement, cursorPos, 4))
	{
	  m_isPress=true;
	}
	

}

//-------------------------------------------------------------------------------------------
void TimeImageButton::_cursorReleased(const Ogre::Vector2& cursorPos) 
{

	

	if (isCursorOver(mElement, cursorPos, 4)&&mListener!=NULL)
	{
		if(getState()==NORMAL)
		{
            mListener->buttonHit(this);
		}else if(m_CurrentTime<m_Time)///如果长按的时间很小表示改变状态第一次离开
		{
			mListener->buttonHit(this);
		
		}
		
	}
	m_CurrentTime=0.0f;
	m_isPress=false;

}
//-------------------------------------------------------------------------------------------
void TimeImageButton::_focusLost()
{
  m_isPress=false;
}

//---------------------------------------------------------------------------------------------
void TimeImageButton::updateState()
{
	if(m_State==NORMAL)
	{
		m_pDeleteElement->hide();
	}else if(m_State==Press)
	{
		m_pDeleteElement->show();
	}

}

//--------------------------------------------------------------------------------------------
///重置状态
void TimeImageButton::reset()
{
	m_isPress=false;
	m_CurrentTime=0;
	m_State=NORMAL;
	updateState();

}