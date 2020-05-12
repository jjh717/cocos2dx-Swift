#import "CocosBridging.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"
#include "OpenItemScene.h"
#include "AppDelegate.h"

@implementation CocosBridging
 
static AppDelegate s_sharedApplication;
static UIView *contentView;

- (UIView *)cocosScreenSetting:(UIView *) view {
    cocos2d::Application *app = cocos2d::Application::getInstance();

    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();
 
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                            pixelFormat: (__bridge NSString *)cocos2d::GLViewImpl::_pixelFormat
                                            depthFormat: cocos2d::GLViewImpl::_depthFormat
                                     preserveBackbuffer: NO
                                             sharegroup: nil
                                          multiSampling: cocos2d::GLViewImpl::_multisamplingCount > 0 ? YES : NO
                                        numberOfSamples: cocos2d::GLViewImpl::_multisamplingCount ];

    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];
    
    return eaglView;
}

- (void)runScene:(UIView *) view {
    contentView = view;
    
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView((__bridge void *)contentView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);
 
    cocos2d::Application::getInstance()->run();
}

- (void)ResourcesDestroy {
    #if USE_AUDIO_ENGINE
        AudioEngine::end();
    #elif USE_SIMPLE_AUDIO_ENGINE
        SimpleAudioEngine::end();
    #endif
}

- (void)EnterBackground {
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}
 
- (void)EnterForeground {
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}
 
- (void)dealloc {
    
}
 
@end
