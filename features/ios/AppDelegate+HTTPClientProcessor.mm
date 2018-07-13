FEATURE ios.mm/Properties
@property (nonatomic, strong) HTTPClientProcessor *httpClientProcessor;

FEATURE ios.mm/Setup
[self setupHTTPClientProcessor];

FEATURE ios.mm/Impl
- (void)setupHTTPClientProcessor
{
    self.httpClientProcessor = [HTTPClientProcessor new];

    // Run the processor each frame.

    // NOTE Create weak reference to `self` to escape so-called retain cycle.
    // NOTE Without `weakification` we get compile time warning from ARC.
    __weak typeof(self)weakSelf = self;

    self.renderVC.frame = ^() {
        // NOTE Convert weak self to strong self.
        __strong typeof(self)self = weakSelf;

        [self.httpClientProcessor process];
    };
}
