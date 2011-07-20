
/*****************************************************************
界面控件的封装
*********************************************************************/





#pragma  once


#include "SdkTrays.h"



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


	~StaticImage();


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