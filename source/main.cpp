#include "sdk_init.hpp"

#define APPLICATION_NAME "oss-rtld"
#define APPLICATION_NAME_LEN 8

struct ApplicationName {
    int unknown;
    int name_lengh;
    char name[APPLICATION_NAME_LEN + 1];
};

__attribute__((section(".rodata.module_name")))
ApplicationName application_name = {
    .unknown = 0, .name_lengh = APPLICATION_NAME_LEN, .name = APPLICATION_NAME};

extern "C" void __rtld_start_app(Handle thread_handle,
                                 uintptr_t argument_address,
                                 void (*notify_exception_handler_ready)(),
                                 void (*call_initializator)()) {
    hs::init::Start(thread_handle, argument_address, notify_exception_handler_ready, call_initializator);
}

extern "C" void __rtld_handle_exception() {
    if (!hs::os::detail::UserExceptionHandler) {
        rtld::svc::ReturnFromException(0xF801);
        while (true) {
        }
    }

    hs::os::detail::UserExceptionHandler();
}
