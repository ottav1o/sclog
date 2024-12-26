#include <stdio.h>
#include "../source/logger.h"

int main(void)
{
    struct Logger *h = log_init("./logs.txt", "FOO-BAZ-BAR");
    sclog_enable_echoing();
    sclog_set_default_handle(h);
    log_info(SCLOG_DEFAULT_HANDLE, "Hello World!\n");
    
    sclog_disable_echoing();

    sclog_kill_handle(h);

    return 0;
}
