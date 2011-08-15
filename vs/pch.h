
#pragma  once



#include "Ogre.h"



#ifdef  WIN32


#define OGRE_PLATFORM  OGRE_PLATFORM_WIN32

#else

#define OGRE_PLATFORM OGRE_PLATFORM_IPHONE

#endif



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

#include <Windows.h>
#include "OIS/OIS.h"

#else if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE

#include "OgreGLESPlugin.h"

#endif




#define SafeDelete(a) if(a!=NULL){delete a;a=NULL;}