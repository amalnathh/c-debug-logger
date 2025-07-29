#include "log.h"

int main() {
    int temperature = 500;
    
    // These work in debug builds, disappear in production
    log_info("System starting...");
    log_debug("Temperature sensor: %d°C", temperature);
    
    if (temperature > 50) {
        log_error("Overheating detected: %d°C", temperature);
        log_critical("Fuck you");
    }
    
    return 0;
}