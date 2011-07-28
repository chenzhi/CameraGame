/**************************************************
选择用户用用脸型界面。这个界面实际是3d场景,选择胖瘦脸的模型
**************************************************/



#include "UIBase.h"



///用户选择脸和头套类
class UserSelectMode
{
public:

	/**构造函数 
	*@param faceMesh 脸的mesh文件名
	*@param 头套的文件名
	*/
	UserSelectMode(const Ogre::String& faceMesh,const Ogre::String&headMesh);

	~UserSelectMode();

	///每帧更新
	void update(float time);

	/**设置脸部模型*/
	void setFaceMesh(const Ogre::String& faceMesh);

	/**设置头套模型*/
	void setHeadMesh(const Ogre::String& headMesh);

	///获取脸部mesh名
	bool  getFaceMeshName(Ogre::String& meshName)const ;

	///获取头部mesh名
	bool  getHeadMeshName(Ogre::String& meshName)const ;

	///是否与射线相交，用来做拾取
	bool isIntersect(const  Ogre::Ray& ray); 


	/**重置*/
	void reset();


	///移动到指定位置
	void translate(const Ogre::Vector3& pos);


	/**设置是否可见*/
	void setVisible(bool b);


	/**设置位置*/
	void setPosition(float x,float y,float z);

	/**更新朝向，使其面向摄像机*/
	void updateOrientation();

protected:

	
	/**更新位置
	*@param precent 0--1.0之间
	*/
	void updatePos(float precent);


	Ogre::Vector3  m_orginPos;///原始位置

	Ogre::Vector3  m_targetPos;//目标位置

	float          m_currentTime;///移动时间
	bool           m_isRoll;     ///是否移动

	Ogre::SceneNode* m_pNode;    
	Ogre::Entity*    m_pFaceEntity;
	Ogre::Entity*    m_pHeadEntity;

	Ogre::AnimationState* m_pAnimation;



};



////脸型选择数据源
class UserFaceDataSource
{

public:
	UserFaceDataSource()
	{
		m_FaceModeCollect.push_back("face_shou.mesh");
		m_FaceModeCollect.push_back("face_pang.mesh");

	}


	~UserFaceDataSource()
	{

	}


	unsigned int getFaceModeCount() const{return m_FaceModeCollect.size();}

	const Ogre::String& getFaceMode(unsigned int index	 )const
	{
		assert(index<m_FaceModeCollect.size());
		return m_FaceModeCollect[index];
	}


	
protected:

	Ogre::StringVector m_FaceModeCollect;



};




class UISelectFaceMode :public UIBase
{


public:


	
	UISelectFaceMode();


	~UISelectFaceMode();




protected:

	void init();


	/**设置是否可见*/
	virtual void  setVisible(bool b);


	///设置用户选择模型 是否可以 
	void setUserSelctModeVisible(bool b);


	/**手指离开*/
	virtual void onEndTouch(int x,int y);

	//每帧更新
	virtual void update(float time);


protected:

	///销毁所有脸部模型
	void destroyAllFaceMode();

	///初始化所有的脸部模型
	void initAllFaceMode();


	///初始背景
	void initBackEntity();

	///消毁背景
	void destroyBackEnetiy();


	typedef std::vector<UserSelectMode*>FaceModeCollect;
	FaceModeCollect                   m_FaceModeCollect;

	UserFaceDataSource                m_FaceModeSource;

	Ogre::Entity*                     m_pBackEntity;
	





};