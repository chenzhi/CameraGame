

#include "pch.h"
#include "UISelectHead.h"
#include "Widget.h"
#include "Application.h"
#include "Tool.h"
#include "Config.h"



FaceModeDataSource::FaceModeDataSource()
{

	m_ElementCollect.push_back(std::make_pair("InterfaceModel_duck.png","duck.mesh"));
	m_ElementCollect.push_back(std::make_pair("xuanmoxing_xuanzekuang_hema.png","hema.mesh"));
    m_ElementCollect.push_back(std::make_pair("xuanmoxing_xuanzekuang_laoshu.png","mouse.mesh"));
	m_ElementCollect.push_back(std::make_pair("InterfaceModel_xiaoji.png","xiaoji.mesh"));
	m_ElementCollect.push_back(std::make_pair("InterfaceModel_xiaolu.png","deer.mesh"));/*InterfaceModel_xiaoji*/
	m_ElementCollect.push_back(std::make_pair("InterfaceModel_xiaolu.png","head_tu.mesh"));
}

 
FaceModeDataSource::~FaceModeDataSource()
{


}
//---------------------------------------------------------------

unsigned int FaceModeDataSource::getElementCount()
{
	return m_ElementCollect.size();
}


	/**获取元素的贴图名
*成功返回true 失败返回false
*/
bool  FaceModeDataSource::getElementTexture(unsigned int index,Ogre::String& textureName)
{
	if(index>=m_ElementCollect.size())
		return false;

	textureName=m_ElementCollect[index].first;//获取贴图名
	return true;

}

	/**获取元素的用户数据
	*成功返回true 失败返回false
	*/
bool FaceModeDataSource::getElementUserData(unsigned index,Ogre::String& elementData)
{

	if(index>=m_ElementCollect.size())
		return false;

	elementData=m_ElementCollect[index].second;//获取用户数据
	return true;

}







//---------------------------------------------------------------
UISelectHead:: UISelectHead()
:UIBase("UISelectHead",""),m_pReturnButton(NULL)
{


}


//---------------------------------------------------------------
 UISelectHead::~ UISelectHead()
{


}


//---------------------------------------------------------------
void  UISelectHead::init()
{

	UIBase::init();

	//Ogre::SceneManager* pSceneMrg=Application::getSingleton().getMainSceneManager();
	//Ogre::Entity* pHead=pSceneMrg->createEntity("Head.mesh");
	//Ogre::SceneNode* pScenNode=  pSceneMrg->getRootSceneNode()->createChildSceneNode();
	//pScenNode->attachObject(pHead);


	StaticImage* pImage=new StaticImage("SelectHeadBackGround","jieshu_background.png");
	registerWidget(pImage);
	Ogre::OverlayElement* pElment=pImage->getOverlayElement();
	pImage->setMetricsMode(Ogre::GMM_RELATIVE);
	pImage->setHorizontalAlignment(Ogre::GHA_LEFT);
	pImage->setVerticalAlignment(Ogre::GVA_TOP);
	pImage->setLeft(0.0f);
	pImage->setWidth(1.0f);
	pImage->setTop(0.0f);
	pImage->setHeight(1.0f);

	SliderGallery* pSliderGallery=new SliderGallery("SelectHeadSliderGallery",new FaceModeDataSource(),"cz/SliderGallery");
	registerWidget(pSliderGallery);
	pSliderGallery->getOverlayElement()->setHorizontalAlignment(Ogre::GHA_LEFT);
	//pSliderGallery->getOverlayElement()->setLeft();




	m_pReturnButton=new ImageButton("SelectHeadReturn","moshi_fanhui_release.png","moshi_fanhui_press.png");
	m_pReturnButton->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_pReturnButton->setLeft(10);
	m_pReturnButton->setVerticalAlignment(Ogre::GVA_BOTTOM);
	m_pReturnButton->setTop(-128);
	m_pReturnButton->setWidth(80);
	m_pReturnButton->setHeight(80);
	registerWidget(m_pReturnButton);





	//返回按钮



}


//----------------------------------------------------------------
void  UISelectHead::sliderGalleryhit(SrollButton* pbutton)
{

    const Ogre::String& userData=pbutton->getUserData();
	g_userInformation.setHeadMode(userData);

	///选择了头套进入选择脸型界面
	setVisible(false);
	UIBase* pSelectFace=Application::getSingleton().getUIByName("UISelectFaceMode");
	pSelectFace->setVisible(true);


	return ;

}

void UISelectHead::buttonHit(Widget* pWidget)
{
	if(pWidget==NULL)
		return ;


	//返回按钮，回到选择人物界面
	if(pWidget==m_pReturnButton)
	{

		Ogre::StringVectorPtr pUserList=Tools::getUserFaceFileList();

		if(pUserList.isNull()||pUserList->empty())///如果没有信息就返回到捕脸界面
		{
		   
			UIBase* pUI=Application::getSingletonPtr()->getUIByName("CaptureFaceUI");
		    pUI->setVisible(true);
	
     	}else///返回到选择用户的界面
		{

			UIBase* pUI=Application::getSingletonPtr()->getUIByName("UISelectUser");
			pUI->setVisible(true);
		}
         setVisible(false);

		return ;

	}

}