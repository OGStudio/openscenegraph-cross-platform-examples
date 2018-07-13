FEATURE ios.mm/Properties
@property (nonatomic, copy) void (^frame)();

FEATURE ios.mm/Frame
[self reportFrame];

FEATURE ios.mm/Impl
- (void)reportFrame
{
    if (self.frame != nil)
    {
        self.frame();
    }
}
