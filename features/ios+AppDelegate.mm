FEATURE ios.h/Impl
@interface AppDelegate : UIResponder <UIApplicationDelegate>
@property (nonatomic, strong) UIWindow *window;
@end

FEATURE ios.mm/Begin
@implementation AppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    auto frame = [[UIScreen mainScreen] bounds];
    self.window = [[UIWindow alloc] initWithFrame:frame];

FEATURE ios.mm/End
    self.window.backgroundColor = UIColor.whiteColor;
    [self.window makeKeyAndVisible];

    return YES;
}

@end
