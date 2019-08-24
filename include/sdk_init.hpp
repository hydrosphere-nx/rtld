#pragma once

#include <stdint.h>
#include <rtld.hpp>

#ifndef WEAK
#define WEAK __attribute__((weak))
#endif

namespace hs {
namespace os {
namespace detail {
// FIXME: We set this weak to avoid a compiler optimization on a call.
void WEAK UserExceptionHandler(void);
}  // namespace detail
}  // namespace os

namespace init {
void WEAK Start(unsigned long thread_handle, unsigned long argument_address,
                void (*notify_exception_handler_ready)(),
                void (*call_initializator)());
}

}  // namespace hs
