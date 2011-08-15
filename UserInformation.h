
/***********************************************
全局变量。保存用户的信息

**************************************************/



#pragma  once



 
class UserInformation
{
public:

	UserInformation()
	{}


	~UserInformation(){}
	
	///用户选择的模式
	void setWarMode(unsigned int mode) {m_SelectWarMode=mode;}

	unsigned int getWarMode()const {return m_SelectWarMode;}


	///用户选择的脸的纹理
	void setUserImage(const Ogre::String& imageName){m_SelectUserImage=imageName;}

	const Ogre::String& getUserImage()const {return m_SelectUserImage;}


	///用户选择脸的模型
	void setFaceMode(const Ogre::String&faceMode)   {m_SelectFaceMode=faceMode;}

	const Ogre::String& getFaceMode()const           {return m_SelectFaceMode;}


	///用户选择头的模型
	void setHeadMode(const Ogre::String& headMode)  { m_SelectHeadMode=headMode;}

	const Ogre::String& getHeadMode()const           {return m_SelectHeadMode;}


protected:

	static  unsigned int               m_SelectWarMode;      ///用户选择的战争模式

	static Ogre::String               m_SelectUserImage;      ///用户选择的脸图

	static Ogre::String               m_SelectFaceMode;       ///选择的脸部模型

	static Ogre::String               m_SelectHeadMode;       ///选择的头部模型 




	

};