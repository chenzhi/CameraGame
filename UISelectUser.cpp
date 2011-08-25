#include "pch.h"
#include "UISelectUser.h"
#include  "Widget.h"
#include "Application.h"
#include "Config.h"
#include "Tool.h"





UISelectUser::UISelectUser()
:UILayout("tukumoshi"),m_ToCaptureButton(NULL),m_pReturnButton(NULL),m_NeedUpdate(false)
{


}


//----------------------------------------
UISelectUser::~UISelectUser()
{


}

//-----------------------------------------------
void  UISelectUser::init()
{

	UILayout::init();

	Widget* pWidget=getWidgetByName("toukujiemian/toukuhonglian");
	m_FaceMaskCollect.push_back(pWidget);


	pWidget=getWidgetByName("toukujiemian/ltoukuanlian");
	m_FaceMaskCollect.push_back(pWidget);
	

	pWidget=getWidgetByName("toukujiemian/toukujulian");
	m_FaceMaskCollect.push_back(pWidget);


	pWidget=getWidgetByName("toukujiemian/toukuyinglan");
	m_FaceMaskCollect.push_back(pWidget);


	pWidget=getWidgetByName("toukujiemian/toukulvlian");
	m_FaceMaskCollect.push_back(pWidget);


	return ;

	/*
	///背景
	StaticImage* pImage=new StaticImage("SelectUserBackGround","jieshu_background.png");
	registerWidget(pImage);
	Ogre::OverlayElement* pElment=pImage->getOverlayElement();
	pElment->setMetricsMode(Ogre::GMM_RELATIVE);
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	pElment->setVerticalAlignment(Ogre::GVA_TOP);
	pElment->setWidth(1.0f);
	pElment->setHeight(1.0f);




	///跳到拍照界面
	m_ToCaptureButton=new ImageButton("UISelectUser_GoCapture","tuku_zuoanniu_release.png","tuku_zuoanniu_press.png");
	registerWidget(m_ToCaptureButton);
	m_ToCaptureButton->_assignListener(this);
	pElment=m_ToCaptureButton->getOverlayElement();
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_ToCaptureButton->setWidth(65);//zxt_modify
	m_ToCaptureButton->setHeight(65);
	m_ToCaptureButton->setLeft(30);
	m_ToCaptureButton->setTop(-20);

	///返回按钮

	///返回上一层按钮
	m_pReturnButton=new ImageButton("UISelctReturnButton,","moshi_fanhui_release.png","moshi_fanhui_press.png");
	registerWidget(m_pReturnButton);
	m_pReturnButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_pReturnButton->setLeft(10);
	m_pReturnButton->setVerticalAlignment(Ogre::GVA_BOTTOM);
	m_pReturnButton->setTop(-100);
	m_pReturnButton->setWidth(80);
	m_pReturnButton->setHeight(80);
    




	///删除提示框
   StaticImage* pDeleteImage=new StaticImage("UISelectDeleteImage","tuku_delete_0.png");
   registerWidget(pDeleteImage);
   pDeleteImage->setVerticalAlignment(Ogre::GVA_BOTTOM);
   pDeleteImage->setWidth(256);
   pDeleteImage->setTop(-pDeleteImage->getHeight()-20);
   pDeleteImage->setLeft(-pDeleteImage->getWidth()*0.5f);
    //*/
	
}



//-----------------------------------------------
void UISelectUser::update(float time)
{
	UILayout::update(time);

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

	///先销毁所有的
	destroyAllUserList();

	m_UserList=pUserList;

	///最多只显示5个
    int userSize=m_UserList->size();
	if(userSize>5)
	{
		userSize=5;
	}

	size_t maskSize=m_FaceMaskCollect.size();
	for(size_t i=0;i<maskSize;++i)
	{
	   this->unregisterWidget(m_FaceMaskCollect[i]);
	}

	

	for(int i=0;i<userSize;++i)
	{
		//Ogre::String buttonName="UserFace_"+Ogre::StringConverter::toString(i);


		Widget* pMaskFace=m_FaceMaskCollect[i];
		float left=pMaskFace->getLeft();
		float width=pMaskFace->getWidth();
		float top=pMaskFace->getTop();
		float height=pMaskFace->getHeight();



		Ogre::String imageName=m_UserList->at(i);
		TimeImageButton* pButton=new TimeImageButton(imageName, imageName);

		m_UserButtonCollect.push_back(pButton);

		pButton->setHorizontalAlignment(Ogre::GHA_LEFT);
		pButton->setVerticalAlignment(Ogre::GVA_TOP);
		pButton->setMetricsMode(Ogre::GMM_RELATIVE);

		pButton->setTop(top);
		pButton->setWidth(width);
		pButton->setLeft(left);
		pButton->setHeight(height);

		registerWidget(pButton);
		

	
	}



	
	for(size_t i=0;i<maskSize;++i)
	{
		registerWidget(m_FaceMaskCollect[i]);
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

	///如果一个用户按钮都没有点到。重置删除状态
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


//----------------------------------------------------------
void  UISelectUser::setVisible(bool b)
{
    UIBase::setVisible(b);
    if(b)
    {
        m_NeedUpdate=true;
    }
    
}


//-------------------------------------------------------
void UISelectUser::buttonHit(Widget* pbutton)
{
	if(pbutton==NULL)
		return ;


	const Ogre::String WidgetName=pbutton->getName();
	//如果是跳到拍照按钮
	if(WidgetName=="toukujiemian/toukudajiantouzuo")
	{
		setVisible(false);

		UIBase* pCaptureFace= Application::getSingleton().getUIByName("zhaoxiang");
		assert(pCaptureFace);
		pCaptureFace->setVisible(true);
		return ;

	}else if(pbutton==m_pReturnButton)//如果是返回按钮
	{
		Application::getSingleton().getCurrentActive()->setNextStateType(ST_SELECTMODE);
		return ;

	}



	///如果是选择已有的脸
	const Ogre::String& imageName=pbutton->getName();
	size_t size=m_UserList->size();
	for(size_t i=0;i<size;++i)
	{
		Ogre::String username=m_UserList->at(i);

		if(username==imageName)
		{

			TimeImageButton*  pTimeButton=static_cast<TimeImageButton*>(pbutton);

			///如果是删除用户脸
			if(pTimeButton->getState()==TimeImageButton::Press)
			{

				username=Tools::getUserFacePath()+"/"+username;
				::remove(username.c_str());
                
                //ogre 移除贴图
                Ogre::TextureManager::getSingleton().remove(username);
				m_NeedUpdate=true;
				return ;
			}else if(pTimeButton->getState()==TimeImageButton::NORMAL)///杩?????澶村????
			{
				setVisible(false);
				g_userInformation.setUserImage(username);
				UIBase* pSelectFaceMode= Application::getSingleton().getUIByName("toutaoxuanzejiemian");
				pSelectFaceMode->setVisible(true);

			}


		}


	}



	return ;
}
