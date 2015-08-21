# WKWebView+Screenshot

Summary
-------

WKWebView+Screenshot provides simple methods that use private(!) APIs of the WebKit framework to capture a screenshot of a WKWebView running on OS X.

Let me repeat the important part: This way of capturing screenshots of a WKWebView may break at any time since it's using private and undocumented APIs! It's also very likely that Apple would not allow an App that uses this method in the Mac App Store!

Unfortunately, I'm not aware of any other way to capture screenshots of an WKWebView at the moment so this is probably your best bet if you're publishing outside of the App Store.

ARC is currently not supported but it should be easy to convert the project. Alternatively, if your project is using ARC, you can also just disable it for WKWebView+Screenshot.m ([see this StackOverflow post](http://stackoverflow.com/questions/6646052)).

Sample Usage
------------

Asynchronous method:
```
[wkWebView captureScreenshotWithCompletionHandler:^(NSImage *screenshot) {
  self.imageView.image = screenshot;
}];
```

 Synchronous method:
```
dispatch_time_t timeout = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC));
self.imageView.image = [wkWebView captureScreenshotWithTimeout:timeout];
```

License
-------

[New BSD License](http://en.wikipedia.org/wiki/BSD_licenses). For the full license text, see [here](https://raw.github.com/LemonMojo/WKWebView-Screenshot/master/LICENSE).

Credits
-------
WKWebView+Screenshot was created by [Felix Deimel](https://github.com/LemonMojo).<br />
