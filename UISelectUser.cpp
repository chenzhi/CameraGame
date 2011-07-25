#include "pch.h"
#include "UISelectUser.h"
#include  "Widget.h"
#include "Application.h"
#include "Config.h"
#include "Tool.h"





UISelectUser::UISelectUser()
:UIBase("UISelectUser",""),m_ToCaptureButton(NULL),m_NeedUpdate(false)
{


}


//----------------------------------------
UISelectUser::~UISelectUser()
{


}

//-----------------------------------------------
void  UISelectUser::init()
{

	UIBase::init();


	StaticImage* pImage=new StaticImage("SelectUserBackGround","tuku_background.png");
	registerWidget(pImage);
	Ogre::OverlayElement* pElment=pImage->getOverlayElement();
	pElment->setMetricsMode(Ogre::GMM_RELATIVE);
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	pElment->setVerticalAlignment(Ogre::GVA_TOP);
	pElment->setWidth(1.0f);
	pElment->setHeight(1.0f);




	///捕脸按钮
	m_ToCaptureButton=new ImageButton("UISelectUser_GoCapture","moshi_fanhui_press.png","moshi_fanhui_release.png");
	registerWidget(m_ToCaptureButton);
	m_ToCaptureButton->_assignListener(this);
	pElment=m_ToCaptureButton->getOverlayElement();
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_ToCaptureButton->setWidth(80);
	m_ToCaptureButton->setHeight(80);

	return ;
}



//-----------------------------------------------
void UISelectUser::update(float time)
{
	UIBase::update(time);

	if(m_NeedUpdate)
	{
		updateUserList();
	}

	return ;

}


//-------------------------------------------------------
void  UISelectUser::updateUserList()
{

	Ogre::StringVectorPtr pUserList=Tools::getUserFaceFileList();
	setUserList(pUserList);
	m_NeedUpdate=false;

}



//-------------------------------------------------------
void  UISelectUser::setUserList(Ogre::StringVectorPtr pUserList)
{

	if(pUserList.isNull())
		return ;

	///????觧?
	destroyAllUserList();

	m_UserList=pUserList;

	///最多只取5个用户
	int userSize=m_UserList->size();
	if(userSize>5)
	{
		userSize=5;
	}

	for(int i=0;i<userSize;++i)
	{
		//Ogre::String buttonName="UserFace_"+Ogre::StringConverter::toString(i);
		Ogre::String imageName=m_UserList->at(i);
		TimeImageButton* pButton=new TimeImageButton(imageName, imageName);
		registerWidget(pButton);
		m_UserButtonCollect.push_back(pButton);

		Ogre::OverlayElement* pElement=pButton->getOverlayElement();
		pElement->setHorizontalAlignment(Ogre::GHA_LEFT);
		pElement->setLeft(200+150*i);

	}




	return ;

}


//-------------------------------------------------------
void  UISelectUser::destroyAllUserList()
{

	ImageButtonCollect::iterator it=m_UserButtonCollect.begin();
	ImageButtonCollect::iterator itend=m_UserButtonCollect.end();

	for(;it!=itend;++it)
	{
		destroyWidget(*it);
	}

	m_UserButtonCollect.clear();

	return ;

}

//-------------------------------------------------------
void UISelectUser::onEndTouch(int x,int y)
{
	UIBase::onEndTouch(x,y);



	///重置所有的候选按钮状态
	bool needRest=true;

	ImageButtonCollect::iterator it=m_UserButtonCollect.begin();
	ImageButtonCollect::iterator itend=m_UserButtonCollect.end();
	Ogre::Vector2  area(x,y);

	for(;it!=itend;++it)
	{
		if((*it)->isCursorOver((*it)->getOverlayElement(),area))
		{

			needRest=false;
			break;;
		}
	}

	if(needRest)
	{
		resetUserFaceButton();
	}


}

//----------------------------------------------------------
void   UISelectUser::resetUserFaceButton()
{
	ImageButtonCollect::iterator it=m_UserButtonCollect.begin();
	ImageButtonCollect::iterator itend=m_UserButtonCollect.end();

	for(;it!=itend;++it)
	{
		(*it)->reset();
	}
	return ;
}

//-------------------------------------------------------
void UISelectUser::buttonHit(Widget* pbutton)
{
	if(pbutton==NULL)
		return ;


	//返回到捕脸的界面
	if(pbutton==m_ToCaptureButton)
	{
		setVisible(false);

		UIBase* pCaptureFace= Application::getSingleton().getUIByName("CaptureFaceUI");
		assert(pCaptureFace);
		pCaptureFace->setVisible(true);
		return ;

	}



	///如果选择了玩家	
	const Ogre::String& imageName=pbutton->getName();
	size_t size=m_UserList->size();
	for(size_t i=0;i<size;++i)
	{
		Ogre::String username=m_UserList->at(i);

		if(username==imageName)
		{

			TimeImageButton*  pTimeButton=static_cast<TimeImageButton*>(pbutton);

			///删除一个用户图片
			if(pTimeButton->getState()==TimeImageButton::Press)
			{

				username=Tools::getUserFacePath()+"/"+username;
				::remove(username.c_str());
				m_NeedUpdate=true;
				return ;
			}else if(pTimeButton->getState()==TimeImageButton::NORMAL)///进入选择头套界面
			{
				setVisible(false);
				g_userInformation.setUserImage(username);
				UIBase* pSelectFaceMode= Application::getSingleton().getUIByName("UISelectHead");
				pSelectFaceMode->setVisible(true);

			}


		}


	}



	return ;
}