#ifndef GST_REPEAT_LOG_H
#define GST_REPEAT_LOG_H

#include <gst/gst.h>

/**
 * Sends a log message with INFO level to GStreamer's log.<br />
 * <br />
 * This uses WARN by default instead of INFO, because INFO is cluttered with GST messages.
 */
#define INFO(depth, ...) r_log(GST_LEVEL_WARNING, depth, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

/**
 * Sends a log message with ERROR level to GStreamer's log.
 */
#define ERROR(depth, ...) r_log(GST_LEVEL_ERROR, depth, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define R_DEPTH_ROUTINE  10001
#define R_DEPTH_ACTION   10002

/**
 * Send a log message entry to GStreamer's log.
 *
 * @param level  GST_LEVEL
 * @param depth  R_DEPTH
 * @param format Format string
 * @param ...    Format varargs
 * @return void
 */
void r_log(int level, int depth, const char* file, const char* function, int line, const char* format, ...);

#endif //GST_REPEAT_LOG_H
