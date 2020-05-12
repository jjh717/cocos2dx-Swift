#ifndef  _COCOS_BRIDGING_H_
#define  _COCOS_BRIDGING_H_

#import <UIKit/UIKit.h>


@interface CocosBridging : NSObject {
 
} 

- (UIView *)cocosScreenSetting:(UIView *) view;
- (void)runScene:(UIView *) view;

- (void)EnterBackground;
- (void)EnterForeground;

@end

#endif
