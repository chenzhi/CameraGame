/*******************************************************

解析界面布局类

***********************************************************/




#pragma once


class UIBase;


class LayoutParse
{


public:

	LayoutParse();



	 ~LayoutParse();



	 /**解析界面文件，失败返回假*/
	 UIBase*  parse(const Ogre::String& fileName);





};