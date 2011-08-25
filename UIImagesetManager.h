
/**************************************************
imageset管理器。
**************************************************/


#pragma  once

#include "UIIMageSet.h"




class UIImagesetManager :public Ogre::Singleton<UIImagesetManager>
{

public:

	UIImagesetManager();

	~UIImagesetManager();


	/**从指定的文件中创建一个imageset.
	*@return 成功返回真。失败返回假
	*@param resourceGroup.ogre的资源组
	*/
	bool createImageset(const Ogre::String& fileName,const Ogre::String& resourceGroup);



	/**获取指定的imageset，无返回空
	*/
	UIImageSet* getImagesetByName(const Ogre::String& name)const  ;


	/**返回指定名字的imageset*/
	UIImageSet* getImagesetByFileName(const Ogre::String& name) const;



	/**销毁指定imageset*/
	void  destroyImagetset(const Ogre::String& name);


	/**销毁所有的imageset*/
	void destroyAllImageset();


	/**通过名字获取指定的image对像
	@return 无返回空指针
	*/
	Image* getImageByName(const Ogre::String& name)const ;



protected:

	typedef std::vector<UIImageSet*> ImagesetCollect;
	ImagesetCollect   m_ImagesetCollect;




};