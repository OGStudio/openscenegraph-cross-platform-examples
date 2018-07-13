FEATURE ios.h/Impl
@interface HTTPClientProcessor : NSObject

- (instancetype)initWithHTTPClient:(void *)client;
- (void)process;

@end

FEATURE ios.mm/Impl
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
