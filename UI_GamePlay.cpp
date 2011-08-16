


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
   pImage->setMetricsMode(Ogre::GMM_RELATIVE);
   pImage->setHorizontalAlignment(Ogre::GHA_LEFT);
   pImage->setVerticalAlignment(Ogre::GVA_TOP);
   pImage->setLeft(0.0f);
   pImage->setWidth(1.0f);
   pImage->setTop(0.0f);
   pImage->setHeight(1.0f);


   ImageButton* pPlayButton=new ImageButton("GamePlayer_PlayerButton","play_play_release.png","play_play_press.png");
   registerWidget(pPlayButton);
   float width=300;
   //float width=400;
   float height=128;
   //float height=200;
   pPlayButton->setHeight(height);
   pPlayButton->setWidth(width);
   pPlayButton->setLeft(width*(-0.5f));
   pPlayButton->setTop(160.0f);
  // pPlayButton->setTop(height*(-0.5f));



   //faceBool°´Å¥
   ImageButton* pPlayFaceBook=new ImageButton("GamePlayer_FaceBookButton","play_facebook_release.png","play_facebook_press.png");
   registerWidget(pPlayFaceBook);
   pPlayFaceBook->setHorizontalAlignment(Ogre::GHA_RIGHT);
   pPlayFaceBook->setVerticalAlignment(Ogre::GVA_BOTTOM);
   pPlayFaceBook->setWidth(80);
   pPlayFaceBook->setHeight(80);
   pPlayFaceBook->setLeft(-130);
   pPlayFaceBook->setTop(-228);



   //twit

   ImageButton* pPlayTwitterBook=new ImageButton("GamePlayer_twitterButton","play_twitter_release.png","play_twitter_press.png");
   registerWidget(pPlayTwitterBook);
   pPlayTwitterBook->setHorizontalAlignment(Ogre::GHA_RIGHT);
   pPlayTwitterBook->setVerticalAlignment(Ogre::GVA_BOTTOM);

   pPlayTwitterBook->setWidth(80);
   pPlayTwitterBook->setHeight(80);
   pPlayTwitterBook->setLeft(-130);
   pPlayTwitterBook->setTop(-128);

  



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



