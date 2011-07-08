//
//  Config.h
//  ogreApp
//
//  Created by thcz on 11-7-7.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


/**************************
 游戏常量宏和全局变量定义在此处
 *************************/




///ui overlay 界面定义所有路径

#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE

const  static std::string g_UIPath="Media/CameraGame/UI/";

#else

const  static std::string g_UIPath="../../../Media/CameraGame/UI/";

#endif