#ifndef GST_REPEAT_ERROR_H
#define GST_REPEAT_ERROR_H

#define R_CODE_SUCCESS                                   0
#define R_CODE_ERROR_OPTIONS                          9001
#define R_CODE_ERROR_NO_PIPELINE                      9002

// TODO let CMake set these values...
#define R_VERSION_MAJOR                                  1
#define R_VERSION_MINOR                                  0
#define R_VERSION_PATCH                                  0
#define R_VERSION_REV                                    1
#define R_VERSION         g_strdup_printf("%d.%d.%d/%d", \
                                        R_VERSION_MAJOR, \
                                        R_VERSION_MINOR, \
                                        R_VERSION_PATCH, \
                                        R_VERSION_REV  )

#endif //GST_REPEAT_ERROR_H
