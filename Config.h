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

#include "UserInformation.h"



///ui overlay 界面定义所有路径

#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE

const  static std::string g_UIPath="Media/CameraGame/UI/";
const  static std::string g_UserFacePath="/UserFace";
const  static std::string g_EnemyFormat="Media/EnemyFormat.cfg";///敌人阵型文件


#else


const  static std::string g_UIPath="../../../Media/CameraGame/UI/";
const  static std::string g_UserFacePath="../../../Media/CameraGame/UserFace";
const  static std::string g_EnemyFormat="../../../Media/EnemyFormat.cfg";


#endif




///用户照片保存的格式
static  const  std::string g_UserFaceFormt=".png";

///用户选择信息
static UserInformation g_userInformation;

///不能被击打目标的脸型
static const   Ogre::String  m_FriendFaceImage="";
