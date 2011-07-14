
#include "pch.h"
#include "UISelectUser.h"
#include  "Widget.h"







UISelectUser::UISelectUser()
:UIBase("UISelectUser","")
{


}


//----------------------------------------
UISelectUser::~UISelectUser()
{


}

//-----------------------------------------------
void  UISelectUser::init()
{

	m_pParentOverlay =Ogre::OverlayManager::getSingleton().create("UISelectUser");
	m_pParentOverlay->show();


	StaticImage* pImage=new StaticImage("SelectUserBackGround","sdk_button_up.png");
	registerWidget(pImage);
	Ogre::OverlayElement* pElment=pImage->getOverlayElement();
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>(pElment));
	pElment->setMetricsMode(Ogre::GMM_RELATIVE);
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	pElment->setVerticalAlignment(Ogre::GVA_TOP);
	pElment->setWidth(1.0f);
	pElment->setHeight(1.0f);
    
    
    
    
    ///创建左边按钮用来跳到捕获脸的界面。
    ImageButton* pButton=new ImageButton("UISelectUser_GoCapture","sdk_button_up.png","sdk_button_down.png");
    registerWidget(pButton);
    pButton->_assignListener(this);
    pElment=pButton->getOverlayElement();
	m_pParentOverlay->add2D( static_cast<Ogre::OverlayContainer*>(pElment));
	pElment->setHorizontalAlignment(Ogre::GHA_LEFT);
	//pElment->setWidth(1.0f);
	//pElment->setHeight(1.0f);

    
    
    

    
    
    ///创建五个按钮用来选择已拍照的人物。
    
    //ImageButton* pButton =new ImageButton("SelectUser_1",















	return ;
}



//-------------------------------------------------------
void  UISelectUser::setUserList(Ogre::StringVectorPtr pUserList)
{

	///如果传无效指针忽视
	if(pUserList.isNull())
		return ;

	///删除旧的
	destroyAllUserList();

	m_UserList=pUserList;

	///循环创建有用户按钮,最多只创建5个
	int userSize=m_UserList->size();
	if(userSize>5)
	{
		userSize=5;
	}

	for(int i=0;i<userSize;++i)
	{
		Ogre::String buttonName="UserFace_"+Ogre::StringConverter::toString(i);
		Ogre::String imageName=m_UserList->at(i);
		ImageButton* pButton=new ImageButton(buttonName, imageName,imageName);
		registerWidget(pButton);
		m_UserButtonCollect.push_back(pButton);

		Ogre::OverlayElement* pElement=pButton->getOverlayElement();
		pElement->setHorizontalAlignment(Ogre::GHA_LEFT);

		pElement->setLeft(200+200*i);

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