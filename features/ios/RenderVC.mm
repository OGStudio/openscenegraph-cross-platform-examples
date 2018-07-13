FEATURE ios.h/Impl
@interface RenderVC : UIViewController
@end

FEATURE ios.mm/Properties
@interface RenderVC ()
    @property (nonatomic, strong) CADisplayLink *displayLink;

FEATURE ios.mm/Frame
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

FEATURE ios.mm/Impl
}

FEATURE ios.mm/End
@end

