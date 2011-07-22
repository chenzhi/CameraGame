


#include "pch.h"
#include "UI_GamePlay.h"
#include "Widget.h"
#include "Application.h"


//-----------------------------------------------------------
UIGamePlay::UIGamePlay()
:UIBase("UIGamePlay","")
{
	
}


//-----------------------------------------------------------
UIGamePlay::~UIGamePlay()
{


}



//-----------------------------------------------------------
void UIGamePlay::init()
{

   UIBase::init();

   StaticImage* pImage=new StaticImage("GamePlayBackGround","sdk_logo.png");
    registerWidget(pImage);
   Ogre::OverlayElement* pElment=pImage->getOverlayElement();
   pImage->setMetricsMode(Ogre::GMM_RELATIVE);
   pImage->setHorizontalAlignment(Ogre::GHA_LEFT);
   pImage->setVerticalAlignment(Ogre::GVA_TOP);

   pImage->setLeft(0.0f);
   pImage->setWidth(1.0f);
   pImage->setTop(0.0f);
   pImage->setHeight(1.0f);


   ImageButton* pPlayButton=new ImageButton("GamePlayer_PlayerButton","sdk_logo.png","sdk_button_down.png");
   registerWidget(pPlayButton);
   pElment=pPlayButton->getOverlayElement();
   pPlayButton->_assignListener(this);
   float width=pElment->getWidth();
   float height=pElment->getHeight();
   pPlayButton->setLeft(width*(-0.5f));
   pPlayButton->setTop(height*(-0.5f));


   m_pRotateImage=new RotateImage("rotsa","sdk_button_down.png");
   registerWidget(m_pRotateImage);
   static_cast<RotateImage*>(m_pRotateImage)->setOrientation(1.70f);



}


//-----------------------------------------------------------
void UIGamePlay::buttonHit(Widget* button)
{

	if(button->getName()=="GamePlayer_PlayerButton")
	{

		Application::getSingleton().getCurrentActive()->setNextStateType(ST_SELECTMODE);
	}
	return ;

}



void  UIGamePlay::update(float time)
{
	if(m_pRotateImage!=NULL)
	{
		m_pRotateImage->update(time);
	}

}