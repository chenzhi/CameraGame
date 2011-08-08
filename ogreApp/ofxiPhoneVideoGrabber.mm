/*
 *  ofxiPhoneVideoGrabber.mm
 */

#include "ofxiPhoneVideoGrabber.h"

#import <UIKit/UIKit.h>




#if __IPHONE_OS_VERSION_MIN_REQUIRED > __IPHONE_3_2



#if defined  __arm__

@implementation iPhoneVideoGrabber

@synthesize captureSession	= _captureSession;
@synthesize grabberPtr;

#pragma mark -
#pragma mark Initialization
- (id)init {
	self = [super init];
//	if (self) {
//		/*We initialize some variables (they might be not initialized depending on what is commented or not)*/
//		self.imageView = nil;
//		self.prevLayer = nil;
//		self.customLayer = nil;
//	}
	bInitCalled = false;
	return self;
}



//--------------------------------------------------------
- (void)initCapture:(int)framerate capWidth:(int)w capHeight:(int)h
{
	/*We setup the input*/
	captureInput	= [AVCaptureDeviceInput 
										  deviceInputWithDevice:[AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo] 
										  error:nil];
										  	
	/*We setupt the output*/
	AVCaptureVideoDataOutput *captureOutput = [[AVCaptureVideoDataOutput alloc] init];
	/*While a frame is processes in -captureOutput:didOutputSampleBuffer:fromConnection: delegate methods no other frames are added in the queue.
	 If you don't want this behaviour set the property to NO */
	captureOutput.alwaysDiscardsLateVideoFrames = YES; 
	/*We specify a minimum duration for each frame (play with this settings to avoid having too many frames waiting
	 in the queue because it can cause memory issues). It is similar to the inverse of the maximum framerate.
	 In this example we set a min frame duration of 1/10 seconds so a maximum framerate of 10fps. We say that
	 we are not able to process more than 10 frames per second.*/
	captureOutput.minFrameDuration = CMTimeMake(1, framerate);
    fps=framerate;
	
	/*We create a serial queue to handle the processing of our frames*/
	dispatch_queue_t queue;
	queue = dispatch_queue_create("cameraQueue", NULL);
	[captureOutput setSampleBufferDelegate:self queue:queue];
	dispatch_release(queue);
	
	// Set the video output to store frame in BGRA (It is supposed to be faster)
	NSString* key = (NSString*)kCVPixelBufferPixelFormatTypeKey; 
	NSNumber* value = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_32BGRA]; 

	NSDictionary* videoSettings = [NSDictionary dictionaryWithObject:value forKey:key]; 
	[captureOutput setVideoSettings:videoSettings]; 

	/*And we create a capture session*/	
	self.captureSession = [[AVCaptureSession alloc] init];
	
	[self.captureSession beginConfiguration]; 
	
	NSString * preset = AVCaptureSessionPresetMedium;
	width	= 480;
	height	= 360;	
		
	if( w == 640 && h == 480 ){
		preset = AVCaptureSessionPreset640x480;
		width	= w;
		height	= h;
	}
	else if( w == 1280 && h == 720 ){
		preset = AVCaptureSessionPreset1280x720;
		width	= w;
		height	= h;		
	}

	[self.captureSession setSessionPreset:preset]; 
	
	/*We add input and output*/
	[self.captureSession addInput:captureInput];
	[self.captureSession addOutput:captureOutput];
	
	[self.captureSession commitConfiguration];		
	//[self.captureSession startRunning];

	bInitCalled = true;
	
}


//--------------------------------------------------------
-(void) startCapture
{

	if( !bInitCalled )
    {
		[self initCapture:fps capWidth:width capHeight:height];
	}

	[self.captureSession startRunning];
	
	[captureInput.device lockForConfiguration:nil];
	
	//if( [captureInput.device isExposureModeSupported:AVCaptureExposureModeAutoExpose] ) [captureInput.device setExposureMode:AVCaptureExposureModeAutoExpose ];
	if( [captureInput.device isFocusModeSupported:AVCaptureFocusModeAutoFocus] )
        [captureInput.device setFocusMode:AVCaptureFocusModeAutoFocus ];

}


//--------------------------------------------------------
-(void) lockExposureAndFocus
{

	[captureInput.device lockForConfiguration:nil];
	
	//if( [captureInput.device isExposureModeSupported:AVCaptureExposureModeLocked] ) [captureInput.device setExposureMode:AVCaptureExposureModeLocked ];
	if( [captureInput.device isFocusModeSupported:AVCaptureFocusModeLocked] )	
        [captureInput.device setFocusMode:AVCaptureFocusModeLocked ];
	
	
}


//--------------------------------------------------------
-(void)stopCapture
{
	[self.captureSession stopRunning];
    
}


//--------------------------------------------------------
-(CGImageRef)getCurrentFrame
{
	return currentFrame;
}


//--------------------------------------------------------
#pragma mark -
#pragma mark AVCaptureSession delegate
- (void)captureOutput:(AVCaptureOutput *)captureOutput 
didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer 
	   fromConnection:(AVCaptureConnection *)connection 
{ 
	/*We create an autorelease pool because as we are not in the main_queue our code is
	 not executed in the main thread. So we have to create an autorelease pool for the thread we are in*/
	
	//printf("capturing!\n");	
	
	//NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer); 
    /*Lock the image buffer*/
    CVPixelBufferLockBaseAddress(imageBuffer,0); 

    /*Get information about the image*/
    uint8_t *baseAddress	= (uint8_t *)CVPixelBufferGetBaseAddress(imageBuffer); 
    size_t bytesPerRow		= CVPixelBufferGetBytesPerRow(imageBuffer); 
    size_t widthIn			= CVPixelBufferGetWidth(imageBuffer); 
    size_t heightIn			= CVPixelBufferGetHeight(imageBuffer);  
    
    
    grabberPtr->updatePixels(baseAddress,widthIn,heightIn,bytesPerRow);
    CVPixelBufferUnlockBaseAddress(imageBuffer,0);
    
    return ;
    
	    
    /*Create a CGImageRef from the CVImageBufferRef*/
    CGColorSpaceRef colorSpace	= CGColorSpaceCreateDeviceRGB(); 
    CGContextRef newContext		= CGBitmapContextCreate(baseAddress, widthIn, heightIn, 8, bytesPerRow, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
    
    
    CGImageRelease(currentFrame);	
    
    currentFrame			= CGBitmapContextCreateImage(newContext); 

	//CGImageRelease(currentFrame);	
	//currentFrame = CGImageCreateCopy(newImage);		
		
    /*We release some components*/
    CGContextRelease(newContext); 
    CGColorSpaceRelease(colorSpace);

	/*We relase the CGImageRef*/
	//CGImageRelease(newImage);
		
	/*We unlock the  image buffer*/
	CVPixelBufferUnlockBaseAddress(imageBuffer,0);
	
	grabberPtr->updatePixelsCB(currentFrame);
   // grabberPtr->updatePixelsCB(newImage);
	
	//[pool release];
} 

#pragma mark -
#pragma mark Memory management

- (void)dealloc
{
    [super dealloc];
}


@end




namespace Ogre
{
    template<> ofxiPhoneVideoGrabber* Ogre::Singleton<ofxiPhoneVideoGrabber>::ms_Singleton=0;
    
}


//--------------------------------------------------------
ofxiPhoneVideoGrabber::ofxiPhoneVideoGrabber(int width,int height)
:m_pTemPixel(NULL)
{
	fps		= 30;
	grabber = [[iPhoneVideoGrabber alloc] init];
    grabber.grabberPtr = this;
    m_width=width;
    m_height=height;
	pixels	= NULL;
    
    initGrabber(m_width,m_height);
}

//--------------------------------------------------------
ofxiPhoneVideoGrabber::~ofxiPhoneVideoGrabber()
{
	[grabber stopCapture];
    [grabber release];
	clear();
    if(m_pTemPixel!=NULL)
    {
        free(m_pTemPixel);
    }
}

//--------------------------------------------------------
void ofxiPhoneVideoGrabber::clear()
{
	if( pixels != NULL ){
		delete[] pixels;
		pixels = NULL;
	}
	//tex.clear();
}

//--------------------------------------------------------
void ofxiPhoneVideoGrabber::setCaptureRate(int capRate)
{
	fps = capRate;
}

//--------------------------------------------------------
void ofxiPhoneVideoGrabber::initGrabber(int w, int h)
{

	[grabber initCapture:fps capWidth:w capHeight:h];
    
	
	
	m_width	= grabber->width;
	m_height	= grabber->height;
	
	clear();
	
	pixels = new unsigned char[m_width * m_height * 4];
	memset(pixels, 0, m_width*m_height*4);
	
	//tex.allocate(width, height, GL_RGB);
		
	[grabber startCapture];
    m_isCapture=true;
	
	m_bUpdateTex = true;
    
    ///初始化纹理
    initOgreTexture();
}

//--------------------------------------------------------
void ofxiPhoneVideoGrabber::updatePixelsCB( CGImageRef & ref )
{
	m_bUpdateTex = convertCGImageToPixels(ref, pixels);
}


//-------------------------------------------------------------
void ofxiPhoneVideoGrabber::updatePixels(uint8_t* pImage,int w,int h, int preByterow)
{
   // for (int i=0; i<h; ++i) 
   // {
        memcpy(pixels, pImage, preByterow*h);
   // }
    
    m_bUpdateTex=true;
    return ;
    
}

	
//--------------------------------------------------------
void ofxiPhoneVideoGrabber::draw(float x, float y)
{
	draw(x, y, m_width, m_height);
}

//--------------------------------------------------------
void ofxiPhoneVideoGrabber::draw(float x, float y, float w, float h)
{
	if( m_bUpdateTex )
    {
		//tex.loadData(pixels, w, h, GL_RGB);
		m_bUpdateTex = false;
	}
	//tex.draw(x, y, w, h);
}

//--------------------------------------------------------
bool ofxiPhoneVideoGrabber::convertCGImageToPixels(CGImageRef & ref, unsigned char * pixels)
{
	CGContextRef spriteContext;

	int bytesPerPixel	= CGImageGetBitsPerPixel(ref)/8;
	if(bytesPerPixel == 3) bytesPerPixel = 4;
	
	int w			= CGImageGetWidth(ref);
	int h			= CGImageGetHeight(ref);
    
	
	// Allocated memory needed for the bitmap context
	//GLubyte *pixelsTmp	= (GLubyte *) malloc(w * h * bytesPerPixel);
    
    if(m_pTemPixel==NULL)
    {
        m_pTemPixel	= (unsigned char *) malloc(w * h * bytesPerPixel);
    }
   
	
	// Uses the bitmatp creation function provided by the Core Graphics framework. 
	spriteContext = CGBitmapContextCreate(pixels, w, h, CGImageGetBitsPerComponent(ref), w * bytesPerPixel, CGImageGetColorSpace(ref), bytesPerPixel == 4 ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNone);
	
	if(spriteContext == NULL)
    {
		//ofLog(OF_LOG_ERROR, "convertCGImageToPixels - CGBitmapContextCreate returned NULL");
		//free(pixelsTmp);
		return false;
	}

	CGContextDrawImage(spriteContext, CGRectMake(0.0, 0.0, (CGFloat)w, (CGFloat)h), ref);
	CGContextRelease(spriteContext);
	
    return true;
	int totalSrcBytes = w*h*bytesPerPixel;  
	int j = 0;
	for(int k = 0; k < totalSrcBytes; k+= bytesPerPixel )
    {
		pixels[j  ] = m_pTemPixel[k  ];
		pixels[j+1] = m_pTemPixel[k+1];
		pixels[j+2] = m_pTemPixel[k+2];
        pixels[j+3]=  m_pTemPixel[k+3];
		
		j+=4;
	}
					
	//free(pixelsTmp);
	return true;
}


//--------------------------------------------------------
void ofxiPhoneVideoGrabber::stopCapture()
{
    [grabber stopCapture];
    m_isCapture=false;
}

//--------------------------------------------------------
void ofxiPhoneVideoGrabber::startCapture()
{
    [grabber startCapture];
    m_isCapture=true;
}



//--------------------------------------------------------
Ogre::TexturePtr ofxiPhoneVideoGrabber::getOgreTexture() const 
{
    return m_pTexture;
    
}

bool  ofxiPhoneVideoGrabber::SaveTexture(const char* fileName)
{
    
    if(m_pTexture.isNull())
        return true;
    
    Ogre::HardwarePixelBufferSharedPtr pPixelBuff= m_pTexture->getBuffer(0,0);
    if(pPixelBuff.isNull()==false)
    {
        pPixelBuff->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);
        const Ogre::PixelBox &pb = pPixelBuff->getCurrentLock();
        size_t rowPitch = pb.rowPitch;
        size_t pixelSize=Ogre::PixelUtil::getNumElemBits(pb.format);
        pixelSize/=8;
        rowPitch*=pixelSize;
        char* data = (char*)(pb.data);
        
        
        Ogre::Image image;
        image.load("sdk_logo.png", "General");
        data=(char*)image.getData();
        int width=image.getWidth();
        int height=image.getHeight();
        rowPitch=width*Ogre::PixelUtil::getNumElemBytes(image.getFormat());
        
        
        /*Create a CGImageRef from the CVImageBufferRef*/
        CGColorSpaceRef colorSpace	= CGColorSpaceCreateDeviceRGB(); 
        CGContextRef newContext		= CGBitmapContextCreate(data, width, height, 8, rowPitch, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
        
        CGImageRef currentFrame			= CGBitmapContextCreateImage(newContext); 
        
        
        
        UIImage* pImage=[UIImage imageWithCGImage:currentFrame];
        NSData* pdata= UIImagePNGRepresentation(pImage);
        NSString* strFile=[NSString stringWithCString:fileName encoding:NSASCIIStringEncoding];
        [pdata writeToFile:strFile atomically:YES];
        //[strFile autorelease];
        
        CGContextRelease(newContext); 
        CGColorSpaceRelease(colorSpace);
        CGImageRelease(currentFrame);	
        pPixelBuff->unlock();
        
        return true;
    }
    return false;
        
}

    
    
    
    



//--------------------------------------------------------
void ofxiPhoneVideoGrabber::initOgreTexture()
{
    if(m_pTexture.isNull()==false)
    {
        Ogre::TextureManager::getSingleton().remove(m_pTexture->getName());
        m_pTexture.setNull();
    }
    
        
    m_pTexture=Ogre::TextureManager::getSingleton().createManual("videoTexture_ofxiPhoneVideoGrabber", "General", 
    Ogre::TEX_TYPE_2D, m_width, m_height, 1, 1,Ogre::PF_R8G8B8A8); 
    
    return ;
    
}


//--------------------------------------------------------
void ofxiPhoneVideoGrabber::updateOgreTexture()
{
    if(m_isCapture==false)
    {
        return ;
    }
    
    if(m_pTexture.isNull())
        return ;
    
    
    
    if(isUpdate())
    {
        
        unsigned char* pPixel=getPixels();
        
        Ogre::HardwarePixelBufferSharedPtr pPixelBuff= m_pTexture->getBuffer(0,0);
        int yoffset=m_pTexture->getHeight()-m_height;
        if(pPixelBuff.isNull()==false)
        {
            pPixelBuff->lock(Ogre::HardwareBuffer::HBL_DISCARD);
            const Ogre::PixelBox &pb = pPixelBuff->getCurrentLock();
            
            // size_t height = pb.getHeight();
            // size_t width = pb.getWidth();
            // size_t depth = pb.getDepth();
            size_t rowPitch = pb.rowPitch;
            // size_t slicePitch = pb.slicePitch;
            size_t pixelSize=Ogre::PixelUtil::getNumElemBits(pb.format);
            pixelSize/=8;
            
            rowPitch*=pixelSize;
            Ogre::uint8 *data = static_cast<Ogre::uint8*>(pb.data);
            
            for(int i=0;i<m_height ;++i)
            {
                unsigned char* pRow=pPixel+i*m_width*4;
                unsigned char* ptarget=data+(i+yoffset)*rowPitch;
                
                for(int j=0;j<m_width;++j)
                {
                    int pixIndex=j*4;
                    ptarget[pixIndex]=pRow[pixIndex+2];
                    ptarget[pixIndex+1]=pRow[pixIndex+1];
                    ptarget[pixIndex+2]=pRow[pixIndex];
                    ptarget[pixIndex+3]=pRow[pixIndex+3];
                }
                
               // memcpy(ptarget,pRow,m_width*pixelSize);
            }
            
            pPixelBuff->unlock();
            
        }
        
        
        
        ///重置状态
        m_bUpdateTex=false;

        
    }
    
    
    
}


//--------------------------------------------------------
void ofxiPhoneVideoGrabber::update()
{
    if(isUpdate()&&m_isCapture)
    {
        updateOgreTexture();
    }
}


//--------------------------------------------------------
bool ofxiPhoneVideoGrabber::getOgreTexture(Ogre::TexturePtr pTexture)
{
    
    unsigned char* pPixel=getPixels();
    
    Ogre::HardwarePixelBufferSharedPtr pPixelBuff= pTexture->getBuffer(0,0);
    int yoffset=pTexture->getHeight()-m_height;
    if(pPixelBuff.isNull()==false)
    {
        pPixelBuff->lock(Ogre::HardwareBuffer::HBL_DISCARD);
        const Ogre::PixelBox &pb = pPixelBuff->getCurrentLock();
        
        // size_t height = pb.getHeight();
        // size_t width = pb.getWidth();
        // size_t depth = pb.getDepth();
        size_t rowPitch = pb.rowPitch;
        // size_t slicePitch = pb.slicePitch;
        size_t pixelSize=Ogre::PixelUtil::getNumElemBits(pb.format);
        pixelSize/=8;
        
        rowPitch*=pixelSize;
        Ogre::uint8 *data = static_cast<Ogre::uint8*>(pb.data);
        
        for(int i=0;i<m_height ;++i)
        {
            unsigned char* pRow=pPixel+i*m_width*4;
            unsigned char* ptarget=data+(i+yoffset)*rowPitch;
            
            for(int j=0;j<m_width;++j)
            {
                int pixIndex=j*4;
                ptarget[pixIndex]=pRow[pixIndex+2];
                ptarget[pixIndex+1]=pRow[pixIndex+1];
                ptarget[pixIndex+2]=pRow[pixIndex];
                ptarget[pixIndex+3]=pRow[pixIndex+3];
            }
            
            // memcpy(ptarget,pRow,m_width*pixelSize);
        }
        
        pPixelBuff->unlock();
    }

    
    return true;
}

#endif	// (__arm__) compile only for ARM

#else   // compile for 4.0+

#warning "skipping ofxIphoneVideoGrabber compilation because you need > 3.2 iOS SDK"

#endif




