//
//  Tool.cpp
//  ogreApp
//
//  Created by thcz on 11-7-6.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "Tool.h"



Ogre::StringVectorPtr Tools::getUserFaceFileList()
{
    
    
    std::string userFacePath;
    
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
    
    userFacePath= Ogre::iPhoneDocumentsDirectory();
    //userFacePath+=g_UserFacePath;
#else
    userFacePath=g_UserFacePath;
    
#endif
    
	Ogre::Archive* pArchive= Ogre::ArchiveManager::getSingleton().load(userFacePath,"FileSystem");
	
	///如果未打开表示没有用户信息
	if(pArchive==NULL)
	{
        return Ogre::StringVectorPtr();
	}
    
    Ogre::ArchiveManager::getSingleton().unload(pArchive);
    Ogre::StringVectorPtr pFileList= pArchive->list(false,false);
    
    return pFileList;
    
    /*
    ///排除后缀非png的文件
    Ogre::StringVector filteFile;
    int size=pFileList->size();
    
    for(int i=0;i<size;++i)
    {
        Ogre::String fileName=pFileList->at(i);
        
        
        if(fileName.find(".png",fileName.begin(),fileName.end())==Ogre::String::npos)
        {
            filteFile.push_back(fileName);
        }
    }
    
    return pFileList;
   
   //*/
}