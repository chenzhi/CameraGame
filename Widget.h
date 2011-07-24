
/*****************************************************************
界面控件的封装
*********************************************************************/





#pragma  once


#include "SdkTrays.h"



class Ogre::OverlayElement;

/**
图片按钮
*/
class ImageButton :public Widget
{

public:


	/**构造函数
	*@name                控件名
	*@param normalTexture 正常装态下的图片
	*@param pressTexture  手指按下的图片
	*/
	ImageButton( const Ogre::String& name,const Ogre::String& normalTexture,const Ogre::String& pressTexture);


	virtual ~ImageButton();


protected:


	virtual void _cursorPressed(const Ogre::Vector2& cursorPos);

	virtual void _cursorReleased(const Ogre::Vector2& cursorPos) ;

	virtual void _focusLost();



	/**根据状态刷新显示*/
	void updateState();



protected:


	 Ogre::String m_NormalTexture;
	 Ogre::String m_PressTexture;

	 Ogre::MaterialPtr m_pMaterial;

	 ButtonState       m_State;



};




/******************************************************************
静态图片控件
*******************************************************************/
class StaticImage : public Widget
{

public:


	
	/**构造函数
	*@param  textureName 贴图文件名
	*/
	StaticImage(const Ogre::String& name, const Ogre::String& textureName);


    virtual	~StaticImage();


	void setImage(const Ogre::String& textureName);


protected:

	Ogre::MaterialPtr m_pMaterial;


};




/*********************************************
长按图片按钮,按下时间超过指定时间会发出事件
**************************************************/

class TimeImageButton:public Widget
{

public:
	enum TIB
	{

		NORMAL,///正常状态
		Press,///长按后弹起状态。这时会出现减号符


	};

public:
	TimeImageButton(const Ogre::String&name, const Ogre::String& imageName);

	~TimeImageButton();


	virtual void update(float time);


	virtual void _cursorPressed(const Ogre::Vector2& cursorPos);

	virtual void _cursorReleased(const Ogre::Vector2& cursorPos) ;

	virtual void _focusLost();



	///重置状态
	void reset();

	TIB getState()const{return m_State;}
    
    
    
    


protected:

	///根据状态更新显示
	void updateState();
    
    ///摇动按钮
    void rotateButton(float time);



	float m_Time;///长按多长时间
	float m_CurrentTime;//当时计时
	TIB   m_State;
	bool  m_isPress;///是否按下

	Ogre::MaterialPtr m_pBackgroundMaterial;
	Ogre::MaterialPtr m_pDeleteMaterial;

	Ogre::OverlayElement* m_pDeleteElement;///删除按钮
    

};



/***********************************************
会显示3d图形的按钮。可以把一scenenode挂到这个按钮上
**************************************************/
class Image3DButton :public Widget
{
public:

	Image3DButton(const Ogre::String& name,Ogre::SceneNode* pNode);


	~Image3DButton();


    /**设置挂载的节点*/
	void   setSceneNode(Ogre::SceneNode* pNode);

	virtual void _cursorPressed(const Ogre::Vector2& cursorPos);

	virtual void _cursorReleased(const Ogre::Vector2& cursorPos) ;


	///返回名字
	virtual const Ogre::String& getName();


protected:

	Ogre::Overlay*  m_pOveraly;

	Ogre::SceneNode* m_pScenNode;

	 

};



/*************************************************
滑动按钮，
****************************************************/

///滚动按钮的数据源
class 	SliderGalleryDataSource
{
public:
	SliderGalleryDataSource(){}


	virtual ~SliderGalleryDataSource(){}


	/**获取共有多少个元素
	*/
	virtual	unsigned int getElementCount()=0;


	/**获取元素的贴图名
	*成功返回true 失败返回false
	*/
	virtual bool  getElementTexture(unsigned int index,Ogre::String& textureName)=0;



	/**获取元素的用户数据
	*成功返回true 失败返回false
	*/
	virtual bool getElementUserData(unsigned index,Ogre::String& elementData)=0;


};


///滚动窗口里的每一个按钮
class SrollButton
{

public:

	SrollButton(Ogre::OverlayElement* pElement)
		:m_pElement(pElement),m_OriginalPos(0.0f),m_targetPos(0.0f),m_Visible(false)
	{

		Ogre::MaterialPtr pMat=pElement->getMaterial();
		assert(pMat.isNull()==false);
		pMat= pMat->clone(pElement->getName());
		pElement->setMaterialName(pMat->getName());
		m_OriginaWidth=pElement->getWidth();
		m_TargetWidth=m_OriginaWidth;

		m_OriginaHeight=pElement->getHeight();
		m_TargetHeight=m_OriginaHeight;

		m_OriginaZOrder=pElement->getZOrder();
		m_TargetZorder=m_OriginaZOrder;

		return;

	}

	/**滚动函数*/
	void sroll(float precent)
	{
		if(m_pElement==NULL)
			return ;
		if(precent>=1.0f)
		{
			m_pElement->setLeft(m_targetPos.x);
			m_pElement->setTop(m_targetPos.y);
			m_pElement->show();
			return ;
		}

		m_pElement->setLeft(m_OriginalPos.x+(m_targetPos.x-m_OriginalPos.x)*precent);
		m_pElement->setTop(m_OriginalPos.y+(m_targetPos.y-m_OriginalPos.y)*precent);
		m_pElement->setWidth(m_OriginaWidth+(m_TargetWidth-m_OriginaWidth)*precent);
		m_pElement->setHeight(m_OriginaHeight+(m_TargetHeight-m_OriginaHeight)*precent);
		//m_pElement->getZOrder()
		

		

		
		
		if(m_Visible)
		{
			m_pElement->show();
		}else
		{
			m_pElement->hide();

		}
		return ;

	}


	/**设置按钮的图片
	*/
	void setTextureName(const Ogre::String& textureName)
	{
		if(m_pElement==NULL)
			return ;
		m_pElement->getMaterial()->getTechnique(0)->getPass(0)->
			getTextureUnitState(0)->setTextureName(textureName);


	}


	/**调置用户数据
	*/
	void setUserData(const Ogre::String& data)
	{
		m_userData=data;
	}


	/**返回用户数据
	*/
	const Ogre::String getUserData()const
	{
		return m_userData;
	}


	/**判断鼠标是在按钮的范围
	*/
	bool isCursorOver(const Ogre::Vector2& pos)
	{
		if(m_pElement==NULL)
			return false;
		if(m_pElement->isVisible()==false)
			return false;

		return Widget::isCursorOver(m_pElement,pos);


	}


	///设置是否可见
	void setVisible(bool b)
	{
		if(m_pElement!=NULL)
		{
			if(b)
			{
            	m_pElement->show();				
			}else
			{

				m_pElement->hide();
			}

		}
	}


public:

	Ogre::OverlayElement*  m_pElement; 
	Ogre::Vector2          m_OriginalPos; ///滚动开始的位置 
	Ogre::Vector2          m_targetPos;   ///滚动结不束位置

	int                    m_OriginaWidth;//宽
	int                    m_TargetWidth;

	int                    m_OriginaHeight;//高
	int                    m_TargetHeight;

	int                    m_OriginaZOrder;  //z顺序
	int                    m_TargetZorder; 


	bool                   m_Visible;     ///滚动是否隐藏
	Ogre::String           m_userData;     ///用户保存数据



};


class SliderGallery : public Widget
{

public:



public:

	SliderGallery(const Ogre::String& name,SliderGalleryDataSource* pDataSource);
 
   virtual	~SliderGallery();


   /**设置数据源*/
   void setDataSource(SliderGalleryDataSource* pSource);



protected:

	/**鼠标回调事件
	*/
	virtual void _cursorPressed(const Ogre::Vector2& cursorPos);

	/**鼠标回调事件
	*/
	virtual void _cursorReleased(const Ogre::Vector2& cursorPos) ;

	/**鼠标回调事件
	*/
	virtual void _cursorMoved(const Ogre::Vector2& cursorPos);




protected:


	///每帧更新涵数
	void update(float tim);


	///向前滚动一格
	void previsouButton();


	///向后滚动一格
	void nextButton();

	///获取所有按钮原来的位置
	void saveButtonPos() ;

	///删除所有的滚动按钮
	void destroySrollButton();


	///刷新所有button数据
	void resetButtonInformation();


	///滚动结束
	void endRoll();


	///更新左右滚动按钮状态
	void updateSrollButton();


	protected:

	
	Ogre::OverlayElement* m_pPrevisouButton;///向前一个按钮

	Ogre::OverlayElement* m_pNextButton; ///向后一个按钮



	typedef std::vector<SrollButton*> SrollButtonCollect;
	SrollButtonCollect         m_ButtonCollect; ///记录滚动所有的按钮


	bool                  m_IsPress;         ///是否按下
	int                   m_RollDir;        ///滚动方向 0,表示不滚动。-1向滚动一格 1向左路滚动一格
	float                 m_RollTime;       ///滚动时间




	SliderGalleryDataSource*      m_pDataSource; ////数据源
	unsigned int                  m_DataIndex; ///最左边按钮对应数据源里第几个数据


};


/*************************************************
可旋转的静态图片
****************************************************/
class RotateImage :public StaticImage
{

public:
	RotateImage(const Ogre::String& name, const Ogre::String& imageName);

	~RotateImage();

	/**设置朝向
	*@param radian 弧度单位
	*/
	void setOrientation(float radian);


	void update(float time);

protected:

	


};