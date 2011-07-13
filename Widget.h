
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