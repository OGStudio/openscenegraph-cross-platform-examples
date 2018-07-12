
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "ios.h"

#include "library.h"

// ios+AppDelegate Start
@implementation AppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    auto frame = [[UIScreen mainScreen] bounds];
    self.window = [[UIWindow alloc] initWithFrame:frame];

// ios+AppDelegate End
    // ios+RenderVC Start
    self.window.rootViewController = [RenderVC new];
    
    // ios+RenderVC End
    // ios+HTTPClientProcessor Start
    [self setupHTTPClientProcessor];
    
    // ios+HTTPClientProcessor End
// ios+AppDelegate Start
    self.window.backgroundColor = UIColor.whiteColor;
    [self.window makeKeyAndVisible];

    return YES;
}

// ios+AppDelegate End
    // ios+HTTPClientProcessor Start
    - (void)setupHTTPClientProcessor
    {
        auto client = library::httpClient();
        self.httpClientProcessor = [[HTTPClientProcessor alloc] initWithHTTPClient:client];
        // Regularly process the processor.
        self.httpClientProcessorTimer =
            [NSTimer
                scheduledTimerWithTimeInterval:0
                target:self
                selector:@selector(processHTTPClientProcessor)
                userInfo:nil
                repeats:YES
            ];
    }
    
    - (void)processHTTPClientProcessor
    {
        [self.httpClientProcessor process];
    }
    
    // ios+HTTPClientProcessor End
// ios+AppDelegate Start
@end
// ios+AppDelegate End

// ios+HTTPClientProcessor Start
@interface HTTPClientProcessor ()
@property (nonatomic, assign) void *client;
// TODO processors
@end

@implementation HTTPClientProcessor

- (instancetype)initWithHTTPClient:(void *)client
{
    self = [super init];

    self.client = client;

    return self;
}

- (void)process
{
    // TODO
    NSLog(@"HTTPClientProcessor.process");
}

@end

/*
    // TODO Check for URL validity.
    NSURL *address = [NSURL URLWithString:url];
    NSLog(@"TODO performGetRequest. address: '%@'", address);
    NSURLSession *session = NSURLSession.sharedSession;
    // Define completion handler.
    auto handler = ^void(NSData *data, NSURLResponse *response, NSError *error) {
        NSLog(@"Completion handler invoked");
    };
    // Perform request.
    auto task = [session
        dataTaskWithURL:address
        completionHandler:handler];
    [task resume];
*/
// ios+HTTPClientProcessor End
// ios+RenderVC Start
@interface RenderVC ()
@property (nonatomic, strong) CADisplayLink *displayLink;
@end

@implementation RenderVC

- (void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];

    // Setup render view once.
    // TODO Support render window resizing to allow multiple calls.
    static bool didSetup = false;
    if (!didSetup)
    {
        [self setupRenderView];
        didSetup = true;
    }
}

- (void)setupRenderView
{
    // Remove old display link.
    if (self.displayLink)
    {
        [self.displayLink invalidate];
        self.displayLink = nil;
    }
    // Create new display link.
    self.displayLink =
        [CADisplayLink
            displayLinkWithTarget:self
            selector:@selector(renderFrame)];
    [self.displayLink
        addToRunLoop:[NSRunLoop currentRunLoop]
        forMode:NSDefaultRunLoopMode];

    // Embed OpenSceneGraph render view.
    auto size = self.view.frame.size;
    auto renderView =
        library::init(
            size.width,
            size.height,
            [UIScreen mainScreen].scale,
            self.view
        );
    [self.view sendSubviewToBack:renderView];
}

- (void)renderFrame
{
    library::frame();
}

@end

// ios+RenderVC End

