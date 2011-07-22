
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

	Ogre::TextureUnitState* pTextureState=m_pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);

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
    
    rotateButton(time);


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
   updateState();
}


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

//---------------------------------------------------------------------------------------------
void TimeImageButton::rotateButton(float time)
{
    if(m_State==NORMAL)
    {
        
    }else
    {
        
        
    }
    
}

//--------------------------------------------------------------------------------------------
void TimeImageButton::reset()
{
	m_isPress=false;
	m_CurrentTime=0;
	m_State=NORMAL;
	updateState();

}


/***********************************************
会显示3d图形的按钮。可以把一scenenode挂到这个按钮上
**************************************************/
//-----------------------------------------------------------------------------------------
Image3DButton::Image3DButton(const Ogre::String& name,Ogre::SceneNode* pNode)
:m_pOveraly(NULL),m_pScenNode(pNode)
{

	m_pOveraly=Ogre::OverlayManager::getSingleton().create(name);
	mElement = Ogre::OverlayManager::getSingleton().createOverlayElementFromTemplate("cz/ImageButton", "Panel", name);
	m_pOveraly->add2D( static_cast<Ogre::OverlayContainer*>(mElement));


}

//-----------------------------------------------------------------------------------------
Image3DButton::~Image3DButton()
{

	Ogre::OverlayManager::getSingleton().destroy(m_pOveraly);
}


//-----------------------------------------------------------------------------------------
void Image3DButton::_cursorPressed(const Ogre::Vector2& cursorPos)
{


}

//-----------------------------------------------------------------------------------------
void Image3DButton::_cursorReleased(const Ogre::Vector2& cursorPos) 
{

	if (isCursorOver(mElement, cursorPos, 4))
	{
		if(mListener!=NULL)
		{
			mListener->buttonHit(this);
		}

	}
	return ;

}


//-----------------------------------------------------------------------------------------
const Ogre::String& Image3DButton::getName()
{


	return m_pOveraly->getName();
}


//-----------------------------------------------------------------------------------------
void   Image3DButton::setSceneNode(Ogre::SceneNode* pNode)
{
	if(m_pScenNode!=NULL)
	{
		Ogre::SceneNode* pParentNode=m_pScenNode->getParentSceneNode();
		if(pParentNode!=NULL)
		{
			pParentNode->removeChild(m_pScenNode);
		}
	}

	m_pScenNode=pNode;
	if(m_pOveraly!=NULL)
	{
		m_pOveraly->add3D(m_pScenNode);
	}



}



/*************************************************
滑动按钮，
****************************************************/


//-------------------------------------------------------
SliderGallery::SliderGallery(const Ogre::String& name,SliderGalleryDataSource* pDataSource)
:Widget(),m_IsPress(false),m_RollDir(0),m_RollTime(0.0f),m_pDataSource(pDataSource),m_DataIndex(0)
{

	mElement=Ogre::OverlayManager::getSingleton().createOverlayElementFromTemplate("cz/SliderGallery","Panel",name);

	Ogre::OverlayContainer* pContainer=static_cast<Ogre::OverlayContainer*>(mElement);

    m_pPrevisouButton=pContainer->getChild(getName()+"/cz/SliderGallery/PreviousButton");
    m_pNextButton=pContainer->getChild(getName()+"/cz/SliderGallery/NextButton");


	pContainer = static_cast<Ogre::OverlayContainer*>(pContainer->getChild(name+"/cz/SliderGallery/Backgroud"));

	Ogre::OverlayElement* pButton=pContainer->getChild(pContainer->getName()+"/cz/SliderGallery/1");
	SrollButton* pSrollButton= new SrollButton(pButton);
	m_ButtonCollect.push_back(pSrollButton);


	pButton=pContainer->getChild(pContainer->getName()+"/cz/SliderGallery/2");
	pSrollButton= new SrollButton(pButton);
	m_ButtonCollect.push_back(pSrollButton);


	pButton=pContainer->getChild(pContainer->getName()+"/cz/SliderGallery/3");
	pSrollButton= new SrollButton(pButton);
	m_ButtonCollect.push_back(pSrollButton);



	///初始化资源
	resetButtonInformation();


}


//-------------------------------------------------------
SliderGallery::~SliderGallery()
{
	destroySrollButton();
	SafeDelete(m_pDataSource);


}



//-------------------------------------------------------
void SliderGallery::setDataSource(SliderGalleryDataSource* pSource)
{
	if(pSource==NULL)
		return ;
	SafeDelete(m_pDataSource);
	m_pDataSource=pSource;


}


//-------------------------------------------------------
void SliderGallery::_cursorPressed(const Ogre::Vector2& cursorPos)
{
	

	m_IsPress=true;	

	//SaveButtonPos();

	if(isCursorOver(m_pPrevisouButton,cursorPos)&&m_RollDir==0)
	{
		
	}else if(isCursorOver(m_pNextButton,cursorPos)&&m_RollDir==0)
	{
		
	}


}


//-------------------------------------------------------
void SliderGallery::_cursorReleased(const Ogre::Vector2& cursorPos)
{
	
	m_IsPress=false;

	if(m_RollDir==0)
	{
		if(isCursorOver(m_pPrevisouButton,cursorPos))
		{
			
			previsouButton();
		     return ;

		}else if(isCursorOver(m_pNextButton,cursorPos))
		{
			nextButton();
			return ;
		}

	}


	///如果没有点击前后按钮。判断是否点击到了主要的内容按钮
	SrollButtonCollect::iterator it=m_ButtonCollect.begin();
	SrollButtonCollect::iterator itend=m_ButtonCollect.end();
	for(;it!=itend;++it)
	{
		if(mListener!=NULL&&(*it)->isCursorOver(cursorPos))
		{
            mListener->sliderGalleryhit(*it);
			return ;
		}
	}



	

	

}


//----------------------------------------------------------
void SliderGallery::previsouButton()
{


	///如果最后一个按钮已经是最后一个元素。就不再向右移动
	if(m_DataIndex>=m_pDataSource->getElementCount()-m_ButtonCollect.size())
	{
		return ;
	}

	m_RollDir=1;
	++m_DataIndex;

	size_t size=m_ButtonCollect.size();
	SrollButton* pFirstButton=m_ButtonCollect[0];
	SrollButton* pLastButton=m_ButtonCollect[size-1];

   pFirstButton->m_OriginalPos=pFirstButton->m_pElement->getLeft();
   pFirstButton->m_targetPos  =pLastButton->m_pElement->getLeft();
   pFirstButton->m_Visible=false;



   for(size_t i=size-1;i>0;--i)
   {
	   pFirstButton=m_ButtonCollect[i];
	   pLastButton=m_ButtonCollect[i-1];

	   pFirstButton->m_OriginalPos=pFirstButton->m_pElement->getLeft();
	   pFirstButton->m_targetPos  =pLastButton->m_pElement->getLeft();
	   pFirstButton->m_Visible=true;


   }


   ///把元素的位置重排 
   pFirstButton=m_ButtonCollect[0];
   m_ButtonCollect.erase(m_ButtonCollect.begin());
   m_ButtonCollect.push_back(pFirstButton);


   return ;

}


//----------------------------------------------------------
void SliderGallery::nextButton()
{

	///如果数据源指向第一个元素。就不能再向前移动
	if(m_DataIndex<=0)
	{
		return ;
	}

	m_RollDir=-1;
	--m_DataIndex;

	size_t size=m_ButtonCollect.size();
	SrollButton* pFirstButton=m_ButtonCollect[size-1];
	SrollButton* pLastButton=m_ButtonCollect[0];

	pFirstButton->m_OriginalPos=pFirstButton->m_pElement->getLeft();
	pFirstButton->m_targetPos  =pLastButton->m_pElement->getLeft();
	pFirstButton->m_Visible=false;



	for(size_t i=0;i<size-1;++i)
	{
		pFirstButton=m_ButtonCollect[i];
		pLastButton=m_ButtonCollect[i+1];

		pFirstButton->m_OriginalPos=pFirstButton->m_pElement->getLeft();
		pFirstButton->m_targetPos  =pLastButton->m_pElement->getLeft();
		pFirstButton->m_Visible=true;


	}


	///把元素的位置重排 
	pLastButton=m_ButtonCollect[size-1];
	m_ButtonCollect.pop_back();
	m_ButtonCollect.insert(m_ButtonCollect.begin(),pLastButton);



}


//----------------------------------------------------------
void  SliderGallery::_cursorMoved(const Ogre::Vector2& cursorPos)
{

}



//-------------------------------------------------------------
void SliderGallery::update(float time)
{
	Widget::update(time);
	

	if(m_RollDir==0)
		return ;

	m_RollTime+=time;
	float precent=m_RollTime/0.5f;
	SrollButtonCollect::iterator it=m_ButtonCollect.begin();
	SrollButtonCollect::iterator itend=m_ButtonCollect.end();
	for(;it!=itend;++it)
	{
		(*it)->sroll(precent);
	}

	if(precent>=1.0f)
	{
		endRoll();

	}

	return ;	

}

//-----------------------------------------------------------------
void SliderGallery::destroySrollButton()
{

	SrollButtonCollect::iterator it=m_ButtonCollect.begin();
	SrollButtonCollect::iterator itend=m_ButtonCollect.end();

	for(;it!=itend;++it)
	{
		delete (*it);
	}
	m_ButtonCollect.clear();

}

//-----------------------------------------------------------------
void SliderGallery::resetButtonInformation()
{

	if(m_pDataSource==NULL)
		return ;

	///重置最左边一个按钮指向第0个元素.
	m_DataIndex=0;

	unsigned int Elementsize=m_pDataSource->getElementCount();
    unsigned int ButtonSize=m_ButtonCollect.size();


	Ogre::String textureName;
	Ogre::String userData;

	///取出数据
	for(unsigned int i=0 ;i<ButtonSize;++i)
	{
		Ogre::String textureName;
		Ogre::String userData;

		if(m_pDataSource->getElementTexture(i,textureName))
		{
			m_ButtonCollect[i]->setTextureName(textureName);
		}

		if(m_pDataSource->getElementUserData(i,userData))
		{
			m_ButtonCollect[i]->setUserData(userData);
		}
	}

	if(Elementsize<ButtonSize)
	{
		for(unsigned int i=Elementsize;i<ButtonSize;++i)
		{

			m_ButtonCollect[i]->setVisible(false);

		}
	}


	return ;

}


//--------------------------------------------------------------
void  SliderGallery::endRoll()
{

	m_RollDir=0;
	m_RollTime=0.0f;

	if(m_pDataSource==NULL)
		return ;


	///重新计算按钮显示
	
	Ogre::String textureName;
	Ogre::String userData;
	size_t buttonSize=m_ButtonCollect.size();
	for(size_t i=0;i<buttonSize;++i)
	{
		if(m_pDataSource->getElementTexture(m_DataIndex+i,textureName))
		{
			m_ButtonCollect[i]->setTextureName(textureName);
		}

		if(m_pDataSource->getElementUserData(m_DataIndex+i,userData))
		{
			m_ButtonCollect[i]->setUserData(userData);
		}

	}

	return ;

}


/*************************************************
可旋转的静态图片
****************************************************/
RotateImage::RotateImage(const Ogre::String& name, const Ogre::String& imageName)
:StaticImage(name,imageName)
{
	

}


//-------------------------------------------------------------------------
RotateImage::~RotateImage()
{

	

}

//-------------------------------------------------------------------------
void RotateImage::setOrientation(float radian)
{
	if(m_pMaterial.isNull())
		return ;
	Ogre::TextureUnitState* pTextureState=m_pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);

	pTextureState->setTextureRotate(Ogre::Radian(radian));

}
//
//void RotateImage::update(float time)
//{
//
//	static float ang=0.0f;
//	ang+=time;
//
//	while (ang>Ogre::Math::PI*2)
//	{
//		ang-=Ogre::Math::PI*2;
//	}
//
//	Ogre::TextureUnitState* pTextureState=m_pMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
//	if(pTextureState!=NULL)
//	{
//		pTextureState->setTextureRotate(Ogre::Radian(ang));
//	}
//
//
//
//
//}
