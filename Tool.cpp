//
//  Tool.cpp
//  ogreApp
//
//  Created by thcz on 11-7-6.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "Tool.h"
#include "config.h"


Ogre::StringVectorPtr Tools::getUserFaceFileList()
{
    
    
    std::string userFacePath;
    
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
    
    userFacePath= Ogre::iPhoneDocumentsDirectory();
    Ogre::LogManager::getSingleton().logMessage(userFacePath);
    //userFacePath=  "/Users/thcz/Downloads";
    //userFacePath+=g_UserFacePath;
#else
    userFacePath=g_UserFacePath;
    
#endif

	//*/
	Ogre::String groupName="UserFace";
	Ogre::ResourceGroupManager* pResourceManager=Ogre::ResourceGroupManager::getSingletonPtr();
	if(pResourceManager->resourceGroupExists(groupName)==false)
	{
		pResourceManager->createResourceGroup(groupName);
		pResourceManager->addResourceLocation(userFacePath,"FileSystem",groupName);

		
		pResourceManager->initialiseResourceGroup(groupName);
		//pResourceManager->loadResourceGroup(groupName);
	}
	
	//*/
    
	Ogre::Archive* pArchive= Ogre::ArchiveManager::getSingleton().load(userFacePath,"FileSystem");
	
	///如果未打开表示没有用户信息
	if(pArchive==NULL)
	{
        return Ogre::StringVectorPtr();
	}else
	{
        /*
		Ogre::ArchiveManager::getSingleton().unload(pArchive);
	    pArchive= Ogre::ArchiveManager::getSingleton().load(userFacePath,"FileSystem");
        if(pArchive==NULL)
		{
			return Ogre::StringVectorPtr();
		}
        
        //*/

	}
    
   
    Ogre::StringVectorPtr pFileList= pArchive->list(false,false);
   //  Ogre::ArchiveManager::getSingleton().unload(pArchive);
  
    ///排除后缀非png的文件
    Ogre::StringVector filteFile;
    int size=pFileList->size();
    
    for(int i=0;i<size;++i)
    {
        Ogre::String fileName=pFileList->at(i);
        if(fileName.find(g_UserFaceFormt,0)==Ogre::String::npos)
        {
            filteFile.push_back(fileName);
        }
    }

	size=filteFile.size();
	for(int i=0;i<size;++i)
	{
		Ogre::StringVector::iterator it =std::find(pFileList->begin(),pFileList->end(),filteFile[i]);
		if(it!=pFileList->end())
		{
			pFileList->erase(it);
		}
	}
    
    return pFileList;
   
   
}