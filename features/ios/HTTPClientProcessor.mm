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
    auto id = library::httpClientExecuteNextRequest(url, data);

    // Non-empty id means we have request to execute.
    if (id)
    {
        [self
            performHTTPRequestWithId:id
            url:@(url.c_str())
            data:@(data.c_str())
        ]; 
    }
}

- (void)performHTTPRequestWithId:(intptr_t)id
    url:(NSString *)url
    data:(NSString *)data
{
    NSLog(@"TODO performHTTPRequestWithId '%ld' url '%@' data '%@'", id, url, data);
    NSURL *address = [NSURL URLWithString:url];
    if (!address)
    {
        library::httpClientCompleteRequest(id, false, "");
    }

    // Define completion handler.
    auto handler = ^void(NSData *data, NSURLResponse *response, NSError *error) {
        // Failure.
        if (error)
        {
            NSString *errorDescription = error.localizedDescription;
            std::string reason = std::string([errorDescription UTF8String]);
            library::httpClientCompleteRequest(id, false, reason);
        }
        // Success.
        else
        {
            NSString *strdata =
                [[NSString alloc]
                    initWithData:data encoding:NSUTF8StringEncoding
                ];
            std::string reply = std::string([strdata UTF8String]);
            library::httpClientCompleteRequest(id, true, reply);
        }
        NSLog(@"Completion handler invoked");
    };

    // Perform GET/POST request.
    NSURLSession *session = NSURLSession.sharedSession;
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:address];
    request.HTTPMethod = data.length ? @"POST" : @"GET";
    request.HTTPBody = [data dataUsingEncoding:NSUTF8StringEncoding];
    auto task =
        [session
            dataTaskWithRequest:request
            completionHandler:handler
        ];
    [task resume];
}

@end

