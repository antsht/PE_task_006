#include "cafe_logic.h"

ErrorCode is_valid_command(char *command) {
    if (strcmp(command, "ORDER") == 0 || strcmp(command, "BAR") == 0 || strcmp(command, "KITCHEN") == 0 ||
        strcmp(command, "STATS") == 0 || strcmp(command, "EXIT") == 0)
        return INVALID_INPUT;
    return OK;
}

void init_queue(Orders_queue_t *queue) {
    queue->current_order_index = 0;
    queue->last_order_index = -1;
    for (int i = 0; i < MAX_RECORDS; i++) {
        queue->orders[i].cost = 0;
        queue->orders[i].order[0] = '\0';
    }
}
ErrorCode get_command(char *command) {
    if (scanf("%s", command) != 1 || !is_valid_command(command)) {
        return INVALID_COMMAND;
    }
    getchar();
    return OK;
}

ErrorCode main_menu_loop(Orders_queue_t *kitchen_queue, Orders_queue_t *bar_queue, Cafe_stats_t *cafe_stats) {
    int stop = 0;
    ErrorCode error = OK;

    while (!stop) {
        char command[BUFFER] = {0};
        try(get_command(command));

        if (strcmp(command, "ORDER") == 0) {
            try(get_order(kitchen_queue));
            try(get_order(bar_queue));
        }

        if (strcmp(command, "BAR") == 0) {
            try(process_order(bar_queue, BAR, cafe_stats));
        }

        if (strcmp(command, "KITCHEN") == 0) {
            try(process_order(kitchen_queue, KITCHEN, cafe_stats));
        }

        if (strcmp(command, "STATS") == 0) {
            print_stats(cafe_stats);
        }
        if (strcmp(command, "EXIT") == 0) {
            stop = 1;
        }
    }
    return error;
}

ErrorCode get_order(Orders_queue_t *queue) {
    char order[MAX_ORDER_LEN] = {0};
    int cost = 0;
    fgets(order, MAX_ORDER_LEN - 1, stdin);
    if (order[strlen(order) - 1] == '\n') order[strlen(order) - 1] = '\0';
    if (strlen(order) == 0) return INVALID_INPUT;
    if (scanf("%d", &cost) != 1 || cost < 0) return INVALID_INPUT;
    getchar();
    try(add_order(queue, order, cost));
    return OK;
}

ErrorCode add_order(Orders_queue_t *queue, char *order, int cost) {
    if (queue->last_order_index == MAX_RECORDS - 1) {
        return BUFFER_OVERFLOW;
    }
    queue->last_order_index++;
    strcpy(queue->orders[queue->last_order_index].order, order);
    queue->orders[queue->last_order_index].cost = cost;
    return OK;
}
ErrorCode process_order(Orders_queue_t *queue, Queue_type_t type, Cafe_stats_t *cafe_stats) {
    if (queue->current_order_index > queue->last_order_index) {
        return NO_DATA;
    }
    printf("%s\n", queue->orders[queue->current_order_index].order);
    if (type == KITCHEN) {
        cafe_stats->kitchen_orders_amount++;
        cafe_stats->kitchen_income += queue->orders[queue->current_order_index].cost;
    }
    if (type == BAR) {
        cafe_stats->bar_orders_amount++;
        cafe_stats->bar_income += queue->orders[queue->current_order_index].cost;
    }

    queue->current_order_index++;
    return OK;
}

void print_stats(Cafe_stats_t *cafe_stats) {
    printf("KITCHEN %d %d\n", cafe_stats->kitchen_orders_amount, cafe_stats->kitchen_income);
    printf("BAR %d %d\n", cafe_stats->bar_orders_amount, cafe_stats->bar_income);
}
