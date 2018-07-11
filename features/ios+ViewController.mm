FEATURE ios.h/Impl
#import <UIKit/UIKit.h>

@interface ViewController: UIViewController
@end

FEATURE ios.mm/Impl
//#import "library.h"

@interface ViewController ()

/*
@property (nonatomic, strong) CADisplayLink *displayLink;
@property (nonatomic, strong) UIView *renderView;
@property (nonatomic, strong) IBOutlet UIView *parentView;
*/

@end

@implementation ViewController

- (void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    // NOTE This must be done exactly once!
    NSLog(@"TODO setup render view");
    //TODO make sure we call this once because this function is called at least twice
    // [self setupRenderView];

    // TODO REMOVE
    self.view.backgroundColor = UIColor.redColor;
}

@end

