# WKWebView+Screenshot

**Update January 18, 2017**: Found another workaround by faking the presence of the WKView.

**Update October 22, 2016**: This doesn't work anymore in 10.12.1 (maybe even 10.12, didn't test) because `WKView` is not exposed as a subview of `WKWebView` anymore. There is however a new API in the making that will allow taking screenshots of `WKWebView`s without using private API: https://bugs.webkit.org/show_bug.cgi?id=161450

Summary
-------

WKWebView+Screenshot provides simple methods that use private(!) APIs of the WebKit framework to capture a screenshot of a WKWebView running on OS X.

Let me repeat the important part: This way of capturing screenshots of a WKWebView may break at any time since it's using private and undocumented APIs! It's also very likely that Apple would not allow an App that uses this method in the Mac App Store!

Unfortunately, I'm not aware of any other way to capture screenshots of an WKWebView at the moment so this is probably your best bet if you're publishing outside of the App Store.

ARC is currently not supported but it should be easy to convert the project. Alternatively, if your project is using ARC, you can also just disable it for WKWebView+Screenshot.m ([see this StackOverflow post](http://stackoverflow.com/questions/6646052)).

Sample Usage
------------

Asynchronous method:
```objc
[wkWebView captureScreenshotWithCompletionHandler:^(NSImage *screenshot) {
  self.imageView.image = screenshot;
}];
```

 Synchronous method:
```objc
dispatch_time_t timeout = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC));
self.imageView.image = [wkWebView captureScreenshotWithTimeout:timeout];
```

License
-------

[New BSD License](http://en.wikipedia.org/wiki/BSD_licenses). For the full license text, see [here](https://raw.github.com/LemonMojo/WKWebView-Screenshot/master/LICENSE).

Credits
-------
WKWebView+Screenshot was created by [Felix Deimel](https://github.com/LemonMojo).<br />
