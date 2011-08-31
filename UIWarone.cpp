#include "pch.h"
#include "UIWarone.h"
#include "Widget.h"
#include "UIWarPause.h"
#include  "Application.h"
#include "Tool.h"
#include "WarManager.h"
#include "EnemyQueue.h"
#include "Tool.h"


//-----------------------------------------------------------------
UIWarone::UIWarone()
:UILayout("moshi1")/*,m_PauseButton(NULL),m_FirePoint(NULL)*/,m_HundredTime(NULL),
m_TenTime(NULL),m_DigitTime(NULL),m_pRotateImage(NULL),m_pEnemy(NULL)
{

	memset(m_ScoreImage,0,5);

}


//-----------------------------------------------------------------
UIWarone::~UIWarone()
{


}

//---------------------------------------------------------------------
void  UIWarone::update(float time)
{
	UILayout::update(time);
	updateEnemyDir();
}



//-----------------------------------------------------------------

void UIWarone::init()
{
	UILayout::init();
	m_TenTime=static_cast<StaticImage*>(getWidgetByName("moshi1/moshi1shijianshuzi5"));
	m_DigitTime=static_cast<StaticImage*>(getWidgetByName("moshi1/moshi1shijianshuzi9"));

	


	///指示哪里有敌人出现的旋转按钮
	m_pRotateImage=new RotateImage("WarModeone_Enemey_Dir","youxi_fangxiang.png");
	registerWidget(m_pRotateImage);


	m_ScoreImage[0]=static_cast<StaticImage*>(getWidgetByName("moshi1/moshi1xiaoshuzi0."));
	m_ScoreImage[1]=static_cast<StaticImage*>(getWidgetByName("moshi1/moshi1xiaoshuzi0"));
	m_ScoreImage[2]=static_cast<StaticImage*>(getWidgetByName("moshi1/moshi1xiaoshuzi8"));
	m_ScoreImage[3]=static_cast<StaticImage*>(getWidgetByName("moshi1/moshi1xiaoshuzi5"));
	m_ScoreImage[4]=static_cast<StaticImage*>(getWidgetByName("moshi1/moshi1xiaoshuzi9"));


	return ;

	///暂停按钮
	/*/
	m_PauseButton=new ImageButton("WarModeone_PauseButton","youxi_zhanting_release.png","youxi_zhanting_press.png");
	registerWidget(m_PauseButton);
	m_PauseButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_PauseButton->setVerticalAlignment(Ogre::GVA_TOP);
	m_PauseButton->setLeft(32);
	m_PauseButton->setTop(32);
	m_PauseButton->setWidth(80);
	m_PauseButton->setHeight(80);



	///中间准心
	///准心
	m_FirePoint=new StaticImage("WarModeone_FirePoint","youxi_zhunxin.png");
	registerWidget(m_FirePoint);
	m_FirePoint->setLeft(m_FirePoint->getWidth()*(-0.5f));
	m_FirePoint->setTop(m_FirePoint->getHeight()*(-0.5f));


    ///创建记时图标
	m_HundredTime=new StaticImage("WarModeone_Hundred","jieshu_shuzi_0.png");
	m_HundredTime->setVerticalAlignment(Ogre::GVA_TOP);
	m_HundredTime->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_HundredTime->setWidth(64);
	m_HundredTime->setHeight(64);
	m_HundredTime->setLeft(-64*3);
	registerWidget(m_HundredTime);
	//m_TenTime;

	m_TenTime=new StaticImage("WarModeone_Ten","jieshu_shuzi_0.png");
	m_TenTime->setVerticalAlignment(Ogre::GVA_TOP);
	m_TenTime->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_TenTime->setWidth(64);
	m_TenTime->setHeight(64);
	m_TenTime->setLeft(-64*2);
	registerWidget(m_TenTime);
	//m_DigitTime;
	m_DigitTime=new StaticImage("WarModeone_Digit","jieshu_shuzi_0.png");
	m_DigitTime->setVerticalAlignment(Ogre::GVA_TOP);
	m_DigitTime->setHorizontalAlignment(Ogre::GHA_RIGHT);
	m_DigitTime->setWidth(64);
	m_DigitTime->setHeight(64);
	m_DigitTime->setLeft(-64);
	registerWidget(m_DigitTime);


//*/


}
//*/

//-----------------------------------------------------------------
void UIWarone::setTime(int time)
{
	unsigned int second=0;
	unsigned int minute=0;
	unsigned int hource=0;

	second=Tools::getValueByBit(time,1);
	minute=Tools::getValueByBit(time,2);
	hource=Tools::getValueByBit(time,3);


	//Tools::parseTime(time*1000,hource,minute,second);

	Ogre::String textureName="set:jifengqiepian0_21 image:moshi1_";


	//m_HundredTime->setImage(textureName+Ogre::StringConverter::toString(hource)+".png");
	m_TenTime->setImage(textureName+Ogre::StringConverter::toString(minute),true);
	m_DigitTime->setImage(textureName+Ogre::StringConverter::toString(second),true);




	return;

}

//-----------------------------------------------------------------
void UIWarone::buttonHit(Widget* button)
{
	///如果点击暂停按钮
	if(button->getName()=="moshi1/moshi1zantingjian")
	{                                                                                          
		UIWarPause* pPauseUI= static_cast<UIWarPause*>(Application::getSingleton().getUIByName("zantingjiemian"));

		std::vector<UIBase*>showList;
		showList.push_back(this);
		pPauseUI->setEndShowUI(showList);
		pPauseUI->setVisible(true);
		setVisible(false);

	}

}


//-----------------------------------------------------
void UIWarone::updateEnemyDir()
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

		//m_pRotateImage->show();
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

	float dis=220;
	m_pRotateImage->setLeft(x*dis);
	m_pRotateImage->setTop(-y*dis);


}


//----------------------------------------------------------------
void  UIWarone::onKillEnemyQueue(EnemyQueue* pEnemyQueue)
{

	m_pEnemy=NULL;
	return ;
}

//----------------------------------------------------------------
void  UIWarone::onLostEnemyQueue(EnemyQueue* pEnemyQueue)
{
	///减少显示一个生合图标

	m_pEnemy=NULL;

	return ;
}

//----------------------------------------------------------------
void UIWarone::onCrateEnemyQueue(EnemyQueue* pEnemyQueue)
{
	m_pEnemy=pEnemyQueue;
}


//----------------------------------------------------------------
void UIWarone::setScore(unsigned int    score)
{
	Ogre::String textureName="set:jifengqiepian0_21 image:gongyongxiaoziti_";
	int temValue=Tools::getValueByBit(score,1);
	m_ScoreImage[0]->setImage(textureName+Ogre::StringConverter::toString(temValue),true);

	temValue=Tools::getValueByBit(score,2);
	m_ScoreImage[1]->setImage(textureName+Ogre::StringConverter::toString(temValue),true);

	temValue=Tools::getValueByBit(score,3);
	m_ScoreImage[2]->setImage(textureName+Ogre::StringConverter::toString(temValue),true);

	temValue=Tools::getValueByBit(score,4);
	m_ScoreImage[3]->setImage(textureName+Ogre::StringConverter::toString(temValue),true);

	temValue=Tools::getValueByBit(score,5);
	m_ScoreImage[4]->setImage(textureName+Ogre::StringConverter::toString(temValue),true);


	return ;

}

//---------------------------------------------------
void UIWarone::reset()
{

	Ogre::String textureName="set:jifengqiepian0_21 image:gongyongxiaoziti_0";
	for(int i=0;i<5;++i)
	{
     m_ScoreImage[i]->setImage(textureName,true);
	}
	



}