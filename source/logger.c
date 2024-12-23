#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

bool echo = false;

/* Open a new stream `path` with mode `w` and return the log handle.  */
__attr_nonnull
struct Logger * log_init(const char *path, const char *identifier)
{
    FILE *stream = fopen(path, "w");
    if (!stream)
    {
        fprintf(stderr, "[CRITICAL] (%s): - Cannot open a new file stream for \"%s\".\n", identifier, path);
        abort();
    }
    
    struct Logger *nl = malloc(sizeof(struct Logger));
    if (!nl)
    {
        fprintf(stderr, "ERROR: Cannot allocate memory for logger structure.\n");
        return NULL;
    }

    nl->lstream = stream;
    nl->identifier = identifier;
    
    return nl;
}

/* Writes message `*fmt` + `args` to `out`. Similar to `fprintf` */
__attr_nonnull
int log_vwritef(FILE *out, const char *id, ErrType type, const char *fmt, va_list args)
{
    time_t now;
    char timestamp[20];
    time(&now);

    strftime(timestamp, sizeof timestamp, "%Y-%m-%d %H:%M:%S", localtime(&now));
    va_list copy;
    va_copy(copy, args);

    switch (type)
    {
        case INFO:
            fprintf(out, "[INFO] (%s): \"%s\" - %s, at line %d: ", id, timestamp, __FILE__, __LINE__);
            vfprintf(out, fmt, args);

            if (echo)
            {
                fprintf(stderr, "[INFO] (%s): \"%s\" - %s, at line %d: ", id, timestamp, __FILE__, __LINE__);
                vfprintf(stderr, fmt, copy);
            }
            break;
        
        case ERROR:
            fprintf(out, "[ERROR] (%s): \"%s\" - %s, at line %d: ", id, timestamp, __FILE__, __LINE__);
            vfprintf(out, fmt, args);

            if (echo)
            {
                fprintf(stderr, "[ERROR] (%s): \"%s\" - %s, at line %d: ", id, timestamp, __FILE__, __LINE__);
                vfprintf(stderr, fmt, copy);
            }
            break;

        case CRITICAL:
            fprintf(out, "[CRITICAL] (%s): \"%s\" - %s, at line %d: ", id, timestamp, __FILE__, __LINE__);
            vfprintf(out, fmt, args);

            fprintf(stderr, "[CRITICAL] (%s): \"%s\" - %s, at line %d: ", id, timestamp, __FILE__, __LINE__);
            vfprintf(stderr, fmt, copy);

            fflush(out);
            
            exit(1);

            break;
        
        case RAW:
            vfprintf(out, fmt, args);
            
            if (echo)
                vfprintf(stdout, fmt, copy);
            
            break;
        
        default:
            break;
    }

    va_end(copy);
    fflush(out);

    return 0;
}

/* Call `log_vwritef` to write a message with format equal to `"[INFO]: [TIMESTAMP] - "`fmt` `args`""` */
__attr_nonnull
int log_info(struct Logger *handle, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    log_vwritef(handle->lstream, handle->identifier, INFO, fmt, args);

    return 0;
}    

/* Call `log_vwritef` to write a message with format equal to `"[ERROR]: [TIMESTAMP] - "`fmt` `args`" */
__attr_nonnull
int log_err(struct Logger *handle, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    log_vwritef(handle->lstream, handle->identifier, ERROR, fmt, args);

    return 0;
}    

/* Call `log_vwritef` to write a message with format equal to `"[CRITICAL]: [TIMESTAMP] - "`fmt` `args`"". PRINT to STDERR and `stdlog` and exit the executation with return code 1.` */
__attr_nonnull
void log_critical(struct Logger *handle, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    log_vwritef(handle->lstream, handle->identifier, CRITICAL, fmt, args);
}

__attr_nonnull
void log_raw(struct Logger *handle, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    log_vwritef(handle->lstream, handle->identifier, RAW, fmt, args);
}

void sclog_enable_echoing(void)
{
    echo = true;
    printf("SCLOG: Echoing is enabled.\n");
}

void sclog_disable_echoing(void)
{
    echo = false;
    printf("SCLOG: Echoing is disabled.\n");
}

__attr_nonnull
void sclog_kill_handle(struct Logger *handler)
{
    log_info(handler, "This handler is being killed.\n");

    if (handler->lstream)
        fclose(handler->lstream);
    
    free(handler);
}
