/*****************************************************


*******************************************************/



#pragma  once


#include "UIImage.h"
#include "rapidxml.hpp"





class UIImageSet
{

	friend class UIImagesetManager;
protected:

	/**构造函数
	*@filename imageset文件名
	*/
	UIImageSet(const Ogre::String& fileName,const Ogre::String& resourceGroup);

	~UIImageSet();
public:


	/**返回imageset的文件名*/
	const Ogre::String& getFileName()const {return m_FileName;}

	/**返回imageset的名*/
	const Ogre::String& getName()const;

	/**获取对应的帖图文件名*/
	const Ogre::String& getTextureName()const {return m_TextureName;}


	/**获取指定的image.如果没有返回空*/
	Image*  getImageByName(const Ogre::String& name)const ;


	/**获取image的数量*/
	unsigned  int getImageCount()const;

	/**获取指定索引的image，如果没有返回空*/
	Image*   getImageByIndex(unsigned int index)const;




protected:

	/**加入一个image*/
	bool       addImage(Image* pImage);

	/**删除所有的image*/
	void       destroyAllImage();

	/** xml相关函数
	@{*/

	Ogre::String getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, const Ogre::String &defaultValue = "");

	Ogre::Real getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, Ogre::Real defaultValue = 0);

	bool getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, bool defaultValue = false);


	/**处理imaset set*/
	bool processImageset(rapidxml::xml_node<>* XMLRoot,const Ogre::String& resourceGroup);

	/**处理image*/
	bool processImage(rapidxml::xml_node<>* XMLRoot);


	/**@}*/

	Ogre::String      m_Name;

	Ogre::String      m_FileName;    ///对应的image文件名

	Ogre::String      m_TextureName;///对应的图片名

	Ogre::Vector2     m_Rect;       ///图片的大小

	UIImageCollect    m_ImageCollect; ///所有image的集合

	Ogre::TexturePtr  m_pOgreTexture;

	



};


