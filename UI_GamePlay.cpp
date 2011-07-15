


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
   pElment->setMetricsMode(Ogre::GMM_RELATIVE);
   pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
   pElment->setVerticalAlignment(Ogre::GVA_TOP);

   pElment->setLeft(0.0f);
   pElment->setWidth(1.0f);
   pElment->setTop(0.0f);
   pElment->setHeight(1.0f);



   ImageButton* pPlayButton=new ImageButton("GamePlayer_PlayerButton","sdk_logo.png","sdk_button_down.png");
   registerWidget(pPlayButton);
   pElment=pPlayButton->getOverlayElement();
   pPlayButton->_assignListener(this);
   float width=pElment->getWidth();
   float height=pElment->getHeight();
   pElment->setLeft(width*(-0.5f));
   pElment->setTop(height*(-0.5f));



 

  




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