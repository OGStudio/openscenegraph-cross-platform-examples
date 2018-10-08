
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

// AppDelegate Start
@interface AppDelegate ()

// AppDelegate End
    // AppDelegate+RenderVC Start
    @property (nonatomic, strong) RenderVC *renderVC;
    
    // AppDelegate+RenderVC End
// AppDelegate Start
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    auto frame = [[UIScreen mainScreen] bounds];
    self.window = [[UIWindow alloc] initWithFrame:frame];

// AppDelegate End
    // AppDelegate+RenderVC Start
    [self setupRenderVC];
    
    // AppDelegate+RenderVC End
// AppDelegate Start
    self.window.backgroundColor = UIColor.whiteColor;
    [self.window makeKeyAndVisible];

    return YES;
}

// AppDelegate End
    // AppDelegate+RenderVC Start
    - (void)setupRenderVC
    {
        self.renderVC = [RenderVC new];
        self.window.rootViewController = self.renderVC;
    }
    // AppDelegate+RenderVC End
// AppDelegate Start
@end
// AppDelegate End


// RenderVC Start
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

// RenderVC End
    // RenderVC+FrameReporting Start
    [self reportFrame];
    
    // RenderVC+FrameReporting End
// RenderVC Start
}

// RenderVC End
    // RenderVC+FrameReporting Start
    - (void)reportFrame
    {
        if (self.frame != nil)
        {
            self.frame();
        }
    }
    // RenderVC+FrameReporting End
// RenderVC Start
@end

// RenderVC End

