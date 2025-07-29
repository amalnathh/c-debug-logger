#include "log.h"

int main() {
    // These work in debug builds, disappear in production
    log_info("This is an info");
    log_debug("Debug Var = %d", 55);
    log_warning("Warning");
    log_error("Major error");
    log_critical("Critical");
    return 0;
}