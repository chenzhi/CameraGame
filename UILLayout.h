
/***********************************************
从一个layout文件中读入界面布局
*************************************************/
#pragma once 

#include "UIBase.h"
#include "rapidxml.hpp"

class UILayout :public UIBase
{

public:

	UILayout(const Ogre::String& fileName);


	~UILayout();


	virtual void init();


protected:


	/**导入layout文件相关函数
	*@{
	*/

	/**
	*@param fileName 导入layout文件名
	*@return 成功返回真。失败返回假
	*/
	bool loadLayoutFile(const Ogre::String& fileName);


	/**处理根窗口*/
	bool processRootWindow(rapidxml::xml_node<>* pNode);

	/**处理窗口*/
	bool processWindow(rapidxml::xml_node<>* pNode);

	/**处理属性*/
	bool processProperty(rapidxml::xml_node<>* pNode);


	/**获取当前节点下的property的子节点的值
	@return 成功返回真。失败返回假
	*/
	bool  getChildProperty(rapidxml::xml_node<>* pNode,const Ogre::String& propertyName, Ogre::String& Value);


	/**把cegui的矩型字型串转成ogre overlay的类型*/
	bool  ConvertCEGUIRectToOgre(const Ogre::String& CEGUICoord,Ogre::Vector4& rect);


	/**@}
	*/




};