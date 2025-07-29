# c-debug-logger

A lightweight, zero-overhead logging library for C embedded systems that behaves like Python's logger with `assert`-style conditional compilation.

## Features

- 🚀 **Zero overhead in production** - All logging completely removed with `-DNDEBUG`
- 📱 **Embedded-friendly** - No dependencies on dynamic memory
- 🎨 **Colored output** - Different colors for each log level (optional if you are using Putty)
- 📍 **Error location tracking** - File name and line number for errors and critical logs
- 🐍 **Python-like API** - Familiar logging interface with multiple levels
- 🔧 **Easy integration** - Single header file, no compilation required
- ⚡ **Configurable** - Enable/disable colors, flushing, and log levels

## Quick Start

1. Download `log.h` and include it in your project
2. Include the header and start logging:

```c
#include "log.h"

int main() {
    print_info("Application starting...");
    
    int sensor_value = read_sensor();
    print_debug("Sensor reading: %d", sensor_value);
    
    if (sensor_value < 0) {
        print_error("Sensor read failed with value: %d", sensor_value);
        return -1;
    }
    
    print_info("Application running successfully");
    return 0;
}
```

## Log Levels

The library supports 5 log levels (similar to Python's logging):

```c
print_debug("Detailed diagnostic info");      // Level 0 - Cyan
print_info("General information");            // Level 1 - Green  
print_warning("Something unexpected");        // Level 2 - Yellow
print_error("Error occurred");               // Level 3 - Red (with file:line)
print_critical("Critical system failure");   // Level 4 - Magenta (with file:line)
```

## Build Configurations

### Debug Build (Development)
```bash
gcc -o myapp main.c
# All logging enabled
```

### Release Build (Production)
```bash
gcc -DNDEBUG -o myapp main.c
# All logging completely removed - zero overhead!
```

### Example Output

**Debug build:**
```
[INFO]: Application starting...
[DEBUG]: Sensor reading: 42
[ERROR] main.c:15: Sensor read failed with value: -1
```

**Release build:**
```
(no logging output - all calls removed by compiler)
```

## Configuration Options

### Disable Colors
```c
#define ENABLE_COLORS 0  // Set to 0 before including log.h
#include "log.h"
```

### Force Immediate Output (Embedded Systems)
```c
#define EMBEDDED_FLUSH   // Define before including log.h
#include "log.h"
```

### Set Log Level at Runtime
```c
set_log_level(print_warning);  // Only WARNING, ERROR, CRITICAL will show
print_debug("This won't appear");
print_error("This will appear");
```

## API Reference

### Logging Macros
- `print_debug(format, ...)` - Debug information
- `print_info(format, ...)` - General information  
- `print_warning(format, ...)` - Warning messages
- `print_error(format, ...)` - Error messages (with file:line)
- `print_critical(format, ...)` - Critical errors (with file:line)

### Configuration Functions
- `set_log_level(log_level_t level)` - Set minimum log level
- `get_log_level()` - Get current log level

### Log Levels
```c
    LOG_DEBUG = 0,
    LOG_INFO = 1,
    LOG_WARNING = 2,
    LOG_ERROR = 3,
    LOG_CRITICAL = 4
```

## Why This Logger?

### ✅ Perfect for Embedded Systems
- No heap allocation
- No external dependencies
- Minimal flash/RAM usage
- Works with any C compiler

### ✅ Production Safe
- Zero performance impact in release builds
- No sensitive debug info in production binaries
- Same binary behavior as `assert()` macros

### ✅ Developer Friendly
- Familiar Python-like interface
- Colored output for easy reading
- File/line info for quick debugging
- Printf-style formatting

## Examples

### Basic Usage
```c
#include "log.h"

void sensor_task() {
    print_info("Starting sensor task");
    
    for (int i = 0; i < 10; i++) {
        int reading = read_sensor(i);
        print_debug("Sensor %d: %d", i, reading);
        
        if (reading > THRESHOLD) {
            print_warning("Sensor %d above threshold: %d", i, reading);
        }
    }
}
```

### Error Handling
```c
#include "log.h"

int init_hardware() {
    print_info("Initializing hardware...");
    
    if (init_gpio() != 0) {
        print_error("GPIO initialization failed");
        return -1;
    }
    
    if (init_uart() != 0) {
        print_critical("UART initialization failed - system unusable");
        return -1;
    }
    
    print_info("Hardware initialized successfully");
    return 0;
}
```

### Conditional Compilation Example
```c
// This code:
print_debug("Processing %d items", count);
expensive_debug_function();

// Becomes this in release builds:
((void)0);  // Completely removed
expensive_debug_function();  // Still executes!
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Changelog

### v1.0.0
- Initial release
- Zero-overhead logging with NDEBUG
- Colored output support
- File/line tracking for errors
- Embedded system optimizations