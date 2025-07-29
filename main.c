#include "log.h"

int main() {
    set_log_level(LOG_ERROR);
    
    // These work in debug builds, disappear in production
    print_info("This is an info");
    print_debug("Debug Var = %d", 55);
    print_warning("Warning");
    print_error("Major error");
    print_critical("Critical");
    return 0;
}