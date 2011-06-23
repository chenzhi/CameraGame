/*
 *  ofxiPhoneVideoGrabber.h
*
 */

#pragma once

#import <UIKit/UIKit.h>



//*
#if __IPHONE_OS_VERSION_MIN_REQUIRED > __IPHONE_3_2


class ofxiPhoneVideoGrabber;

//#if defined  __arm__



@interface iPhoneVideoGrabber : UIViewController <AVCaptureVideoDataOutputSampleBufferDelegate> 
{

	@public
	
	AVCaptureDeviceInput		*captureInput;	
	AVCaptureSession			*_captureSession;
	CGImageRef currentFrame;	
	
	int width;
	int height;
	
	ofxiPhoneVideoGrabber * grabberPtr;
	
	bool bInitCalled;
}

-(void)initCapture:(int)framerate capWidth:(int)w capHeight:(int)h;

-(void)startCapture;
-(void)stopCapture;
-(void)lockExposureAndFocus;

-(CGImageRef)getCurrentFrame;


@property (nonatomic, retain) AVCaptureSession *captureSession;
@property (nonatomic)ofxiPhoneVideoGrabber * grabberPtr;


@end




class ofxiPhoneVideoGrabber : public Ogre::Singleton<ofxiPhoneVideoGrabber>
{

	public:		
    ofxiPhoneVideoGrabber();
    ~ofxiPhoneVideoGrabber();
		
		void clear();
		void setCaptureRate(int capRate);
	
		void initGrabber(int w, int h);
		void updatePixelsCB( CGImageRef & ref );		
		void draw(float x, float y);
		void draw(float x, float y, float w, float h);
	
		unsigned char * getPixels(){
			return pixels;
		}
		float getWidth(){
			return width;
		}
		float getHeight(){
			return height;
		}
    
    /**停止获取图像*/
    void stopCapture();
    
    /**开始获取图像*/
    void startCapture();
	
	protected:
		
		bool convertCGImageToPixels(CGImageRef & ref, unsigned char * pixels);
    
    
		int width, height;
	
		bool bUpdateTex;
		int fps;
		//ofTexture tex;
    
        unsigned char * pixels;
		iPhoneVideoGrabber * grabber;
};


//#endif	// (__arm__) compile only for ARM

 
#else   // (> 3.2 SDK) compile for 4.0+

#warning "skipping ofxIphoneVideoGrabber compilation because you need > 3.2 iOS SDK"


#endif
//*/


