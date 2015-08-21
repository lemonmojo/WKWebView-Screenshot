//
//  LMThumbnailView.h
//  WKWebViewTest
//
//  Created by Felix Deimel on 21.08.15.
//  Copyright (c) 2015 Lemon Mojo - Felix Deimel e.U. All rights reserved.
//

#import <WebKit/WebKit.h>

#if WK_API_ENABLED
#if !TARGET_OS_IPHONE
@class WKView;

NS_CLASS_AVAILABLE(10_10, 8_0) /* WK_CLASS_AVAILABLE(10_10, 8_0) */
@interface _WKThumbnailView : NSView

- (instancetype)initWithFrame:(NSRect)frame fromWKView:(WKView *)wkView;
@property (nonatomic) CGFloat scale;
- (void)_didTakeSnapshot:(CGImageRef)image;
- (void)_viewWasParented;
- (void)_viewWasUnparented;

@end
#endif // TARGET_OS_IPHONE
#endif // WK_API_ENABLED

typedef void (^CaptureScreenshotCompletionHandler) (NSImage* screenshot);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface LMWKThumbnailView : _WKThumbnailView

+ (void)captureScreenshotOfWKWebView:(WKWebView*)wkWebView withCompletionHandler:(CaptureScreenshotCompletionHandler)completionHandler;

- (instancetype)initWithWKWebView:(WKWebView*)wkWebView completionHandler:(CaptureScreenshotCompletionHandler)completionHandler;
- (void)captureScreenshot;

@end

@interface WKWebView (Screenshot)

- (void)captureScreenshotWithCompletionHandler:(CaptureScreenshotCompletionHandler)completionHandler;
- (NSImage*)captureScreenshotWithTimeout:(dispatch_time_t)timeout;

@end