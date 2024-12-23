#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <stdarg.h>

#define __attr_nonnull __attribute__((nonnull))

// enum {
//     SCLOG_HANDLER_DEFAULT
// };

typedef enum {
    INFO,
    ERROR,
    CRITICAL,
    RAW
} ErrType;

struct Logger {
    const char *identifier;
    FILE *lstream;
};

__attr_nonnull
struct Logger * log_init(const char *path, const char *identifier); /* Initiaze a new log handle with id `identifier` and log output file `path`. */

__attr_nonnull
int log_vwritef(FILE *out, const char *id, ErrType type, const char *fmt, va_list args);

__attr_nonnull
int log_info(struct Logger *handle, const char *fmt, ...);             /* Call `log_vwritef` to write a message with format equal to `"[INFO]: [TIMESTAMP] - __FILE__, at line __LINE__ "`fmt` `args`""` */

__attr_nonnull
int log_err(struct Logger *handle, const char *fmt, ...);              /* Call `log_vwritef` to write a message with format equal to `"[ERROR]: [TIMESTAMP] - __FILE__, at line __LINE__ "`fmt` `args`"". DOES NOT PRINT to STDOUT or STDERR.` */

__attr_nonnull
void log_critical(struct Logger *handle, const char *fmt, ...);         /* Call `log_vwritef` to write a message with format equal to `"[CRITICAL]: [TIMESTAMP] - __FILE__, at line __LINE__ "`fmt` `args`"". PRINT to STDERR and `stdlog` and exit the executation with return code 1.` */

__attr_nonnull
void log_raw(struct Logger *handle, const char *fmt, ...);

void sclog_enable_echoing(void);
void sclog_disable_echoing(void);

void sclog_set_default_handle(struct Logger *handle);

__attr_nonnull
void sclog_kill_handle(struct Logger *handler);

#endif /* __LOGGER_H__ */
