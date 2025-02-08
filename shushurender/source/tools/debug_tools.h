#ifndef DEBUG_TOOL_H
#define DEBUG_TOOL_H

#define DEBUG

#ifdef DEBUG
#include "debug_message.h"
#else
#define DEBUG_PRINTF(...)
#define ERR_PRINT(...)
#endif

#endif // DEBUG_TOOL_H