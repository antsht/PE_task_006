#include "cafe_libs/cafe_logic.h"

int main(void) {
    Orders_queue_t kitchen_queue;
    init_queue(&kitchen_queue);

    Orders_queue_t bar_queue;
    init_queue(&bar_queue);

    Cafe_stats_t cafe_stats = {
        .kitchen_orders_amount = 0, .kitchen_income = 0, .bar_orders_amount = 0, .bar_income = 0};

    try(main_menu_loop(&kitchen_queue, &bar_queue, &cafe_stats));

    return 0;
}