FEATURE ios.h/Impl
@interface AppDelegate : UIResponder <UIApplicationDelegate>
    @property (nonatomic, strong) UIWindow *window;
@end

FEATURE ios.mm/Properties
@interface AppDelegate ()

FEATURE ios.mm/Setup
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    auto frame = [[UIScreen mainScreen] bounds];
    self.window = [[UIWindow alloc] initWithFrame:frame];

FEATURE ios.mm/Impl
    self.window.backgroundColor = UIColor.whiteColor;
    [self.window makeKeyAndVisible];

    return YES;
}

FEATURE ios.mm/End
@end
