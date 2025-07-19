#pragma once
#include <assert.h>

#ifdef DEBUG
#define ASSERT(p) assert((p))
#else
#define ASSERT(_) do {} while (0)
#endif
