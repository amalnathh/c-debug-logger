#include "log.h"

int main() {
    set_log_level(LOG_ERROR);

    const char *modes[] = {"Debug", "Info", "Warning", "Error", "Critical"};
    int sel = getInput("Select log level:", modes, 5);
    set_log_level((log_level_t)sel);
    print_info("Log level set to %s", modes[sel]);

    
    // These work in debug builds, disappear in production
    print_info("This is an info");
    print_debug("Debug Var = %d", 55);
    print_warning("Warning");
    print_error("Major error");
    print_critical("Critical");


    return 0;
}