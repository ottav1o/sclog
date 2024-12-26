#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <stdarg.h>

#define SCLOG_DEFAULT_HANDLE NULL
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

extern struct Logger *default_handle;

__attribute__((nonnull))
struct Logger * log_init(const char *path, const char *identifier); /* Initiaze a new log handle with id `identifier` and log output file `path`. */

__attribute__((nonnull))
int log_vwritef(FILE *out, const char *id, ErrType type, const char *fmt, va_list args);

__attribute__((nonnull(2)))
void log_info(struct Logger *handle, const char *fmt, ...);             /* Call `log_vwritef` to write a message with format equal to `"[INFO]: [TIMESTAMP] - __FILE__, at line __LINE__ "`fmt` `args`""` */

__attribute__((nonnull(2)))
void log_err(struct Logger *handle, const char *fmt, ...);              /* Call `log_vwritef` to write a message with format equal to `"[ERROR]: [TIMESTAMP] - __FILE__, at line __LINE__ "`fmt` `args`"". DOES NOT PRINT to STDOUT or STDERR.` */

__attribute__((nonnull(2)))
void log_critical(struct Logger *handle, const char *fmt, ...);         /* Call `log_vwritef` to write a message with format equal to `"[CRITICAL]: [TIMESTAMP] - __FILE__, at line __LINE__ "`fmt` `args`"". PRINT to STDERR and `stdlog` and exit the executation with return code 1.` */

__attribute__((nonnull(2)))
void log_raw(struct Logger *handle, const char *fmt, ...);

void sclog_enable_echoing(void);
void sclog_disable_echoing(void);

__attribute__((nonnull))
void sclog_set_default_handle(struct Logger *handle);

__attribute__((nonnull))
void sclog_kill_handle(struct Logger *handler);

#endif /* __LOGGER_H__ */
