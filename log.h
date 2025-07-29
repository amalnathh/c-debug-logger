#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>  // For variadic functions (printf-style formatting)
#include <string.h>  // For strrchr to extract filename

// Log levels
typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO = 1,
    LOG_WARNING = 2,
    LOG_ERROR = 3,
    LOG_CRITICAL = 4
} log_level_t;

// Global log level (only messages at this level or higher will be printed)
static log_level_t current_log_level = LOG_INFO;

// ANSI color codes for different log levels (disable if your terminal doesn't support colors)
#define RESET_COLOR   "\033[0m"
#define DEBUG_COLOR   "\033[36m"  // Cyan
#define INFO_COLOR    "\033[32m"  // Green
#define WARNING_COLOR "\033[33m"  // Yellow
#define ERROR_COLOR   "\033[31m"  // Red
#define CRITICAL_COLOR "\033[35m" // Magenta

// Set to 0 to disable colors for embedded systems without color terminal support
#define ENABLE_COLORS 1

// Get log level string and color
static const char* get_level_string(log_level_t level) {
    switch(level) {
        case LOG_DEBUG:    return "DEBUG";
        case LOG_INFO:     return "INFO";
        case LOG_WARNING:  return "WARNING";
        case LOG_ERROR:    return "ERROR";
        case LOG_CRITICAL: return "CRITICAL";
        default:           return "UNKNOWN";
    }
}

static const char* get_level_color(log_level_t level) {
#if ENABLE_COLORS
    switch(level) {
        case LOG_DEBUG:    return DEBUG_COLOR;
        case LOG_INFO:     return INFO_COLOR;
        case LOG_WARNING:  return WARNING_COLOR;
        case LOG_ERROR:    return ERROR_COLOR;
        case LOG_CRITICAL: return CRITICAL_COLOR;
        default:           return RESET_COLOR;
    }
#else
    return ""; // No colors for embedded systems
#endif
}

// Check if NDEBUG is defined (same as assert behavior)
#ifdef NDEBUG
    // Release build - all logging disabled (compiles to nothing)
    #define log_debug(format, ...)    ((void)0)
    #define log_info(format, ...)     ((void)0)
    #define log_warning(format, ...)  ((void)0)
    #define log_error(format, ...)    ((void)0)
    #define log_critical(format, ...) ((void)0)
    
    // Stub functions for release builds
    #define set_log_level(level)      ((void)0)
    #define get_log_level()           (LOG_INFO)

#else
    // Debug build - logging enabled
    
    // Core logging function
    static void log_message(log_level_t level, const char* format, ...) {
        if (level < current_log_level) {
            return; // Skip if below current log level
        }
        
        const char* level_str = get_level_string(level);
        const char* color = get_level_color(level);
        const char* reset = ENABLE_COLORS ? RESET_COLOR : "";
        
        // Print log level with optional color
        printf("%s[%s]%s: ", color, level_str, reset);
        
        // Print the actual message using variadic arguments
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
        
        printf("\n");
        
        // For embedded systems, you might want to ensure immediate output
        #ifdef EMBEDDED_FLUSH
        fflush(stdout);
        #endif
    }
    
    // Core logging function with file and line info (for errors)
    static void log_message_with_location(log_level_t level, const char* file, int line, const char* format, ...) {
        if (level < current_log_level) {
            return; // Skip if below current log level
        }
        
        const char* level_str = get_level_string(level);
        const char* color = get_level_color(level);
        const char* reset = ENABLE_COLORS ? RESET_COLOR : "";
        
        // Extract just the filename (not full path)
        const char* filename = strrchr(file, '/');
        if (filename) {
            filename++;  // Skip the '/'
        } else {
            // Try Windows path separator
            filename = strrchr(file, '\\');
            if (filename) {
                filename++;  // Skip the '\'
            } else {
                filename = file;  // No path separator found, use as-is
            }
        }
        
        // Print log level with file and line info
        printf("%s[%s]%s %s:%d: ", color, level_str, reset, filename, line);
        
        // Print the actual message using variadic arguments
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
        
        printf("\n");
        
        // For embedded systems, you might want to ensure immediate output
        #ifdef EMBEDDED_FLUSH
        fflush(stdout);
        #endif
    }

    // Convenience macros for different log levels
    #define print_debug(format, ...)    log_message(LOG_DEBUG, format, ##__VA_ARGS__)
    #define print_info(format, ...)     log_message(LOG_INFO, format, ##__VA_ARGS__)
    #define print_warning(format, ...)  log_message(LOG_WARNING, format, ##__VA_ARGS__)
    #define print_error(format, ...)    log_message_with_location(LOG_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)
    #define print_critical(format, ...) log_message_with_location(LOG_CRITICAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

#endif // NDEBUG

// Function to set the global log level
static void set_log_level(log_level_t level) {
    current_log_level = level;
}

// Function to get current log level
static log_level_t get_log_level(void) {
    return current_log_level;
}

#endif // LOG_H