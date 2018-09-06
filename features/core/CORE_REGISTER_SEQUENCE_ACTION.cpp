FEATURE core.h/Impl
#define CORE_REGISTER_SEQUENCE_ACTION(SEQUENCE, ACTION, CALL) \
    SEQUENCE.registerAction(ACTION, [=]() { return CALL; });

