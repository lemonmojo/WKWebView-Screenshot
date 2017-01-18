//
//  LMThumbnailView.m
//  WKWebViewTest
//
//  Created by Felix Deimel on 21.08.15.
//  Copyright (c) 2015 Lemon Mojo - Felix Deimel e.U. All rights reserved.
//

#import "WKWebView+Screenshot.h"

@implementation LMFakeWKView

- (instancetype)initWithWebView:(WKWebView*)webView
{
    self = [super init];
    
    if (self) {
        self.webView = webView;
    }
    
    return self;
}

+ (instancetype)fakeWKViewWithWebView:(WKWebView*)webView
{
    return [[[LMFakeWKView alloc] initWithWebView:webView] autorelease];
}

- (void)dealloc
{
    self.webView = nil;
    
    [super dealloc];
}

- (NSView*)_thumbnailView
{
    return nil;
}

- (NSWindow*)window
{
    return self.webView.window;
}

- (void*)pageRef
{
    return [self.webView performSelector:@selector(_pageForTesting)];
}

@end

@implementation LMWKThumbnailView {
    CaptureScreenshotCompletionHandler _completionHandler;
}

+ (void)captureScreenshotOfWKWebView:(WKWebView*)wkWebView withCompletionHandler:(CaptureScreenshotCompletionHandler)completionHandler
{
    __block LMWKThumbnailView* thumbnailView = [[LMWKThumbnailView alloc] initWithWKWebView:wkWebView completionHandler:^(NSImage *screenshot) {
        [thumbnailView release];
        
        if (completionHandler) {
            completionHandler(screenshot);
        }
    }];
    
    [thumbnailView captureScreenshot];
}

- (instancetype)initWithWKWebView:(WKWebView*)wkWebView completionHandler:(CaptureScreenshotCompletionHandler)completionHandler
{
    self.fakeWKView = [LMFakeWKView fakeWKViewWithWebView:wkWebView];
    
    if (self = [super initWithFrame:NSZeroRect fromWKView:(WKView*)self.fakeWKView]) {
        self.exclusivelyUsesSnapshot = YES;
        _completionHandler = [completionHandler copy];
    }
    
    return self;
}

- (void)dealloc
{
    [_completionHandler release]; _completionHandler = nil;
    self.fakeWKView = nil;
    
    [super dealloc];
}

- (void)captureScreenshot
{
    [self requestSnapshot];
}

- (void)_didTakeSnapshot:(CGImageRef)image
{
    NSImage *screenshot = nil;
    
    if (image) {
        screenshot = [[[NSImage alloc] initWithCGImage:image size:NSZeroSize] autorelease];
    }
    
    CaptureScreenshotCompletionHandler completionHandler = _completionHandler;
    
    if (completionHandler) {
        completionHandler(screenshot);
    }
}

@end

@implementation WKWebView (Screenshot)

- (void)captureScreenshotWithCompletionHandler:(CaptureScreenshotCompletionHandler)completionHandler
{
    [LMWKThumbnailView captureScreenshotOfWKWebView:self withCompletionHandler:completionHandler];
}

- (NSImage*)captureScreenshotWithTimeout:(dispatch_time_t)timeout
{
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    
    __block NSImage* theScreenshot = nil;
    
    [self captureScreenshotWithCompletionHandler:^(NSImage *screenshot) {
        if (screenshot) {
            theScreenshot = [screenshot retain];
        }
        
        dispatch_semaphore_signal(semaphore);
    }];
    
    while (dispatch_semaphore_wait(semaphore, DISPATCH_TIME_NOW)) {
        if (dispatch_time(DISPATCH_TIME_NOW, 0) > timeout) {
            theScreenshot = nil;
            break;
        }
        
        [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0]];
    }

    return [theScreenshot autorelease];
}

@end
