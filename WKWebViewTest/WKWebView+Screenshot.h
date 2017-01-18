//
//  LMThumbnailView.h
//  WKWebViewTest
//
//  Created by Felix Deimel on 21.08.15.
//  Copyright (c) 2015 Lemon Mojo - Felix Deimel e.U. All rights reserved.
//

#import <WebKit/WebKit.h>

@interface LMFakeWKView : NSObject

- (instancetype)initWithWebView:(WKWebView*)webView;

@property (strong) WKWebView* webView;

@end

#if WK_API_ENABLED
#if !TARGET_OS_IPHONE
@class WKView;

NS_CLASS_AVAILABLE(10_10, 8_0) /* WK_CLASS_AVAILABLE(10_10, 8_0) */
@interface _WKThumbnailView : NSView

- (instancetype)initWithFrame:(NSRect)frame fromWKView:(WKView *)wkView;

@property (nonatomic) CGFloat scale;
@property (nonatomic, readonly) CGSize snapshotSize;
@property (nonatomic) CGSize maximumSnapshotSize;
@property (nonatomic) BOOL exclusivelyUsesSnapshot;

// Defaults to NO.
@property (nonatomic) BOOL shouldKeepSnapshotWhenRemovedFromSuperview;

// This should be removed when all clients go away; it is always YES now.
@property (nonatomic) BOOL usesSnapshot;

- (void)requestSnapshot;

- (void)_didTakeSnapshot:(CGImageRef)image;
- (void)_viewWasParented;
- (void)_viewWasUnparented;

@end
#endif // TARGET_OS_IPHONE
#endif // WK_API_ENABLED

typedef void (^CaptureScreenshotCompletionHandler) (NSImage* screenshot);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface LMWKThumbnailView : _WKThumbnailView

@property (strong) LMFakeWKView* fakeWKView;

+ (void)captureScreenshotOfWKWebView:(WKWebView*)wkWebView withCompletionHandler:(CaptureScreenshotCompletionHandler)completionHandler;

- (instancetype)initWithWKWebView:(WKWebView*)wkWebView completionHandler:(CaptureScreenshotCompletionHandler)completionHandler;
- (void)captureScreenshot;

@end

@interface WKWebView (Screenshot)

- (void)captureScreenshotWithCompletionHandler:(CaptureScreenshotCompletionHandler)completionHandler;
- (NSImage*)captureScreenshotWithTimeout:(dispatch_time_t)timeout;

@end
