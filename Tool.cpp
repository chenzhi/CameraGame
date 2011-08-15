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
#include "OgreCodec.h"
#include "OgreImageCodec.h"
#include  "Application.h"


Ogre::StringVectorPtr Tools::getUserFaceFileList()
{
    
    
    std::string userFacePath= Tools::getUserFacePath();


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

//-----------------------------------------------------------------------
Ogre::String Tools::getUserFacePath()
{
    
#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE
    Ogre::String  userFacePath= Ogre::iPhoneDocumentsDirectory();
    userFacePath+=g_UserFacePath;
    return userFacePath;
#else
    
    return g_UserFacePath;
    
#endif

}

//----------------------------------------------------------------------- 
void Tools::ConverTextureToImage(Ogre::TexturePtr pTexture,Ogre::Image& image)
{
    Ogre::PixelFormat pixelFormat=  pTexture->getFormat();
	
	Ogre::HardwarePixelBufferSharedPtr pBuffer=pTexture->getBuffer();
	pBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
	
    
	const Ogre::PixelBox& pixelBox=pBuffer->getCurrentLock();
	size_t rowPitch=pixelBox.rowPitch;
	size_t height=pTexture->getHeight();
    size_t width=pTexture->getWidth();
    
	size_t size=rowPitch*height*Ogre::PixelUtil::getNumElemBytes(pixelFormat);
    
	Ogre::uchar* pImageBuffer= OGRE_ALLOC_T(Ogre::uchar,size , Ogre::MEMCATEGORY_GENERAL);
	memcpy(pImageBuffer,pixelBox.data,size);
    
	image.loadDynamicImage(pImageBuffer,width,height,1,pixelFormat,true);
    
	pBuffer->unlock();
    
	return ;
    
}



//----------------------------------------------------------------------- 
/*
bool Tools::SaveTexture(Ogre::TexturePtr pTexture,const Ogre::String& filename)
{
    if(pTexture.isNull())
        return true;
    
    Ogre::String strExt;
    size_t pos = filename.find_last_of(".");
    if( pos == Ogre::String::npos )
        OGRE_EXCEPT(
                    Ogre::Exception::ERR_INVALIDPARAMS, 
                    "Unable to save image file '" + filename + "' - invalid extension.",
                    "Image::save" );
    
    while( pos != filename.length() - 1 )
        strExt += filename[++pos];
    
    Ogre::Codec * pCodec = Ogre::Codec::getCodec(strExt);
    if( !pCodec )
    {
        OGRE_EXCEPT(
                    Ogre::Exception::ERR_INVALIDPARAMS, 
                    "Unable to save image file '" + filename + "' - invalid extension.",
                    "Image::save" );
    }
    
    Ogre::ImageCodec::ImageData* imgData = OGRE_NEW Ogre::ImageCodec::ImageData();
    imgData->format = pTexture->getFormat();
    imgData->height = pTexture->getHeight();
    imgData->width = pTexture->getWidth();
    imgData->depth = pTexture->getDepth();
    
    
    
    Ogre::HardwarePixelBufferSharedPtr pbuffer=pTexture->getBuffer();
    
    void * pdata= pbuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
    
	const Ogre::PixelBox& pixelBox=pbuffer->getCurrentLock();
	size_t rowPitch=pixelBox.rowPitch;
	size_t height=pTexture->getHeight();
    size_t size=rowPitch*height*Ogre::PixelUtil::getNumElemBytes(pTexture->getFormat());
    imgData->size = size;
    
    // Wrap in CodecDataPtr, this will delete
    Ogre::Codec::CodecDataPtr codeDataPtr(imgData);
    // Wrap memory, be sure not to delete when stream destroyed
    Ogre::MemoryDataStreamPtr wrapper(OGRE_NEW Ogre::MemoryDataStream(pdata, size, false));
    pCodec->codeToFile(wrapper, filename, codeDataPtr);    
    pbuffer->unlock();
    
       
    return true;
}
//*/

//--------------------------------------------------------
bool  Tools::saveOgreTexture(const char* fileName,Ogre::TexturePtr pTexture)
{
#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE
    if (pTexture.isNull()) 
    {
        return true;
    }
    
    Ogre::HardwarePixelBufferSharedPtr pBuffer= pTexture->getBuffer();
    pBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);
    const Ogre::PixelBox &pb = pBuffer->getCurrentLock();
    
    unsigned char* data=(unsigned char*)pb.data;
    int width=pTexture->getWidth();
    int height=pTexture->getHeight();
    int rowPitch=width* Ogre::PixelUtil::getNumElemBytes(pTexture->getFormat()); 
    
    CGColorSpaceRef colorSpace	= CGColorSpaceCreateDeviceRGB(); 
    CGContextRef newContext		= CGBitmapContextCreate(data, width, height, 8, rowPitch, colorSpace, kCGImageAlphaPremultipliedLast );
    CGImageRef currentFrame			= CGBitmapContextCreateImage(newContext);
    
    UIImage* pImage=[UIImage imageWithCGImage:currentFrame];
    NSData* pdata= UIImagePNGRepresentation(pImage);
    NSString* strFile=[NSString stringWithCString:fileName encoding:NSASCIIStringEncoding];
    [pdata writeToFile:strFile atomically:YES];  
    
    CGContextRelease(newContext); 
    CGColorSpaceRelease(colorSpace);
    CGImageRelease(currentFrame);	
    
    
    pBuffer->unlock();
    
    
#endif
    
    return true;
    
}

//--------------------------------------------------------
bool  Tools::getScreenSnapshot(Ogre::TexturePtr pTexture)
{

	if(pTexture.isNull())
		return false;

    
    Ogre::SceneManager* pSceneManager=Application::getSingleton().getMainSceneManager();
	Ogre::TexturePtr pRenderTarget=pTexture;
    static  Ogre::Camera* SnapshotCamera=NULL;
     Ogre::Viewport* pViewport=NULL;

    if(SnapshotCamera==NULL)
    { 
        SnapshotCamera=pSceneManager->createCamera("ScreenSnapshot_Camera");
        pSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(SnapshotCamera);
    }
    
    
    
  //  if(pRenderTarget.isNull())
  //  {
  //      pRenderTarget=Ogre::TextureManager::getSingleton().createManual
  //      ("ScreenSnapshot_Rendtarget", "General", Ogre::TEX_TYPE_2D,     
		//512,512,0,Ogre::PF_R8G8B8A8,Ogre::TU_RENDERTARGET | /*Ogre::TU_DEFAULT | */Ogre::TU_DYNAMIC_WRITE_ONLY,0,false);

  //      
  //      assert(pRenderTarget.isNull()==false);
  //      Ogre::RenderTarget* ptarget=pRenderTarget->getBuffer()->getRenderTarget();

  //      
  //      
  //  }
  //  
     Ogre::RenderTarget* ptarget=pRenderTarget->getBuffer()->getRenderTarget();
	 pViewport=ptarget->addViewport(SnapshotCamera);
	 ptarget->setAutoUpdated(false);
	 pViewport->setOverlaysEnabled(false);
	 pViewport->setClearEveryFrame(true);
	 pViewport->setBackgroundColour(Ogre::ColourValue::Black);

    
    assert(pViewport);
    Ogre::Camera* pMainCamera=Application::getSingleton().getMainCamera();
    SnapshotCamera->setFOVy(pMainCamera->getFOVy());
    SnapshotCamera->setNearClipDistance(pMainCamera->getNearClipDistance());
    SnapshotCamera->setFarClipDistance(pMainCamera->getFarClipDistance());
    
    SnapshotCamera->getParentSceneNode()->setPosition(pMainCamera->getParentSceneNode()->getPosition());
    SnapshotCamera->getParentSceneNode()->setOrientation(pMainCamera->getParentSceneNode()->getOrientation());
    pRenderTarget->getBuffer()->getRenderTarget()->update();

	ptarget->removeAllViewports();


//	Ogre::Math::intersects()
    
    return true;
}




//--------------------------------------------------------
bool  Tools::saveOgreTextureToPhotosAlbum(Ogre::TexturePtr pTexture)
{
//#ifndef __arm__
///    return false;
//#endif

#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE
    
    if(pTexture.isNull())
        return false;
    
    
    
    if (pTexture.isNull()) 
    {
        return true;
    }
    
    Ogre::HardwarePixelBufferSharedPtr pBuffer= pTexture->getBuffer();
   // pBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);
   // const Ogre::PixelBox &pb = pBuffer->getCurrentLock();
    
   // pBuffer->unlock();
    //return true;
    
   
    int width=pTexture->getWidth();
    int height=pTexture->getHeight();
    int rowPitch=width* Ogre::PixelUtil::getNumElemBytes(pTexture->getFormat()); 
    
    int size=rowPitch*height;
    
    void* data=malloc(size);
    
    //memcpy(data, pb.data, size);
    memset(data, 128, size);
    //pBuffer->unlock();
    
    CGColorSpaceRef colorSpace	= CGColorSpaceCreateDeviceRGB(); 
    CGContextRef newContext		= CGBitmapContextCreate(data, width, height, 8, rowPitch, colorSpace,/*kCGImageAlphaNone */kCGImageAlphaPremultipliedLast );
    CGImageRef currentFrame= CGBitmapContextCreateImage(newContext);
    
   // UIImage* pImage=[UIImage imageWithCGImage:currentFrame];
    //NSData* pdata= UIImagePNGRepresentation(pImage);
  
    UIImage* pImage=[UIImage imageWithContentsOfFile:@"youxi_zhanting_release.png"];
    
    UIImageWriteToSavedPhotosAlbum(pImage, nil, nil, nil);
    
    //[pdata writeToFile:strFile atomically:YES];  
    
    CGContextRelease(newContext); 
    CGColorSpaceRelease(colorSpace);
    CGImageRelease(currentFrame);	
    
    
    free(data);
    

#endif
    
    return true;
      
}

