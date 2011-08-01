#include "pch.h"
#include "UIWarModeThree.h"
#include "Widget.h"
#include "WarModeThree.h"
#include "UIWarPause.h"
#include "Application.h"

//------------------------------------------------------------
UIWarModeThree::UIWarModeThree(WarModeThree* pWarMode)
:UIBase("UIWarModeThree",""),m_pWarMode(pWarMode),
m_pPauseButton(NULL),m_pSnapshotButton(NULL),m_pItemSelectSlider(NULL),m_pPowerBackground(NULL)
{

}



//------------------------------------------------------------
UIWarModeThree::~UIWarModeThree()
{


}


//------------------------------------------------------------
void UIWarModeThree::init()
{
	UIBase::init();



	///暂停按钮

	///暂停按钮
	m_pPauseButton=new ImageButton("WarModeThree_PauseButton","youxi_zhanting_release.png","youxi_zhanting_press.png");	registerWidget(m_pPauseButton);
	m_pPauseButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_pPauseButton->setVerticalAlignment(Ogre::GVA_TOP);
	m_pPauseButton->setLeft(32);
	m_pPauseButton->setTop(32);
	m_pPauseButton->setWidth(64);
	m_pPauseButton->setHeight(64);



	///能量槽背景图
	m_pPowerBackground=new StaticImage("WarModeThree_PowerBackground","model3__xuetiao_1.png");
	registerWidget(m_pPowerBackground);
	int width=32;
	int height=300;
	m_pPowerBackground->setWidth(width);
	m_pPowerBackground->setHeight(height);
	m_pPowerBackground->setHorizontalAlignment(Ogre::GHA_RIGHT);
	int left=-width-50;
	m_pPowerBackground->setLeft(left);
	int top=-0.5*height-50;
	m_pPowerBackground->setTop(top);


	///能量槽数值图片
	m_pPowerImage=new StaticImage("WarModeThree_Power","model3__xuetiao.png");
	registerWidget(m_pPowerImage);
	width=32;
	height=300;
	m_pPowerImage->setWidth(width);
	m_pPowerImage->setHeight(height);
	m_pPowerImage->setHorizontalAlignment(Ogre::GHA_RIGHT);
	left=-width-50;
	m_pPowerImage->setLeft(left);
	top=-0.5*height-50;
	m_pPowerImage->setTop(top);





	///拍照键
	m_pSnapshotButton=new ImageButton("WarModeThree_SnapshotButton","paizhao_paizhao_release.png","paizhao_paizhao_press.png");
	registerWidget(m_pSnapshotButton);
	m_pSnapshotButton->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_pSnapshotButton->setLeft(left+16+(m_pSnapshotButton->getWidth()*-0.5f));
	m_pSnapshotButton->setTop(top+(m_pSnapshotButton->getHeight()*-0.5f));



	///道具选择滚动控件
	m_pItemSelectSlider =new SliderGallery("WarModeThree_ItemSlectSlider",new ItemDataSource(),"cz/Select/Arms");
	registerWidget(m_pItemSelectSlider);




}


//-----------------------------------------------------------------------------
void  UIWarModeThree::setPowerPercent(float percent)
{
	std::max(0.0f,percent);
	std::min(1.0f,percent);

	int height=m_pPowerBackground->getHeight();
    int top=m_pPowerBackground->getTop();

	float newHeight=height*percent;

	int newTop=(top+height)-(height)*percent;
	m_pPowerImage->setTop(newTop);
	m_pPowerImage->setHeight(newHeight-5);



}

//void UIWarModeThree::update(float time)
//{
//	UIBase::update(time);
//
//    static float countTime=0;
//	countTime+=time;
//
//	int temIn=(int)countTime%10;
//	setPowerPercent(temIn*0.1f);
//
//
//}

//--------------------------------------------------------------------------
void UIWarModeThree::sliderGalleryhit(SrollButton* pbutton )
{

	if(pbutton==NULL)
		return ;

}


//--------------------------------------------------------------------------
void UIWarModeThree::buttonHit(Widget* pbutton)
{
	if(pbutton==NULL)
		return ;

	///如果是返回按钮。
	if(pbutton==m_pPauseButton)
	{
		UIWarPause* pPauseUI= static_cast<UIWarPause*>(Application::getSingleton().getUIByName("UIWarPause"));
		if(pPauseUI!=NULL)
		{
			std::vector<UIBase*>showList;
			showList.push_back(this);
			pPauseUI->setEndShowUI(showList);
			pPauseUI->setVisible(true);
			this->setVisible(false);
		}

		return ;

	}


}
