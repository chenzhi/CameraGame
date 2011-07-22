


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

   StaticImage* pImage=new StaticImage("GamePlayBackGround","play_background.png");
    registerWidget(pImage);
   Ogre::OverlayElement* pElment=pImage->getOverlayElement();
   pImage->setMetricsMode(Ogre::GMM_RELATIVE);
   pImage->setHorizontalAlignment(Ogre::GHA_LEFT);
   pImage->setVerticalAlignment(Ogre::GVA_TOP);

   pImage->setLeft(0.0f);
   pImage->setWidth(1.0f);
   pImage->setTop(0.0f);
   pImage->setHeight(1.0f);


   ImageButton* pPlayButton=new ImageButton("GamePlayer_PlayerButton","play_play_release.png","play_play_press.png");
   registerWidget(pPlayButton);
   pElment=pPlayButton->getOverlayElement();
   pPlayButton->_assignListener(this);
   float width=256;
   float height=200;
   pElment->setHeight(height);
   pElment->setWidth(width);
   pPlayButton->setLeft(width*(-0.5f));
   pPlayButton->setTop(50.0f);
  // pPlayButton->setTop(height*(-0.5f));


  



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



