FEATURE network.h/Include
#include "network-extlib.h"

FEATURE network-extlib.h/Impl
#define MG_ENABLE_SSL 1
#include <mongoose.h>

FEATURE network-extlib.cpp/Impl
#include <mongoose.c>
