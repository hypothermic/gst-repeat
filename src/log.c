#include "log.h"

void r_log(int level, int depth, const char* file, const char* function, int line, const char* format, ...) {
    va_list args;
    va_start(args, format);

    gst_debug_log_valist(GST_CAT_DEFAULT, level, file, function, line, NULL, format, args);

    va_end(args);
}