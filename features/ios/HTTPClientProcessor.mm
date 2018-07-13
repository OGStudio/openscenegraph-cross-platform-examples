FEATURE ios.h/Impl
@interface HTTPClientProcessor : NSObject

- (void)process;

@end

FEATURE ios.mm/Impl
@interface HTTPClientProcessor ()
// TODO processors?
@end

@implementation HTTPClientProcessor

- (void)process
{
    // Collect one pending HTTP request per execution run.
    std::string url;
    std::string data;
    int id = library::httpClientNextPendingRequest(url, data);

    // Non-empty id means we have request to execute.
    if (id)
    {
        [self
            performHTTPRequestWithId:id
            url:@(url.c_str())
            data:@(data.c_str())
        ]; 
    }

    // TODO Remove completed HTTP requests.
    /*
    for (HTTPURLRequest *request in self.requests)
    {
        if (status == COMPLETED

    }
    */
}

- (void)performHTTPRequestWithId:(int)id
    url:(NSString *)url
    data:(NSString *)data
{
    NSLog(@"TODO performHTTPRequestWithId '%d' url '%@' data '%@'", id, url, data);

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
}

@end

