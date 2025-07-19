#pragma once

#define STATIC_ASSERT(COND,MSG) typedef char assert_failed_##MSG[(COND)?1:-1]

