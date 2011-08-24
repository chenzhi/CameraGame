/********************************************


**********************************************/


#pragma  once


class UIImageSet;

class Image
{

	friend class UIImageSet;
protected:

	/**构造函数
	*@param name
	*@UIImageSet 所属的imageset指针
	*@left ,top,right,bottom image内容在imageset里的相对位置。0---1之间
	*/
	Image(const Ogre::String& name,UIImageSet* pParent,float left,float top,float right,float bottom)
		:m_Name(name),m_pParent(pParent),m_UV(left,top,right,bottom)
	{

	}


	~Image(){}

public:
	const Ogre::String& getName()const {return m_Name;}


	const Ogre::Vector4& getUV()const {return m_UV;}


	UIImageSet*          getParent()const {return m_pParent;}


protected:

	Ogre::String    m_Name;///名字
	UIImageSet*     m_pParent;
	Ogre::Vector4   m_UV;  ///每个点的uv


};


typedef std::vector<Image*> UIImageCollect;