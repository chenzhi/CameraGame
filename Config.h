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


#pragma  once





///ui overlay 界面定义所有路径

#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE

const  static std::string g_UIPath="Media/CameraGame/UI/";
const  static std::string g_UserFacePath="Media/CameraGame/UserFace";


#else


const  static std::string g_UIPath="../../../Media/CameraGame/UI/";
const  static std::string g_UserFacePath="../../../Media/CameraGame/UserFace/";


#endif




///用户选择进入的模式
static  unsigned int g_UserMode =0;