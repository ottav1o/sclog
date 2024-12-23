#include <stdio.h>
#include "../source/logger.h"

int main(void)
{
    struct Logger *h = log_init("./logs.txt", "FOO-BAZ-BAR");
    sclog_enable_echoing();
    log_info(h, "And we are... Nirvana!\n");
    sclog_disable_echoing();

    sclog_kill_handle(h);

    return 0;
}
