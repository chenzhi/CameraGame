/***************************************************
选择头套模型界面
*****************************************************/



#pragma  once

#include "UIBase.h"
#include "Widget.h"




class FaceModeDataSource :public SliderGalleryDataSource
{

public:

	FaceModeDataSource();


	virtual ~FaceModeDataSource();



protected:

	/**获取共有多少个元素
	*/
	virtual	unsigned int getElementCount();


	/**获取元素的贴图名
	*成功返回true 失败返回false
	*/
	virtual bool  getElementTexture(unsigned int index,Ogre::String& textureName);

	/**获取元素的用户数据
	*成功返回true 失败返回false
	*/
	virtual bool getElementUserData(unsigned index,Ogre::String& elementData);


protected:

	typedef std::vector< std::pair<Ogre::String ,Ogre::String >  > ElementCollect;
	ElementCollect m_ElementCollect;



};










class UISelectHead :public UIBase
{



public:

	 UISelectHead();

	~ UISelectHead();







protected:


	/**初始化*/
	virtual void init();


	/**点击滚动按钮回调函数*/
	 virtual void sliderGalleryhit(SrollButton* pbutton);



	 ///点击按钮回调事件
     void  buttonHit(Widget* pWidget);



protected:



	Widget* m_pReturnButton;




};