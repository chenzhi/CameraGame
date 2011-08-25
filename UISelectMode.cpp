#include "pch.h"
#include "UISelectMode.h"
#include "Widget.h"
#include "Config.h"
#include "Application.h"
#include "Config.h"


UISelectMode::UISelectMode()
:UILayout("moshixuanze")
{



}



UISelectMode::~UISelectMode()
{


}



/**初始化*/
/*
void UISelectMode::init()
{
	UIBase::init();

	///模式选择背景图
	StaticImage* pImage=new StaticImage("SelectModeBackGround","jieshu_background.png");
	registerWidget(pImage);
	pImage->setMetricsMode(Ogre::GMM_RELATIVE);
	pImage->setHorizontalAlignment(Ogre::GHA_LEFT);
	pImage->setVerticalAlignment(Ogre::GVA_TOP);
	pImage->setWidth(1.0f);
	pImage->setHeight(1.0f);


	///静态图片stage
    pImage=new StaticImage("SelectMode_StageImage","moshi_stage.png");
	registerWidget(pImage);
	pImage->setVerticalAlignment(Ogre::GVA_TOP);
	pImage->setTop(100);
	int width=300;
	int height=65;
	pImage->setWidth(width);
	pImage->setHeight(height);
	pImage->setLeft(width*-0.5f);


	


	///模式1按钮
	ImageButton* pPlayButton=new ImageButton("SelectMode_1","moshi_leftright.png","moshi_leftright.png");
	registerWidget(pPlayButton);
	pPlayButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	width=pPlayButton->getWidth();
	height=pPlayButton->getHeight();
	pPlayButton->setLeft(-5);
	pPlayButton->setTop(height*(-0.9f));
	pPlayButton->setWidth(350);
	pPlayButton->setHeight(310);


	///模式2按钮
	pPlayButton=new ImageButton("SelectMode_2","moshi_updown.png","moshi_updown.png");
	registerWidget(pPlayButton);
	//pPlayButton->setHorizontalAlignment(Ogre::GHA_CENTER);
	width=pPlayButton->getWidth();
	height=pPlayButton->getHeight();
	pPlayButton->setLeft(-width-45.0f);
	pPlayButton->setTop(height*(-0.9f));
	pPlayButton->setWidth(350);
	pPlayButton->setHeight(310);



	///模式3按钮
	pPlayButton=new ImageButton("SelectMode_3","moshi_smile.png","moshi_smile.png");
	registerWidget(pPlayButton);
	pPlayButton->setHorizontalAlignment(Ogre::GHA_RIGHT);
	width=pPlayButton->getWidth();
	height=pPlayButton->getHeight();
	pPlayButton->setLeft(-width-210.0f);
	pPlayButton->setTop(height*(-0.9f));
	pPlayButton->setWidth(350);
	pPlayButton->setHeight(310);






	///返回按钮
	Widget* pReturnButton=new ImageButton("SelectMode_return","moshi_fanhui_release.png","moshi_fanhui_press.png");
	pReturnButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	pReturnButton->setWidth(80);
	pReturnButton->setHeight(80);
	pReturnButton->setLeft(10);
	pReturnButton->setVerticalAlignment(Ogre::GVA_BOTTOM);
	pReturnButton->setTop(-100);
	registerWidget(pReturnButton);






	return ;
}

//*/


void UISelectMode::buttonHit(Widget* button)
{
	const  Ogre::String&  name=button->getName();

	///如果是返回按钮
	if(name=="moshixuanze/moshixuanzefanhui")
	{
		Application::getSingleton().getCurrentActive()->setNextStateType(ST_GAMEPLAY);
		return ;

	}


	if(name=="moshixuanze/moshixuanzelanlvyuan")
	{
     g_userInformation.setWarMode(0);

	}else if(name=="moshixuanze/moshixuanzelanyuan")
	{
        g_userInformation.setWarMode(1);
	}else if(name=="moshixuanze/moshixuanzehuangyuan")
	{

    g_userInformation.setWarMode(2);
	}



	Application::getSingleton().getCurrentActive()->setNextStateType(ST_CAPTUREFACE);

	return ;


}