FEATURE core.h/Impl
#define CORE_SEQUENCE_ACTION(NAME, CALL) \
    core::Sequence::Action(NAME, [=]() { return CALL; })
