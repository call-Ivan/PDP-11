#include <stdio.h>
#include <stdarg.h>
#include "logging.h"

int main()
{
    set_log_level(INFO);

    int x, y;
    scanf("%d%d", &x, &y);

    logging(INFO, "%d + %d = %d\n", x, y, x + y - 1);
    logging(ERROR, "Oops, %d+%d=%d, not %d\n", x, y, x + y, x + y - 1);
    logging(TRACE, "Эту надпись не должны видеть\n");

    int old_log_level = set_log_level(TRACE);

    logging(TRACE, "Visible text\n");
    logging(DEBUG, "Debug info\n");

    set_log_level(old_log_level);

    logging(INFO, "The end!\n");
    logging(TRACE, "No code after return\n");

    // мои тесты для logging
    printf("Первый тест: уровень INFO"); // дописать свои тесты для проверки logging

    return 0;
}