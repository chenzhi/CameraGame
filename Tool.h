//
//  Tool.h
//  ogreApp
//
//  Created by thcz on 11-7-6.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#pragma once

/**
 工具类，一般都是静态函数，完成一些通用功能 
*/

#include "rapidxml.hpp"


class Tools
{
 
public:
    Tools();

    ~Tools();

    
    
    
    /**销毁一个overlay和其子对像*/
    //static  void DestroyOverlayAndChild(Ogre:::Over);
    
    
    /**获取所有已经保存的用户*/
    static  Ogre::StringVectorPtr getUserFaceFileList();
    
    
    ///获取用户照象后保存的路径
    static Ogre::String       getUserFacePath();
    
    ///把纹理转到image里
    static void ConverTextureToImage(Ogre::TexturePtr pTexture,Ogre::Image& image);
    
    /**保存ogre贴图文件到指定目录。
        *@remark ptexture 。在iphone下必须为HBU_DYNAMIC_WRITE_ONLY 创建。
       */
    static bool  saveOgreTexture(const char* fileName,Ogre::TexturePtr pTexture);
    
    

    
    /**保存屏幕快照
	*@param pTexture 必须是rendetTarget标志创建的帖图
	*/
	static bool  getScreenSnapshot(Ogre::TexturePtr pTexture);
    
    
    
    

   // static bool testSaveTexture(const Ogre::String& fileName);
    
    


   // static  Ogre::String           getIphoneDocumentPath();
     static bool  saveOgreTextureToPhotosAlbum(Ogre::TexturePtr pTexture);

    
    

	 /**把一个毫秒单位转成小时、分、秒格式
	 *@param t 毫秒
	 */
	static void  parseTime(unsigned int t,unsigned int& hourcs,unsigned int& minutes,unsigned int& seconds);

    
	/**
	* Desc:  获得一个数的指定位的值
	* @param value ：数值
	* @param bit ：要指定的位数，个位就是1，十位就是2，百位就是3....
	* return : 返回指定位的值
	*/
	 static int getValueByBit(int value , int bit);



	 static Ogre::String getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, const Ogre::String &defaultValue)
	 {
		 if(XMLNode->first_attribute(attrib.c_str()))
			 return XMLNode->first_attribute(attrib.c_str())->value();
		 else
			 return defaultValue;
	 }

	 static float  getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib,float  defaultValue)
	 {
		 if(XMLNode->first_attribute(attrib.c_str()))
			 return Ogre::StringConverter::parseReal(XMLNode->first_attribute(attrib.c_str())->value());
		 else
			 return defaultValue;
	 }

	 static bool getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, bool defaultValue)
	 {
		 if(!XMLNode->first_attribute(attrib.c_str()))
			 return defaultValue;

		 if(Ogre::String(XMLNode->first_attribute(attrib.c_str())->value()) == "true")
			 return true;

		 return false;
	 }


    
};