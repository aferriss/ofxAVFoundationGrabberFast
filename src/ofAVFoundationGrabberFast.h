/*
 *  AVFoundationVideoGrabber.h
 */

#pragma once
#include "ofConstants.h"

#ifdef OF_VIDEO_CAPTURE_AVF 

//------
#include "ofBaseTypes.h"
#include "ofPixels.h"
#include "ofTexture.h"
#include "ofThread.h"

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <Accelerate/Accelerate.h>
#import <CoreMedia/CoreMedia.h>
#import <CoreVideo/CoreVideo.h>

class ofAVFoundationGrabberFast;

@interface OSXVideoGrabber : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate> {

	@public
	CGImageRef currentFrame;	
	
	int width;
	int height;
	
	BOOL bInitCalled;
	int deviceID;
	
	AVCaptureDeviceInput		*captureInput;	
	AVCaptureVideoDataOutput    *captureOutput;
	AVCaptureDevice				*device;
	AVCaptureSession			*captureSession;

	ofAVFoundationGrabberFast * grabberPtr;
}

-(BOOL)initCapture:(int)framerate capWidth:(int)w capHeight:(int)h;
-(void)startCapture;
-(void)stopCapture;
-(void)updateTexture;
-(void)lockExposureAndFocus;
-(vector <string>)listDevices;
-(void)setDevice:(int)_device;
-(void)eraseGrabberPtr;

-(CGImageRef)getCurrentFrame;

@end

//------

#endif


class ofAVFoundationGrabberFast : virtual public ofBaseVideoGrabber{

	public:		
		ofAVFoundationGrabberFast();
		~ofAVFoundationGrabberFast();
	
		void setDeviceID(int deviceID);
		void setDesiredFrameRate(int capRate);
		bool setPixelFormat(ofPixelFormat PixelFormat);

        bool setup(int w, int h);
		void update();
		bool isFrameNew() const;
		void close();
	
		ofPixels&		 		getPixels();
        const ofPixels&		    getPixels() const;

		float getWidth() const{
			return width;
		}
		float getHeight() const{
			return height;
		}

        bool isInitialized() const;
	
		void updatePixelsCB();
		vector <ofVideoDevice> listDevices() const;
		ofPixelFormat getPixelFormat() const;
    
        ofTexture * getTexture();
        ofTexture texture;
	
	protected:
		bool newFrame = false;
		bool bHavePixelsChanged = false; 
		void clear();
		int width, height;
	
		int device = 0;
        bool bIsInit = false;
	
		int fps  = -1;
		ofTexture tex;
		ofPixels pixels;

		#ifdef __OBJC__
			OSXVideoGrabber * grabber;
		#else
			void * grabber;
		#endif
	
	public:
		ofPixelFormat pixelFormat;
		ofPixels pixelsTmp;
		bool bLock = false;
		ofMutex capMutex;

};

#endif

