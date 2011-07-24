#include "pch.h"
#include "UIWarTwo.h"
#include "Widget.h"



//-----------------------------------------------------------------
UIWarModeTwo::UIWarModeTwo()
:UIBase("UIWarModeTwo",""),m_pRotateImage(NULL)
{

}


//-----------------------------------------------------------------
UIWarModeTwo::~UIWarModeTwo()
{


}


//-----------------------------------------------------------------
void UIWarModeTwo::init()
{
	UIBase::init();


	m_pRotateImage=new RotateImage("Enemey Dir","youxi_fangxiang.png");
	registerWidget(m_pRotateImage);



	



}


///设置敌人所有的方向
void UIWarModeTwo::setEmemeyDir(float Radian)
{

	m_pRotateImage->setOrientation(Radian);



	float y=Ogre::Math::Sin(Radian);
	float x=Ogre::Math::Cos(Radian);


	m_pRotateImage->setLeft(x*200);
	m_pRotateImage->setTop(-y*200);



}