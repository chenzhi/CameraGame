#include "pch.h"
#include "UIWarTwoBalance.h"
#include "Widget.h"
#include "WarMode.h"
#include "Application.h"

//-------------------------------------------------------------
UIWarTowModeBalance::UIWarTowModeBalance(WarMode* pMode)
:UIBase("UIWarTowModeBalance",""),m_pWarMode(pMode)
{

	assert(m_pWarMode);

}


//-------------------------------------------------------------
UIWarTowModeBalance::~UIWarTowModeBalance()
{



}


//-------------------------------------------------------------
void UIWarTowModeBalance::init()
{

	UIBase::init();

	///背景
	StaticImage* pBackGround=new StaticImage("Background","jieshu_background.png");
	registerWidget(pBackGround);
	pBackGround->setMetricsMode(Ogre::GMM_RELATIVE);
	pBackGround->setHorizontalAlignment(Ogre::GHA_LEFT);
	pBackGround->setVerticalAlignment(Ogre::GVA_TOP);
	pBackGround->setWidth(1.0f);
	pBackGround->setHeight(1.0f);



	//按钮背景
	StaticImage* pButtonBackground=new StaticImage("ButtonBackground","jieshu_wenzikuang_1.png");
	registerWidget(pButtonBackground);
	int width=250;
	pButtonBackground->setWidth(width);
	pButtonBackground->setHeight(width);
	pButtonBackground->setTop(-200);
	pButtonBackground->setLeft(width*-0.5f);


	///返回
	ImageButton* pButton=new ImageButton("returnButton","jieshu_return.png","jieshu_return.png");
	registerWidget(pButton);
	width*=0.8f;
	pButton->setWidth(width);
	pButton->setLeft(width*-0.5f);
	pButton->setTop(-130);
	pButton->setHeight(50);


     ///replay按钮
	pButton=new ImageButton("replayButton","jieshu_replay.png","jieshu_replay.png");
	registerWidget(pButton);
	pButton->setWidth(width);
	pButton->setLeft(width*-0.5f);
	pButton->setTop(-50);
	pButton->setHeight(50);



	///分数结算界面
	StaticImage* pStaticImage=new StaticImage("BalanceImage","jieshu_score.png");
	registerWidget(pStaticImage);
    pStaticImage->setLeft(-256);
	pStaticImage->setWidth(200);
	pStaticImage->setHeight(40);
	pStaticImage->setTop(50);





}


//-------------------------------------------------------------
void UIWarTowModeBalance::destroy()
{

}



//-------------------------------------------------------------
void UIWarTowModeBalance::buttonHit(Widget* pbutton)
{
	
     if(pbutton==NULL)
		 return ;

	 if(pbutton->getName()=="returnButton")//返回到模式选择
	 {

		 Application::getSingleton().getCurrentActive()->setNextStateType(ST_SELECTMODE);

	 }else if(pbutton->getName()=="replayButton")///如果是重玩。
	 {
         m_pWarMode->start();
	 }


	 setVisible(false);

}