FEATURE ios.mm/Properties
@property (nonatomic, strong) RenderVC *renderVC;

FEATURE ios.mm/Setup
[self setupRenderVC];

FEATURE ios.mm/Impl
- (void)setupRenderVC
{
    self.renderVC = [RenderVC new];
    self.window.rootViewController = self.renderVC;
}
