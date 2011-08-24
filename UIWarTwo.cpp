#include "pch.h"
#include "UIWarTwo.h"
#include "Widget.h"
#include "WarMode.h"
#include "WarManager.h"
#include "Application.h"
#include "EnemyQueue.h"
#include "UIWarPause.h"


//-----------------------------------------------------------------
UIWarModeTwo::UIWarModeTwo()
:UIBase("UIWarModeTwo",""),m_pRotateImage(NULL),m_PauseButton(NULL),m_pEnemy(NULL)
{

}


//-----------------------------------------------------------------
UIWarModeTwo::~UIWarModeTwo()
{


}


//-----------------------------------------------------------------
void  UIWarModeTwo::update(float time)
 {

	 UIBase::update(time);

	 updateEnemyDir();
 }


//-----------------------------------------------------------------
void UIWarModeTwo::init()
{
	UIBase::init();


	///指示哪里有敌人出现的旋转按钮
	m_pRotateImage=new RotateImage("WarModeTwo_Enemey_Dir","youxi_fangxiang.png");
	//m_pRotateImage->setWidth(40);
	registerWidget(m_pRotateImage);


	///暂停按钮
	m_PauseButton=new ImageButton("WarModeTwo_PauseButton","youxi_zhanting_release.png","youxi_zhanting_press.png");
	registerWidget(m_PauseButton);
	m_PauseButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_PauseButton->setVerticalAlignment(Ogre::GVA_TOP);
	m_PauseButton->setLeft(32);
	m_PauseButton->setTop(32);
	m_PauseButton->setWidth(80);
	m_PauseButton->setHeight(80);

	
	///开枪按钮
    m_pFireButton =new ImageButton("WarModeTwo_FirButton","youxi_gongji_release.png","youxi_gongji_press.png");
	registerWidget(m_pFireButton);
	m_pFireButton->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_pFireButton->setVerticalAlignment(Ogre::GVA_BOTTOM);
	m_pFireButton->setLeft(-m_pFireButton->getWidth());
	m_pFireButton->setTop(-m_pFireButton->getHeight());


	///准心
	m_FirePoint=new StaticImage("WarModeTwo_FirePoint","youxi_zhunxin.png");
	registerWidget(m_FirePoint);
	m_FirePoint->setLeft(m_FirePoint->getWidth()*(-0.5f));
	m_FirePoint->setTop(m_FirePoint->getHeight()*(-0.5f));


	///初始化三个生命显示
	int startleft=-64*3;
	for(int i=0;i<3;++i)
	{
		StaticImage* pImage=new StaticImage("WarModeTwo_Lift_"+Ogre::StringConverter::toString(i),"youxi_shengmingzhi.png");
		registerWidget(pImage);
		pImage->setHorizontalAlignment(Ogre::GHA_RIGHT);
		pImage->setVerticalAlignment(Ogre::GVA_TOP);

		pImage->setWidth(50);
		pImage->setHeight(40);
		pImage->setLeft(startleft+(i)*64);
		pImage->setTop(40);
		m_LifeCollect.push_back(pImage);

	}
	


	
	m_PauseButton=static_cast<ImageButton*>(getWidgetByName("WarModeTwo_PauseButton"));


}



//-----------------------------------------------------
void UIWarModeTwo::updateEnemyDir()
{

	///如果比赛结束就不更新
	if(WarManager::getSingleton().isGameEnd())
	{
	    m_pRotateImage->hide();
		return ;
	}


	if(m_pEnemy==NULL)
	{
		m_pRotateImage->hide();
		return ;
	}

	///如果这个点在屏幕上出现了就隐藏箭头
	Ogre::Camera* pCamera=Application::getSingleton().getMainCamera();

	const Ogre::Matrix4& viewMat=pCamera->getViewMatrix();
	Ogre::Vector3 pos=m_pEnemy->getSceneNode()->getPosition();
	pos=viewMat*pos;

	Ogre::AxisAlignedBox box=m_pEnemy->getWordBox();

	if(pCamera->isVisible(box))
	{
		m_pRotateImage->hide();
		return ;
	}else
	{
		m_pRotateImage->show();
	}



	float  ang= (Ogre::Math::ATan(pos.y/pos.x)).valueDegrees();

	///第三像限
	if(pos.x<0&&pos.y>0)
	{

		ang=90.0f+(90+ang);

	}else if(pos.x<0&&pos.y<0)//第四像限
	{

		ang=180.0f+ang;
	}
	Ogre::Radian Radian=Ogre::Degree(ang);

	m_pRotateImage->setOrientation(Radian.valueRadians());
	float y=Ogre::Math::Sin(Radian);
	float x=Ogre::Math::Cos(Radian);
	m_pRotateImage->setLeft(x*200);
	m_pRotateImage->setTop(-y*200);

	
}

//----------------------------------------------------------------
void  UIWarModeTwo::buttonHit(Widget* button)
{
	
	if(button==m_PauseButton)///如果是暂停
	{

		UIWarPause* pPauseUI= static_cast<UIWarPause*>(Application::getSingleton().getUIByName("zantingjiemian"));
		
		std::vector<UIBase*>showList;
		showList.push_back(this);
		pPauseUI->setEndShowUI(showList);

		pPauseUI->setVisible(true);
		setVisible(false);


	}
}


//-------------------------------------------------------------------
 void UIWarModeTwo::onBeginTouch(int x,int y)
 {

	 ///如果点击到了暂停按钮就忽略
	 if(m_PauseButton->isCursorOver(m_PauseButton->getOverlayElement(),Ogre::Vector2(x,y),4))
	 {
		 return ;
	 }
	 WarManager::getSingleton().fire();
	 return ;
 }



//----------------------------------------------------------------
void  UIWarModeTwo::onKillEnemyQueue(EnemyQueue* pEnemyQueue)
{

	m_pEnemy=NULL;
	return ;
}

//----------------------------------------------------------------
void  UIWarModeTwo::onLostEnemyQueue(EnemyQueue* pEnemyQueue)
{
	///减少显示一个生合图标

	WidgetCollect::iterator it=	m_LifeCollect.begin();
	WidgetCollect::iterator itend=	m_LifeCollect.end();

	for(;it!=itend;++it)
	{
		if(	(*it)->isVisible())
		{
			(*it)->hide();
			return ;
		}
	}

	m_pEnemy=NULL;



	return ;
}

//----------------------------------------------------------------
void UIWarModeTwo::onCrateEnemyQueue(EnemyQueue* pEnemyQueue)
{
	m_pEnemy=pEnemyQueue;
}


///-------------------------------------------------------------
void UIWarModeTwo::reset()
{

	WidgetCollect::iterator it=	m_LifeCollect.begin();
	WidgetCollect::iterator itend=	m_LifeCollect.end();

	for(;it!=itend;++it)
	{
		(*it)->show();
	}

	m_pEnemy=NULL;

}