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
    
    
#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE
   // static  Ogre::String           getIphoneDocumentPath();
#endif
    
    
    
};