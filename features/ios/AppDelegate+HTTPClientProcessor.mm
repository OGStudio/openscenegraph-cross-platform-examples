FEATURE ios.mm/Properties
@property (nonatomic, strong) HTTPClientProcessor *httpClientProcessor;

FEATURE ios.mm/Setup
[self setupHTTPClientProcessor];

FEATURE ios.mm/Impl
- (void)setupHTTPClientProcessor
{
    self.httpClientProcessor = [HTTPClientProcessor new];
    // Regularly process the processor.
    // TODO Subscribe regular processing to frames.
    /*
    self.httpClientProcessorTimer =
        [NSTimer
            scheduledTimerWithTimeInterval:0
            target:self
            selector:@selector(processHTTPClientProcessor)
            userInfo:nil
            repeats:YES
        ];
    */
}
