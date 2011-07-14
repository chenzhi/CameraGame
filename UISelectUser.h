

#pragma  once


#include "UIBase.h"


class ImageButton;
class UISelectUser :public UIBase
{

public:

	UISelectUser();

	~UISelectUser();



	virtual void init();


	/**设置有多少个用户数据*/
	void setUserList(Ogre::StringVectorPtr pUserList);


protected:

	/**删除现有的所有的用户图*/
	void destroyAllUserList();



	///用户列表
	Ogre::StringVectorPtr m_UserList;


	typedef std::vector<ImageButton*> ImageButtonCollect;
	ImageButtonCollect  m_UserButtonCollect;



};