/******************************************
游戏模式三界面
*******************************************/


#include "UIBase.h"
#include "Widget.h"


class WarModeThree;


///道具数据源
class ItemDataSource :public SliderGalleryDataSource
{
public:

	ItemDataSource()
	{
		m_Collect.push_back(std::make_pair("model3__egg_press.png","egg"));
		m_Collect.push_back(std::make_pair("model3__brick_press.png","egg"));
		m_Collect.push_back(std::make_pair("model3__shoes_press.png","egg"));
		m_Collect.push_back(std::make_pair("model3__knife_press.png","egg"));
		m_Collect.push_back(std::make_pair("model3__baseball_press.png","egg"));
		m_Collect.push_back(std::make_pair("model3__baseball_press.png","egg"));
		m_Collect.push_back(std::make_pair("model3__baseball_press.png","egg"));
		
	}


	~ItemDataSource(){}


	
	/**获取共有多少个元素
	*/
	virtual	unsigned int getElementCount()
	{
		return m_Collect.size();
	}


	/**获取元素的贴图名
	*成功返回true 失败返回false
	*/
	virtual bool  getElementTexture(unsigned int index,Ogre::String& textureName)
	{
		if(index>=m_Collect.size())
			return false;
		textureName=m_Collect[index].first;
		return true;

	}



	/**获取元素的用户数据
	*成功返回true 失败返回false
	*/
	virtual bool getElementUserData(unsigned index,Ogre::String& elementData)
	{

		if(index>=m_Collect.size())
			return false;
		elementData=m_Collect[index].second;
		return true;
	
	}



protected:

		typedef std::vector< std::pair<Ogre::String ,Ogre::String >  > ItemCollect;
		ItemCollect    m_Collect;


};







class UIWarModeThree : public UIBase
{

public:

	UIWarModeThree(WarModeThree* pWarMode);


	~UIWarModeThree();


	void init();


	/**设置当前能量槽的百分比
	*@percent 百分比。0--1之前
	*/
	void setPowerPercent(float percent);


	//void update(float time);


	/**界面控件事件*/
	void sliderGalleryhit(SrollButton* pbutton );///滚动栏按钮选择事件

	void buttonHit(Widget* button);


	/**获取当前ui选择的道具类型 */
	const Ogre::String& getCurrentItemType()const {return m_ItemType;}


protected:


	/**开始触摸,发射道具就*/
	//virtual void onBeginTouch(int x,int y);



	WarModeThree*        m_pWarMode;    ///对应的战斗模式

	Widget*              m_pPauseButton;//暂停按钮
	StaticImage*         m_pPowerBackground;///能量槽背景
	StaticImage*         m_pPowerImage;     ///能量槽图片

	Widget*              m_pSnapshotButton;//快速拍照
	SliderGallery*       m_pItemSelectSlider;///选择道具滚动控件

	Ogre::String         m_ItemType;



};